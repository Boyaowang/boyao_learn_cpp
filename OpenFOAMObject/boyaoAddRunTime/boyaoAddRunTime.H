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
    Foam::boyaoAddRunTime

Description

SourceFiles
    boyaoAddRunTimeI.H
    boyaoAddRunTime.C
    boyaoAddRunTimeIO.C

\*---------------------------------------------------------------------------*/
#ifndef _boyaoAddRunTime_H
#define _boyaoAddRunTime_H

#include "boyaoClass3.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
// Forward declaration of classes
class Istream;
class Ostream;
class Time;

// namespace boyaoNameSpace
// {
// Forward declaration of friend functions and operators
class boyaoAddRunTime;
Istream& operator>>(Istream&, boyaoAddRunTime&);
Ostream& operator<<(Ostream&, const boyaoAddRunTime&);


/*---------------------------------------------------------------------------*\
                         Class boyaoAddRunTime Declaration
\*---------------------------------------------------------------------------*/

class boyaoAddRunTime
:
    public boyaoClass3
{
    // Private Data

        //- Description of data_
        label data_;


    // Private Member Functions


public:

  //- Runtime type information
TypeName("boyaoAddRunTime");



    // Static Data Members

        //- Static data staticData
        // static const label staticData;


    // Constructors

        //- Construct null
        boyaoAddRunTime();

        // //- Construct from components
        // boyaoAddRunTime(const label& data);
        //
        // //- Construct from Istream
        // boyaoAddRunTime(Istream&);
        //
        // //- Copy constructor
        // boyaoAddRunTime(const boyaoAddRunTime&);

        // - Disallow default bitwise copy construction
        boyaoAddRunTime(const boyaoAddRunTime&) = delete;


    // Selectors

        //- Select null constructed


    //- Destructor
    virtual ~boyaoAddRunTime();


    // Member Functions

        // Access

        // Check

        // Edit

        // Write


    // Member Operators

        //void operator=(const boyaoAddRunTime&);

        //- Disallow default bitwise assignment
        void operator=(const boyaoAddRunTime&) = delete;


    // Friend Functions

    // Friend Operators

    // IOstream Operators

        friend Istream& operator>>(Istream&, boyaoAddRunTime&);
        friend Ostream& operator<<(Ostream&, const boyaoAddRunTime&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// } // End namespace boyaoNameSpace
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// #include "boyaoAddRunTimeI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
