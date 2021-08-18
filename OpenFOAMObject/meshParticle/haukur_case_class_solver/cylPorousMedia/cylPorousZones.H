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

Class
    Foam::cylPorousZones

Description
    A centralized cylPorousZone collection.

    Container class for a set of cylPorousZones with the cylPorousZone member
    functions implemented to loop over the functions for each cylPorousZone.

    The input file @c constant/cylPorousZone is implemented as
    IOPtrList\<cylPorousZone\> and contains the following type of data:

    @verbatim
    1
    (
    cat1
    {
        coordinateSystem    system_10;
        porosity        0.781;
        Darcy
        {
            d   d [0 -2 0 0 0]  (-1000 -1000 0.50753e+08);
            f   f [0 -1 0 0 0]  (-1000 -1000 12.83);
        }
    }
    )
    @endverbatim

SourceFiles
    cylPorousZones.C

\*---------------------------------------------------------------------------*/

#ifndef cylPorousZones_H
#define cylPorousZones_H

#include "cylPorousZone.H"
#include "IOPtrList.H"

#include "volFieldsFwd.H"
#include "fvMatrix.H"
#include "oneField.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class cylPorousZones Declaration
\*---------------------------------------------------------------------------*/

class cylPorousZones
:
    public IOPtrList<cylPorousZone>
{
    // Private data

        //- Reference to the finite volume mesh this zone is part of
        const fvMesh& mesh_;

        //- Reference to constant coordinate systems
        coordinateSystems csList_;

    // Private Member Functions

        //- Disallow default bitwise copy construct
        cylPorousZones(const cylPorousZones&);

        //- Disallow default bitwise assignment
        void operator=(const cylPorousZones&);


        //- modify time derivative elements
        template<class Type>
        void modifyDdt(fvMatrix<Type>&) const;

public:

    // Constructors

        //- Construct from fvMesh and coordinate systems list
        cylPorousZones(const fvMesh& mesh, const coordinateSystems& cs);

        //- Construct from fvMesh
        //  with automatically constructed coordinate systems list
        cylPorousZones(const fvMesh& mesh);


    // Member Functions

        //- mirror fvm::ddt with porosity
        template<class Type>
        tmp<fvMatrix<Type> > ddt
        (
            GeometricField<Type, fvPatchField, volMesh>&
        );

        //- mirror fvm::ddt with porosity
        template<class Type>
        tmp<fvMatrix<Type> > ddt
        (
            const oneField&,
            GeometricField<Type, fvPatchField, volMesh>&
        );

        //- mirror fvm::ddt with porosity
        template<class Type>
        tmp<fvMatrix<Type> > ddt
        (
            const dimensionedScalar&,
            GeometricField<Type, fvPatchField, volMesh>&
        );

        //- mirror fvm::ddt with porosity
        template<class Type>
        tmp<fvMatrix<Type> > ddt
        (
            const volScalarField&,
            GeometricField<Type, fvPatchField, volMesh>&
        );

        //- Add the viscous and inertial resistance force contribution
        //  to the momentum equation
        void addResistance(fvVectorMatrix& UEqn) const;

        //- Add the viscous and inertial resistance force contribution
        //  to the tensorial diagonal
        void addResistance
        (
            const fvVectorMatrix& UEqn,
            volTensorField& AU
        ) const;

        //- read modified data
        virtual bool readData(Istream&);

        //- write data
        bool writeData(Ostream&, bool subDict = true) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "cylPorousZonesTemplates.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
