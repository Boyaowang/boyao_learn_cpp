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
#include "dictionaryEntry.H"
#include "IOstreams.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::boyaoClass2::boyaoClass2(Istream& is)
{
    // Check state of Istream
    is.check("Foam::boyaoClass2::boyaoClass2(Foam::Istream&)");
     dictionaryEntry boyaoInfo(dictionary::null, is);
//
Info << "call constructor with a input of Istream" << nl;
if (boyaoInfo.size() > 0)
{
     Info << "If loop success" << nl;
     label nComponents = boyaoInfo.size();
     names_.setSize(nComponents, "unknownSpecie");
     Y_.setSize(nComponents, 0.0);
     label cmptI = 0;

    for (auto it = boyaoInfo.begin(); it != boyaoInfo.end(); ++it) {
        Info << it().keyword() << nl;
        names_[cmptI] = it().keyword();
        Y_[cmptI] =  readScalar(boyaoInfo.lookup(names_[cmptI]));
        cmptI++;
    }


}

}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

Foam::Istream& Foam::operator>>(Istream& is, boyaoClass2& boyao)
{
    //Check state of Istream
    Info << "call this operatror" << nl;
    is.check
    (
        "Foam::Istream& Foam::operator>>(Foam::Istream&, Foam::boyaoClass2&)"
    );

     dictionaryEntry boyaoInfo(dictionary::null, is);

     if (boyaoInfo.size() > 0)
     {
       Info << "If loop success" << nl;
       label nComponents = boyaoInfo.size();
       boyao.names_.setSize(nComponents, "unknownSpecie");
       boyao.Y_.setSize(nComponents, 0.0);
       label cmptI = 0;

       for (auto it = boyaoInfo.begin(); it != boyaoInfo.end(); ++it) {
         Info << it().keyword() << nl;
         boyao.names_[cmptI] = it().keyword();
         boyao.Y_[cmptI] =  readScalar(boyaoInfo.lookup(boyao.names_[cmptI]));
         cmptI++;
       }


     }

    return is;
}


Foam::Ostream& Foam::operator<<(Ostream& os, const boyaoClass2& boyao)
{
    //Check state of Ostream
    os.check
    (
        "Foam::Ostream& Foam::operator<<(Foam::Ostream&, "
        "const Foam::boyaoClass2&)"
    );

    return os;
}


// ************************************************************************* //
