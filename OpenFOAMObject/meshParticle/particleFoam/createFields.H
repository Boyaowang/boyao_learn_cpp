Info<< "Reading field T\n" << endl;

volScalarField T
(
    IOobject
    (
        "T",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);


// volScalarField p
// (
//     IOobject
//     (
//         "p",
//         runTime.timeName(),
//         mesh,
//         IOobject::MUST_READ,
//         IOobject::AUTO_WRITE
//     ),
//     mesh
// );


// volScalarField rhois
// (
//     IOobject
//     (
//         "rhois",
//         runTime.timeName(),
//         mesh,
//         IOobject::MUST_READ,
//         IOobject::AUTO_WRITE
//     ),
//     mesh
// );
//
// volScalarField rhoc
// (
//     IOobject
//     (
//         "rhoc",
//         runTime.timeName(),
//         mesh,
//         IOobject::MUST_READ,
//         IOobject::AUTO_WRITE
//     ),
//     mesh
// );

Info<< "Reading transportProperties\n" << endl;

IOdictionary transportProperties
(
    IOobject
    (
        "transportProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);
// Stoi coeff
scalar a = 0.65, b = 0.35;

Info<< "Reading diffusivity DT\n" << endl;

dimensionedScalar lambda
(
    transportProperties.lookup("lambda")
);

// dimensionedScalar Cpw
// (
//     transportProperties.lookup("Cpw")
// );

dimensionedScalar rho
(
    transportProperties.lookup("rho")
);

dimensionedScalar mu
(
    transportProperties.lookup("mu")
);


dimensionedScalar rhos0
(
    transportProperties.lookup("rhos0")
);

dimensionedScalar Bw
(
    transportProperties.lookup("Bw")
);

dimensionedScalar Bc
(
    transportProperties.lookup("Bc")
);

volScalarField rhos
(
    IOobject
    (
        "rhos",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh//dimensionedScalar("rhos", dimensionSet(1,-3,0,0,0,0,0), 400)
);

// initialize the rhos field
volScalarField rhois
(
    IOobject
    (
        "rhois",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh//dimensionedScalar("rhos", dimensionSet(1,-3,0,0,0,0,0), 400)
);

// initialize the char density field
volScalarField rhoc
(
    IOobject
    (
        "rhoc",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh//dimensionedScalar("rhos", dimensionSet(1,-3,0,0,0,0,0), 400)
);

// initialize the rhot1 (primary tar) field
volScalarField rhot1
(
    IOobject
    (
        "rhot1",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh//dimensionedScalar("rhos", dimensionSet(1,-3,0,0,0,0,0), 400)
);

// initialize the rhot2 (secondary tar) field
volScalarField rhot2
(
    IOobject
    (
        "rhot2",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh//dimensionedScalar("rhos", dimensionSet(1,-3,0,0,0,0,0), 400)
);

// initialize the rhoAr field
volScalarField rhoAr
(
    IOobject
    (
        "rhoAr",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh//dimensionedScalar("rhos", dimensionSet(1,-3,0,0,0,0,0), 400)
);

// initialize the rhog field
volScalarField rhog
(
    IOobject
    (
        "rhog",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh//dimensionedScalar("rhos", dimensionSet(1,-3,0,0,0,0,0), 400)
);

scalar eps0;
transportProperties.lookup("eps0") >> eps0;


#include "createFvOptions.H"
