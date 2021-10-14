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

Class
    Foam::boyaoClass3

Description

SourceFiles
    boyaoClass3I.H
    boyaoClass3.C
    boyaoClass3IO.C

\*---------------------------------------------------------------------------*/
#ifndef _boyaoClass3_H
#define _boyaoClass3_H

#include "dictionary.H"
#include "typeInfo.H"
#include "autoPtr.H"
#include "Switch.H"
#include "runTimeSelectionTables.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
// Forward declaration of classes
class Istream;
class Ostream;
class Time;

// Forward declaration of friend functions and operators
class boyaoClass3;
Istream& operator>>(Istream&, boyaoClass3&);
Ostream& operator<<(Ostream&, const boyaoClass3&);


/*---------------------------------------------------------------------------*\
                         Class boyaoClass3 Declaration
\*---------------------------------------------------------------------------*/

class boyaoClass3
{
    // Private Data

        //- Description of data_
        label data_;


    // Private Member Functions


public:

  //- Runtime type information
TypeName("boyaoClass3");

//- Declare runtime constructor selection table
declareRunTimeSelectionTable
(
    autoPtr,
    boyaoClass3,
    dictionary,
    //(const word& name, const Time& runTime, const dictionary& dict),
    (),
    //(name, runTime, dict)
    ()
);
// declareRunTimeSelectionTable
// (
//     autoPtr,
//     functionObject,
//     dictionary,
//     (const word& name, const Time& runTime, const dictionary& dict),
//     (name, runTime, dict)
// );


    // Static Data Members

        //- Static data staticData
        static const label staticData;


    // Constructors

        //- Construct null
        boyaoClass3();

        //- Construct from components
        boyaoClass3(const label& data);

        //- Construct from Istream
        boyaoClass3(Istream&);

        //- Copy constructor
        boyaoClass3(const boyaoClass3&);

        //- Disallow default bitwise copy construction
        //boyaoClass3(const boyaoClass3&) = delete;


    // Selectors

        //- Select null constructed
        static autoPtr<boyaoClass3> New(const word modelName);


    //- Destructor
    virtual ~boyaoClass3();


    // Member Functions

    void helloBoyaoClass3() {
      Info << "hello world from boyaoClass3 " << nl;
    }

        // Access

        // Check

        // Edit

        // Write


    // Member Operators

        //void operator=(const boyaoClass3&);

        //- Disallow default bitwise assignment
        void operator=(const boyaoClass3&) = delete;


    // Friend Functions

    // Friend Operators

    // IOstream Operators

        friend Istream& operator>>(Istream&, boyaoClass3&);
        friend Ostream& operator<<(Ostream&, const boyaoClass3&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "boyaoClass3I.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
