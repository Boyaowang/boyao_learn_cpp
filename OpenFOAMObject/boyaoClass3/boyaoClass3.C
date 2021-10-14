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

#include "boyaoClass3.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

//const dataType Foam::boyaoClass3::staticData();


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //


namespace Foam
{
  defineTypeNameAndDebug(boyaoClass3, 0);
  defineRunTimeSelectionTable(boyaoClass3, dictionary);
}

Foam::boyaoClass3::boyaoClass3()
{}


Foam::boyaoClass3::boyaoClass3(const label& data)
{}


Foam::boyaoClass3::boyaoClass3(const boyaoClass3&)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::boyaoClass3>
Foam::boyaoClass3::New(const word modelType)
{
  Info<< "Selecting boyaoClass3 model " << modelType << endl;
  typename dictionaryConstructorTable::iterator cstrIter =
      dictionaryConstructorTablePtr_->find(modelType);

  if (cstrIter == dictionaryConstructorTablePtr_->end())
  {
      FatalErrorInFunction
          << "Unknown dispersion model type "
          << modelType << nl << nl
          << "Valid dispersion model types are:" << nl
          << dictionaryConstructorTablePtr_->sortedToc()
          << exit(FatalError);
  }

  return autoPtr<boyaoClass3>(cstrIter()());
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::boyaoClass3::~boyaoClass3()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

// void Foam::boyaoClass3::operator=(const boyaoClass3& rhs)
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
