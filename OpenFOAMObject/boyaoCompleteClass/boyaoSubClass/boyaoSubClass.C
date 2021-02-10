/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2021 OpenFOAM Foundation
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
#include "boyaoSubClass.H"
#include "addToRunTimeSelectionTable.H"

namespace Foam
{
    defineTypeNameAndDebug(boyaoSubClass, 0);
    addToRunTimeSelectionTable(boyaoClass2, boyaoSubClass, dictionary);
}

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

//const dataType Foam::boyaoSubClass::staticData();


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::boyaoSubClass::boyaoSubClass()
:
    boyaoClass2()
{}

  //- Construct from components
Foam::boyaoSubClass::boyaoSubClass(const word& name)
:
    boyaoClass2(name)
{
  Info << "call boyaoSub" << nl;
}

// Foam::boyaoSubClass::boyaoSubClass(const fvMesh& mesh)
// :
//     boyaoClass2(), mesh_(mesh)
// {
//   Info << "construct from mesh " << nl;
// }



// Foam::boyaoSubClass::boyaoSubClass(const dataType& data)
// :
//     baseClassName(),
//     data_(data)
// {}
//
//
// Foam::boyaoSubClass::boyaoSubClass(const boyaoSubClass&)
// :
//     baseClassName(),
//     data_()
// {}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::boyaoSubClass>
Foam::boyaoSubClass::New()
{
    return autoPtr<boyaoSubClass>(new boyaoSubClass);
}


Foam::autoPtr<Foam::boyaoClass2> Foam::boyaoSubClass::New
 (
     const fvMesh& mesh
 )
 {

     IOobject nameBoyaoSub
     (
         "boyaoSubProperties", //this indicates which file in constant folder it is in
         mesh.time().constant(),
         mesh,
         IOobject::MUST_READ_IF_MODIFIED,
         IOobject::NO_WRITE,
         false
     );


     word modelType("none");
     if (nameBoyaoSub.typeHeaderOk<IOdictionary>(false))
     {
         IOdictionary(nameBoyaoSub).lookup("reactorProperties") >> modelType; //here you search for the model e.g. P1 model in the run folder
     }
     else
     {
         Info<< "Reactor model not active: reactorProperties not found"
             << endl;
     }

     Info<< "Selecting reactor model " << modelType << endl; // print the model you have chosed


      boyaoClass2::dictionaryConstructorTable::iterator cstrIter =
          boyaoClass2::dictionaryConstructorTablePtr_->find(modelType);


     if (cstrIter == boyaoClass2::dictionaryConstructorTablePtr_->end())
     {
         FatalErrorInFunction
             << "Unknown radiationModel type "
             << modelType << nl << nl
             << "Valid radiationModel types are:" << nl
             << boyaoClass2::dictionaryConstructorTablePtr_->sortedToc()
             << exit(FatalError);
     }
     const word& name = "name";
     return autoPtr<Foam::boyaoClass2>(cstrIter()(name));
 }
 //
 //
 // template<class Thermo>
 // Foam::autoPtr<Thermo> Foam::basicThermo::New
 // (
 //     const fvMesh& mesh,
 //     const word& phaseName
 // )
 // {
 //     IOdictionary thermoDict
 //     (
 //         IOobject
 //         (
 //             phasePropertyName(dictName, phaseName),
 //             mesh.time().constant(),
 //             mesh,
 //             IOobject::MUST_READ_IF_MODIFIED,
 //             IOobject::NO_WRITE,
 //             false
 //         )
 //     );
 //
 //     typename Thermo::fvMeshConstructorTable::iterator cstrIter =
 //         lookupThermo<Thermo, typename Thermo::fvMeshConstructorTable>
 //         (
 //             thermoDict,
 //             Thermo::fvMeshConstructorTablePtr_
 //         );
 //     Info << "call basicThermo New here 1" << nl;
 //
 //     return autoPtr<Thermo>(cstrIter()(mesh, phaseName));
 // }


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::boyaoSubClass::~boyaoSubClass()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

// void Foam::boyaoSubClass::operator=(const boyaoSubClass& rhs)
// {
//     // Check for assignment to self
//     if (this == &rhs)
//     {
//         FatalErrorInFunction
//             << "Attempted assignment to self"
//             << abort(FatalError);
//     }
// }

// * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * Friend Operators * * * * * * * * * * * * * * //


// ************************************************************************* //
