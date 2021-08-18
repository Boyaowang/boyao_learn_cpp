// Solve the rho equation

// fvScalarMatrix rhosEqn
// (
//     fvm::ddt(rhos) - 0.005*rhos
//  ==
//     fvOptions(rhos)
// );
//     fvOptions.constrain(rhosEqn);
//     rhosEqn.solve();
//     fvOptions.correct(rhos);
// dimensionedScalar rhosInit
// (
//   "rPlus",
//   dimensionSet( 1, -3, 0, 0, 0, 0, 0),
//   400
// );

// dimensionedScalar ks
// (
//   "ks",
//   dimensionSet( 0, 0, -1, 0, 0, 0, 0),
//   2
// );



// dimensionedScalar A1
// (
//   "A1",
//   dimensionSet( 0, 0, -1, 0, 0, 0, 0),
//   4.83E+09
// );

//dimensionedScalar A1 = scalarConvert(dimensionSet( 0, 0, -1, 0, 0, 0, 0), AList[0], "A1");

volScalarField eps = 1-(rhos+rhois+rhoc)/rhos0*(1-eps0);

volScalarField ks = AListDim[0] * Foam::exp(-EaListDim[0]/(R*T));

PtrList<volScalarField> kList(reactionNum);
for (label i = 0; i < reactionNum; i++) {
  kList.set
  (
    i,
    new volScalarField(AListDim[i] * Foam::exp(-EaListDim[i]/(R*T)))
  );
};

// for (label i = 0; i < reactionNum; i++) {
//   volScalarField kTemp = AListDim[i] * Foam::exp(-EaListDim[i]/(R*T));
//   Info << "KTemp dimension" << kTemp.dimensions() << nl;
//   kList.append(kTemp);
// }

dimensionedScalar deltaTd
(
  "deltaTd",
  dimensionSet( 0, 0, 1, 0, 0, 0, 0),
  runTime.deltaTValue()
);
// solve solid density rhos
fvScalarMatrix rhosEqn
(
  fvm::ddt(rhos) + (kList[0]+kList[1]+kList[2])*rhos
  ==
  fvOptions(rhos)
);

fvOptions.constrain(rhosEqn);
rhosEqn.solve();
fvOptions.correct(rhos);
// solve intermediate solid density rhois
fvScalarMatrix rhoisEqn
(
  fvm::ddt(rhois) -kList[2]*rhos + kList[3]*rhois
  ==
  fvOptions(rhois)
);

fvOptions.constrain(rhoisEqn);
rhoisEqn.solve();
fvOptions.correct(rhois);
// solve char density rhoc
fvScalarMatrix rhocEqn
(
  fvm::ddt(rhoc) -kList[3]*rhois-eps*kList[4]*rhot1
  ==
  fvOptions(rhoc)
);
fvOptions.constrain(rhocEqn);
rhocEqn.solve();
fvOptions.correct(rhoc);

// rhos = rhos - rhos*ks*deltaTd;

// if (runTime.value()>0) {
//   Info << "Time is lager than 0 " << runTime.deltaTValue() << nl;
// }else if(runTime.value() == 0)
// {
//   Info << "Time is equal to zero" << nl;
// }
