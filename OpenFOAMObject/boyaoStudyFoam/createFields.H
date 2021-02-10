// Info<< "Reading field\n" << endl;
//
// word cloudName = "some";
//
// IOdictionary someProperties
// (
//     IOobject
//     (
//         cloudName + "Properties",
//         runTime.constant(),
//         mesh,
//         IOobject::MUST_READ_IF_MODIFIED,
//         IOobject::NO_WRITE
//     )
// );
//
// dictionary& somePropertiesDict = someProperties;
//
// Info << "runTime is " << someProperties.lookup("asdf") << nl;
//
// Info << "mesh.time() is " << someProperties.lookup("asdf") << nl;
//
// if (someProperties.isDict("thermoType")) {
//   Info << "thermoType is a sub-dict and it is " << nl;
//   const dictionary& thermoTypeDict(someProperties.subDict("thermoType"));
//   Info << thermoTypeDict << nl;
//   Info << thermoTypeDict.lookup("type") << nl;
//   if (thermoTypeDict.found("thermo")) {
//     Info << "the mixture is found" << nl;
//   }
// const word thermoTypeName
// (
//     word(thermoTypeDict.lookup("type")) + '<'
//   + word(thermoTypeDict.lookup("mixture")) + '<'
//   + word(thermoTypeDict.lookup("transport")) + '<'
//   + word(thermoTypeDict.lookup("thermo")) + '<'
//   + word(thermoTypeDict.lookup("equationOfState")) + '<'
//   + word(thermoTypeDict.lookup("specie")) + ">>,"
//   + word(thermoTypeDict.lookup("energy")) + ">>>"
// );
// Info << "the thermoTypeName is " << thermoTypeName << nl;
// }
//
// Info << "runTime.constant() " << runTime.constant() << nl;
//
// // volScalarField S
// // (
// //     IOobject
// //     (
// //         "S",
// //         runTime.timeName(),
// //         mesh,
// //         IOobject::MUST_READ,
// //         IOobject::AUTO_WRITE
// //     ),
// //     mesh
// // );

// IOdictionary someProperties
// (
//     IOobject
//     (
//         "boyao",
//         mesh,
//         runTime.constant(),
//         IOobject::MUST_READ_IF_MODIFIED,
//         IOobject::NO_WRITE
//     )
// );
//
// const dictionary somePropertiesDict = someProperties.subDict("boyaoClass1");
//
//     boyaoClass boyao("boyaow", runTime, somePropertiesDict);
boyaoSubClass boyaoSub("boyaoSub");
autoPtr<boyaoClass2> boyaoFirstSelector(boyaoClass2::New(mesh));

IOdictionary someProperties
(
    IOobject
    (
        "boyaoSubProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);

// List<word> boyaoSubPropertiesList
// (
//   someProperties.subDict("boyaoPropertiesList").toc()
// );


// forAll(boyaoSubPropertiesList,i)
// {
//   Info << boyaoSubPropertiesList[i] << nl;
// }
//
//Info << someProperties.subDict("boyaoPropertiesList") << nl;
Istream& boyaoInput = someProperties.subDict("testList").lookup("boyaoPropertiesList");
Istream& boyaoInput2 = someProperties.subDict("testList").lookup("boyaoPropertiesList2");
Info << someProperties.subDict("testList").lookup("boyaoPropertiesList") << nl;
//boyaoClass2 boyaoSubPropertiesList2 = boyaoInput;
List<boyaoClass2> boyaoSubPropertiesList3
 (
   boyaoInput
 );

boyaoClass2 testInput(boyaoInput2);
//dictionaryEntry boyaoInfo(dictionary::null, someProperties.subDict("boyaoPropertiesList"));
scalarField dMassDV(5, 0.0);

Info<< "\nReading field U\n" << endl;
volScalarField S
(
    // IOobject
    // (
    //     "S",
    //     runTime.timeName(),
    //     mesh,
    //     IOobject::MUST_READ,
    //     IOobject::AUTO_WRITE
    // ),
    boyaoSub.fieldIOobject("S",mesh),
    mesh
);

scalar negativeValue = -10.0045784568277456;
Info << "the magnitude of the negativeValue is " << mag(negativeValue) << nl;
