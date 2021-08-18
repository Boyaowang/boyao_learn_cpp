/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 1991-2008 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

\*----------------------------------------------------------------------------*/

#include "cylPorousZone.H"
#include "fvMesh.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void Foam::cylPorousZone::modifyDdt(fvMatrix<Type>& m) const
{
    if (porosity_ < 1)
    {
        const labelList& cells = mesh_.cellZones()[cellZoneID_];

        forAll(cells, i)
        {
            m.diag()[cells[i]]   *= porosity_;
            m.source()[cells[i]] *= porosity_;
        }
    }
}


template<class RhoFieldType>
void Foam::cylPorousZone::addPowerLawResistance
(
    scalarField& Udiag,
    const labelList& cells,
    const scalarField& V,
    const RhoFieldType& rho,
    const vectorField& U
) const
{
    const scalar C0 = C0_;
    const scalar C1m1b2 = (C1_ - 1.0)/2.0;

    forAll (cells, i)
    {
        Udiag[cells[i]] +=
            V[cells[i]]*rho[cells[i]]*C0*pow(magSqr(U[cells[i]]), C1m1b2);
    }
}


template<class RhoFieldType>
void Foam::cylPorousZone::addViscousInertialResistance
(
    scalarField& Udiag,
    vectorField& Usource,
    const labelList& cells,
    const scalarField& V,
    const RhoFieldType& rho,
    const scalarField& mu,
    const vectorField& U
) const
{
    tensor DD = D_.value();
    tensor FF = F_.value();

    const scalar rotAngle = rotationAngle() * 3.14 / 180;
    const scalar radAngle = radialAngle() * 3.14 / 180;

    const vectorField& cellCenter = mesh_.C();   

    forAll (cells, i)
    {
        const vector c = cellCenter[cells[i]];
        const scalar x = c[0];
        const scalar y = c[1];

        //create cylindrical coordinate system
        const vector eR = vector(x,y,0) / mag(vector(x,y,0));
        const vector eZ = vector(0,0,1);
        const vector eT = eZ ^ eR;

        //local coordinate system
        const vector E1 = cos(radAngle)*eR +             0*eT + sin(radAngle)*eZ;
        const vector E2 =             0*eR + cos(rotAngle)*eT + sin(rotAngle)*eZ;

        const coordinateSystem localCS
              (
                "localCS",
                vector(0,0,0),
                E1,
                E2
              );
        //local-to-global transformation tensor
        const tensor E = localCS.R();
        DD = (E & D_ & E.T()).value();
        FF = (E & F_ & E.T()).value();

        tensor dragCoeff = mu[cells[i]]*DD + (rho[cells[i]]*mag(U[cells[i]]))*FF;
        scalar isoDragCoeff = tr(dragCoeff);

        Udiag[cells[i]] += V[cells[i]]*isoDragCoeff;
        Usource[cells[i]] -=
            V[cells[i]]*((dragCoeff - I*isoDragCoeff) & U[cells[i]]);
    }
}


template<class RhoFieldType>
void Foam::cylPorousZone::addPowerLawResistance
(
    tensorField& AU,
    const labelList& cells,
    const RhoFieldType& rho,
    const vectorField& U
) const
{
    const scalar C0 = C0_;
    const scalar C1m1b2 = (C1_ - 1.0)/2.0;

    forAll (cells, i)
    {
        AU[cells[i]] = AU[cells[i]]
          + I*(rho[cells[i]]*C0*pow(magSqr(U[cells[i]]), C1m1b2));
    }
}


template<class RhoFieldType>
void Foam::cylPorousZone::addViscousInertialResistance
(
    tensorField& AU,
    const labelList& cells,
    const RhoFieldType& rho,
    const scalarField& mu,
    const vectorField& U
) const
{
    tensor DD = D_.value();
    tensor FF = F_.value();
      
    const scalar rotAngle = rotationAngle() * 3.14 / 180; 
    const scalar radAngle = radialAngle() * 3.14 / 180;

    const vectorField& cellCenter = mesh_.C();   
 
    forAll (cells, i)
    {

        const vector c = cellCenter[cells[i]];
        const scalar x = c[0];
        const scalar y = c[1];

        //create cylindrical coordinate system
        const vector eR = vector(x,y,0) / mag(vector(x,y,0));
        const vector eZ = vector(0,0,1);
        const vector eT = eZ ^ eR;

        //local coordinate system
        const vector E1 = cos(radAngle)*eR +             0*eT + sin(radAngle)*eZ;  
        const vector E2 =             0*eR + cos(rotAngle)*eT + sin(rotAngle)*eZ;

        const coordinateSystem localCS
              (
                "localCS",
                vector(0,0,0),
                E1,
                E2
              );
        //local-to-global transformation tensor
        const tensor E = localCS.R();
        DD = (E & D_ & E.T()).value();
        FF = (E & F_ & E.T()).value();

        AU[cells[i]] += mu[cells[i]]*DD + (rho[cells[i]]*mag(U[cells[i]]))*FF;
    }
}


// ************************************************************************* //
