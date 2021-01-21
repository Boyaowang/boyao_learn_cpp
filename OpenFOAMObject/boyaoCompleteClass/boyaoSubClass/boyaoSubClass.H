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
    Foam::boyaoSubClass

Description

SourceFiles
    boyaoSubClassI.H
    boyaoSubClass.C
    boyaoSubClassIO.C

\*---------------------------------------------------------------------------*/

#ifndef _boyaoSubClass_H
#define _boyaoSubClass_H

#include "boyaoClass2.H"
#include "IOobject.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of classes
class Istream;
class Ostream;

// Forward declaration of friend functions and operators
class boyaoSubClass;
Istream& operator>>(Istream&, boyaoSubClass&);
Ostream& operator<<(Ostream&, const boyaoSubClass&);


/*---------------------------------------------------------------------------*\
                         Class boyaoSubClass Declaration
\*---------------------------------------------------------------------------*/

class boyaoSubClass
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
        TypeName("boyaoSubClass");


    // Constructors

        //- Construct null
        boyaoSubClass();

        //- Construct from components
        boyaoSubClass(const label& data);

        //- Construct from components
        boyaoSubClass(const word& name);

        //- Construct from Istream
        boyaoSubClass(Istream&);

        //- Copy constructor
        boyaoSubClass(const boyaoSubClass&);

        //- Disallow default bitwise copy construction
//        boyaoSubClass(const boyaoSubClass&) = delete;


    // Selectors

        //- Select null constructed
        static autoPtr<boyaoSubClass> New();
        static autoPtr<boyaoClass2> New
        (
            const fvMesh& meshFile
        );


    //- Destructor
    virtual ~boyaoSubClass();


    // Member Functions
    void printHelloWorld() {
      cout << "Hello world form boyaoSubClass" << '\n';
    }

        // Access

        // Check

        // Edit

        // Write


    // Member Operators

        //void operator=(const boyaoSubClass&);

        //- Disallow default bitwise assignment
//        void operator=(const boyaoSubClass&) = delete;


    // Friend Functions

    // Friend Operators

    // IOstream Operators

        friend Istream& operator>>(Istream&, boyaoSubClass&);
        friend Ostream& operator<<(Ostream&, const boyaoSubClass&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "boyaoSubClassI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
