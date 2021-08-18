    if (runTime.writeTime())
    {
        volVectorField gradT(fvc::grad(T));
        volVectorField gradp(fvc::grad(p));

        volScalarField gradpx
        (
            IOobject
            (
                "gradpx",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            gradp.component(vector::X)
        );

        volScalarField gradTx
        (
            IOobject
            (
                "gradTx",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            gradT.component(vector::X)
        );

        volScalarField gradTy
        (
            IOobject
            (
                "gradTy",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            gradT.component(vector::Y)
        );

        volScalarField gradTz
        (
            IOobject
            (
                "gradTz",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            gradT.component(vector::Z)
        );

        // rhoCp().write();


        runTime.write();
    }
