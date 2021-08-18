/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) YEAR OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "fixedValueFvPatchFieldTemplate.H"
#include "addToRunTimeSelectionTable.H"
#include "fvPatchFieldMapper.H"
#include "volFields.H"
#include "surfaceFields.H"
#include "unitConversion.H"
//{{{ begin codeInclude

//}}} end codeInclude


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Local Functions * * * * * * * * * * * * * * //

//{{{ begin localCode

//}}} end localCode


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

extern "C"
{
    // dynamicCode:
    // SHA1 = 3923d4a32dfa277b980352d876236decbb50d3e8
    //
    // unique function name that can be checked if the correct library version
    // has been loaded
    void heating_3923d4a32dfa277b980352d876236decbb50d3e8(bool load)
    {
        if (load)
        {
            // code that can be explicitly executed after loading
        }
        else
        {
            // code that can be explicitly executed before unloading
        }
    }
}

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

makeRemovablePatchTypeField
(
    fvPatchScalarField,
    heatingFixedValueFvPatchScalarField
);


const char* const heatingFixedValueFvPatchScalarField::SHA1sum =
    "3923d4a32dfa277b980352d876236decbb50d3e8";


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

heatingFixedValueFvPatchScalarField::
heatingFixedValueFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF
)
:
    fixedValueFvPatchField<scalar>(p, iF)
{
    if (false)
    {
        Info<<"construct heating sha1: 3923d4a32dfa277b980352d876236decbb50d3e8"
            " from patch/DimensionedField\n";
    }
}


heatingFixedValueFvPatchScalarField::
heatingFixedValueFvPatchScalarField
(
    const heatingFixedValueFvPatchScalarField& ptf,
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedValueFvPatchField<scalar>(ptf, p, iF, mapper)
{
    if (false)
    {
        Info<<"construct heating sha1: 3923d4a32dfa277b980352d876236decbb50d3e8"
            " from patch/DimensionedField/mapper\n";
    }
}


heatingFixedValueFvPatchScalarField::
heatingFixedValueFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const dictionary& dict
)
:
    fixedValueFvPatchField<scalar>(p, iF, dict)
{
    if (false)
    {
        Info<<"construct heating sha1: 3923d4a32dfa277b980352d876236decbb50d3e8"
            " from patch/dictionary\n";
    }
}


heatingFixedValueFvPatchScalarField::
heatingFixedValueFvPatchScalarField
(
    const heatingFixedValueFvPatchScalarField& ptf
)
:
    fixedValueFvPatchField<scalar>(ptf)
{
    if (false)
    {
        Info<<"construct heating sha1: 3923d4a32dfa277b980352d876236decbb50d3e8"
            " as copy\n";
    }
}


heatingFixedValueFvPatchScalarField::
heatingFixedValueFvPatchScalarField
(
    const heatingFixedValueFvPatchScalarField& ptf,
    const DimensionedField<scalar, volMesh>& iF
)
:
    fixedValueFvPatchField<scalar>(ptf, iF)
{
    if (false)
    {
        Info<<"construct heating sha1: 3923d4a32dfa277b980352d876236decbb50d3e8 "
            "as copy/DimensionedField\n";
    }
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

heatingFixedValueFvPatchScalarField::
~heatingFixedValueFvPatchScalarField()
{
    if (false)
    {
        Info<<"destroy heating sha1: 3923d4a32dfa277b980352d876236decbb50d3e8\n";
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void heatingFixedValueFvPatchScalarField::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }

    if (false)
    {
        Info<<"updateCoeffs heating sha1: 3923d4a32dfa277b980352d876236decbb50d3e8\n";
    }

//{{{ begin code
    #line 37 "/home/boyao/C++/OpenFOAMObject/meshParticle/cylinderParticle/0/T.boundaryField.bottomWall"
const scalar t = this->db().time().value();
            const scalar Ttemp = 273 + 10*t;
            operator==(Ttemp);
//}}} end code

    this->fixedValueFvPatchField<scalar>::updateCoeffs();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //

