/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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

Application
    laplacianFoam

Description
    Solves a simple Laplace equation, e.g. for thermal diffusion in a solid.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "fvOptions.H"
#include "simpleControl.H"
#include "pisoControl.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// template <class T>
// List<T> dimListAppend(T& refType,IOdictionary &dict, word &name) {
//   List<T> dimList;
//   word reactionName;
//   forAll(dict, i)
//   {
//     reactionName = "reaction" + std::to_string(i);
//     dimensionedScalar dimScalar
//     (
//         dict.subDict(reactionName).lookup(name)
//     );
//     dimList.append(dimScalar);
//   }
//   return dimList;
// }
dimensionedScalar scalarConvert(dimensionSet dimS, scalar a, word name)
{
  dimensionedScalar aDim(name,dimS, a);
  return aDim;
}

int main(int argc, char *argv[])
{
    #include "setRootCaseLists.H"

    #include "createTime.H"
    #include "createMesh.H"

    simpleControl simple(mesh);

    #include "createFields.H"
    #include "createKFields.H"



    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nCalculating temperature distribution\n" << endl;

    while (runTime.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

        // #include "CourantNo.H"
        {
            #include "rhoSEqn.H"
            #include "rhoGEqn.H"
            #include "TEqn.H"
            #include "pEqn.H"
            #include "write.H"
        }

        runTime.write();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }
    // while (runTime.run())
    // {
    //     // #include "readDyMControls.H"
    //     // #include "CourantNo.H"
    //     //#include "setDeltaT.H"
    //
    //     runTime++;
    //
    //     Info<< "Time = " << runTime.timeName() << nl << endl;
    //
    //     {
    //       //#include "UEqn.H"
    //       #include "rhoSEqn.H"
    //       while (piso.correct())
    //       {
    //         #include "rhoGEqn.H"
    //         #include "TEqn.H"
    //         #include "pEqn.H"
    //         #include "write.H"
    //       }
    //     }
    //
    //     runTime.write();
    //
    //
    //     Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
    //     << "  ClockTime = " << runTime.elapsedClockTime() << " s"
    //     << nl << endl;
    //
    //   }
        // while (simple.loop(runTime))
        // {
        //   Info<< "Time = " << runTime.timeName() << nl << endl;
        //
        //   while (simple.correctNonOrthogonal())
        //   {
        //     fvScalarMatrix TEqn
        //     (
        //       fvm::ddt(T) - fvm::laplacian(DT, T)
        //       ==
        //       fvOptions(T)
        //     );
        //
        //     fvOptions.constrain(TEqn);
        //     TEqn.solve();
        //     fvOptions.correct(T);
        //   }
        //
        //   #include "write.H"
        //
        // }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
