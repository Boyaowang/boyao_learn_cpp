#define Amac(z) \
word nameA = "A" + std::to_string(z); \
dimensionedScalar A \
(nameA,dimensionSet( 0, 0, -1, 0, 0, 0, 0), AList[z]);

#define Eamac(z) \
word nameEa = "Ea" + std::to_string(z); \
dimensionedScalar Ea \
(nameEa,dimensionSet(1, 2, -2, 0, -1, 0, 0), EaList[z]);

#define dhmac(z) \
word namedh = "dh" + std::to_string(z); \
dimensionedScalar dh \
(namedh,dimensionSet(0, 2, -2, 0, 0, 0, 0), dhList[z]);

Info<< "Reading reactionProperties\n" << endl;

IOdictionary reactionProperties
(
    IOobject
    (
        "reactionProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);


// dimensionedScalar E1
// (
//   "E1",
//   dimensionSet( 1, 2, -2, 0, -1, 0, 0),
//   152700.0
// );

// word EaListName = "Ea";
// auto EaList = dimListAppend(E1,reactionProperties,EaListName);
// Info << "The EaList is " << EaList[0] <<nl;
// List<dimensionedScalar> AList;
// List<dimensionedScalar> dhList;
List<scalar> EaList,AList,dhList;

label reactionNum = reactionProperties.size();
Info << "Number of reaction is " << reactionNum << nl;
word reactionName;

scalar Ea,A,dh;
forAll(reactionProperties, i)
{
  reactionName = "reaction" + std::to_string(i);

  reactionProperties.subDict(reactionName).lookup("Ea") >> Ea;
  reactionProperties.subDict(reactionName).lookup("A") >> A;
  reactionProperties.subDict(reactionName).lookup("dh") >> dh;

  EaList.append(Ea);
  AList.append(A);
  dhList.append(dh);
}



PtrList<dimensionedScalar> AListDim(reactionNum);
for (label i = 0; i < reactionNum; i++) {
  Amac(i)
  AListDim.set
  (
    i,
    new dimensionedScalar(A)
  );
}

PtrList<dimensionedScalar> EaListDim(reactionNum);
for (label i = 0; i < reactionNum; i++) {
  Eamac(i)
  EaListDim.set
  (
    i,
    new dimensionedScalar(Ea)
  );
}

PtrList<dimensionedScalar> dhListDim(reactionNum);
for (label i = 0; i < reactionNum; i++) {
  dhmac(i)
  dhListDim.set
  (
    i,
    new dimensionedScalar(dh)
  );
}

dimensionedScalar R
(
  "R",
  dimensionSet( 1, 2, -2, -1, -1, 0, 0),
  8.3145
);
