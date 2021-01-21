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

#include "boyaoClass2.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

//const dataType Foam::boyaoClass2::staticData();


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //


namespace Foam
{
      defineTypeNameAndDebug(boyaoClass2, 0);
      defineRunTimeSelectionTable(boyaoClass2, dictionary);
}

Foam::boyaoClass2::boyaoClass2()
{}


Foam::boyaoClass2::boyaoClass2(const label& data)
{}

Foam::boyaoClass2::boyaoClass2(const word& name)
{
  Info << "you input a name " << name << nl;
}

Foam::boyaoClass2::boyaoClass2(const boyaoClass2&)
{}



// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

// Foam::autoPtr<Foam::boyaoClass2>
// Foam::boyaoClass2::New()
// {
//     return autoPtr<boyaoClass2>(new boyaoClass2);
// }

Foam::autoPtr<Foam::boyaoClass2>
Foam::boyaoClass2::New
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
     return autoPtr<boyaoClass2>(cstrIter()(name));
 }


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::boyaoClass2::~boyaoClass2()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

// void Foam::boyaoClass2::operator=(const boyaoClass2& rhs)
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
