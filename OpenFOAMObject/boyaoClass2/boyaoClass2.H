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
    Foam::boyaoClass2

Description

SourceFiles
    boyaoClass2I.H
    boyaoClass2.C
    boyaoClass2IO.C

\*---------------------------------------------------------------------------*/
#ifndef _boyaoClass2_H
#define _boyaoClass2_H

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
class boyaoClass2;
Istream& operator>>(Istream&, boyaoClass2&);
Ostream& operator<<(Ostream&, const boyaoClass2&);


/*---------------------------------------------------------------------------*\
                         Class boyaoClass2 Declaration
\*---------------------------------------------------------------------------*/

class boyaoClass2
{
    // Private Data

        //- Description of data_
        label data_;


    // Private Member Functions


public:

  //- Runtime type information
TypeName("boyaoClass2");

//- Declare runtime constructor selection table
declareRunTimeSelectionTable
(
    autoPtr,
    boyaoClass2,
    dictionary,
    //(const word& name, const Time& runTime, const dictionary& dict),
    (const word& name),
    //(name, runTime, dict)
    (name)
);


    // Static Data Members

        //- Static data staticData
        static const label staticData;


    // Constructors

        //- Construct null
        boyaoClass2();

        //- Construct from components
        boyaoClass2(const label& data);

        //- Construct from Istream
        boyaoClass2(Istream&);

        //- Copy constructor
        boyaoClass2(const boyaoClass2&);

        //- Disallow default bitwise copy construction
        //boyaoClass2(const boyaoClass2&) = delete;


    // Selectors

        //- Select null constructed
        static autoPtr<boyaoClass2> New();


    //- Destructor
    virtual ~boyaoClass2();


    // Member Functions

        // Access

        // Check

        // Edit

        // Write


    // Member Operators

        void operator=(const boyaoClass2&);

        //- Disallow default bitwise assignment
        //void operator=(const boyaoClass2&) = delete;


    // Friend Functions

    // Friend Operators

    // IOstream Operators

        friend Istream& operator>>(Istream&, boyaoClass2&);
        friend Ostream& operator<<(Ostream&, const boyaoClass2&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "boyaoClass2I.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
