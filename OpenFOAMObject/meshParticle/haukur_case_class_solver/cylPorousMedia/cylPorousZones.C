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

\*---------------------------------------------------------------------------*/

#include "cylPorousZones.H"
#include "Time.H"
#include "volFields.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTemplateTypeNameAndDebug(IOPtrList<cylPorousZone>, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::cylPorousZones::cylPorousZones
(
    const fvMesh& mesh,
    const coordinateSystems& cs
)
:
    IOPtrList<cylPorousZone>
    (
        IOobject
        (
            "cylPorousZones",
            mesh.time().constant(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::NO_WRITE
        ),
        cylPorousZone::iNew(mesh)
    ),
    mesh_(mesh),
    csList_(cs)
{}


Foam::cylPorousZones::cylPorousZones
(
    const fvMesh& mesh
)
:
    IOPtrList<cylPorousZone>
    (
        IOobject
        (
            "cylPorousZones",
            mesh.time().constant(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        cylPorousZone::iNew(mesh)
    ),
    mesh_(mesh),
    csList_(mesh)
{
    clear();

    IOPtrList<cylPorousZone> newList
    (
        IOobject
        (
            "cylPorousZones",
            mesh_.time().constant(),
            mesh_,
            IOobject::READ_IF_PRESENT,
            IOobject::NO_WRITE,
            false     // Don't register new zones with objectRegistry
        ),
        cylPorousZone::iNew(mesh_, csList_)
    );

    transfer(newList);
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::cylPorousZones::addResistance(fvVectorMatrix& UEqn) const
{
    forAll(*this, i)
    {
        operator[](i).addResistance(UEqn);
    }
}


void Foam::cylPorousZones::addResistance
(
    const fvVectorMatrix& UEqn,
    volTensorField& AU
) const
{
    // addResistance for each zone, delaying the correction of the
    // precessor BCs of AU
    forAll(*this, i)
    {
        operator[](i).addResistance(UEqn, AU, false);
    }

    // Correct the boundary conditions of the tensorial diagonal to ensure
    // processor bounaries are correctly handled when AU^-1 is interpolated
    // for the pressure equation.
    AU.correctBoundaryConditions();
}


bool Foam::cylPorousZones::readData(Istream& is)
{
    clear();

    IOPtrList<cylPorousZone> newList
    (
        IOobject
        (
            "cylPorousZones",
            mesh_.time().constant(),
            mesh_,
            IOobject::MUST_READ,
            IOobject::NO_WRITE,
            false     // Don't register new zones with objectRegistry
        ),
        cylPorousZone::iNew(mesh_, csList_)
    );

    transfer(newList);

    return is.good();
}


bool Foam::cylPorousZones::writeData(Ostream& os, bool subDict) const
{
    // Write size of list
    os << nl << size();

    // Write beginning of contents
    os << nl << token::BEGIN_LIST;

    // Write list contents
    forAll(*this, i)
    {
        os << nl;
        operator[](i).writeDict(os, subDict);
    }

    // Write end of contents
    os << token::END_LIST << nl;

    // Check state of IOstream
    return os.good();
}


// ************************************************************************* //
