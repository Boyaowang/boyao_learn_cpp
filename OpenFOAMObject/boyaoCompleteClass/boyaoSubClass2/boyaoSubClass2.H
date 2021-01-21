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
    Foam::boyaoSubClass2

Description

SourceFiles
    boyaoSubClass2I.H
    boyaoSubClass2.C
    boyaoSubClass2IO.C

\*---------------------------------------------------------------------------*/

#ifndef _boyaoSubClass2_H
#define _boyaoSubClass2_H

#include "boyaoClass2.H"
#include "IOobject.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of classes
class Istream;
class Ostream;

// Forward declaration of friend functions and operators
class boyaoSubClass2;
Istream& operator>>(Istream&, boyaoSubClass2&);
Ostream& operator<<(Ostream&, const boyaoSubClass2&);


/*---------------------------------------------------------------------------*\
                         Class boyaoSubClass2 Declaration
\*---------------------------------------------------------------------------*/

class boyaoSubClass2
:
    public boyaoClass2
{
    // Private Data

        //- Description of data_
        label data_;


    // Private Member Functions


public:

    // Static Data Members

        //- Static data staticData
        static const label staticData;

        //- Runtime type information
        TypeName("boyaoSubClass2");


    // Constructors

        //- Construct null
        boyaoSubClass2();

        //- Construct from components
        boyaoSubClass2(const label& data);

        //- Construct from components
        boyaoSubClass2(const word& name);

        //- Construct from Istream
        boyaoSubClass2(Istream&);

        //- Copy constructor
        boyaoSubClass2(const boyaoSubClass2&);

        //- Disallow default bitwise copy construction
//        boyaoSubClass2(const boyaoSubClass2&) = delete;


    // Selectors

        //- Select null constructed
        static autoPtr<boyaoSubClass2> New();
        static autoPtr<boyaoClass2> New
        (
            const fvMesh& meshFile
        );


    //- Destructor
    virtual ~boyaoSubClass2();


    // Member Functions
    void printHelloWorld() {
      cout << "Hello world form boyaoSubClass2" << '\n';
    }

        // Access

        // Check

        // Edit

        // Write


    // Member Operators

        //void operator=(const boyaoSubClass2&);

        //- Disallow default bitwise assignment
//        void operator=(const boyaoSubClass2&) = delete;


    // Friend Functions

    // Friend Operators

    // IOstream Operators

        friend Istream& operator>>(Istream&, boyaoSubClass2&);
        friend Ostream& operator<<(Ostream&, const boyaoSubClass2&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "boyaoSubClass2I.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
