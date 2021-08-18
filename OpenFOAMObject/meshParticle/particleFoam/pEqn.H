volScalarField pCoeff = B*p/(mu*eps);
dimensionedScalar Mt2
(
  "Mt2",
  dimensionSet( 1, 0, 0, 0, -1, 0, 0),
  0.11
);
dimensionedScalar Mg
(
  "Mg",
  dimensionSet( 1, 0, 0, 0, -1, 0, 0),
  0.038
);

fvScalarMatrix pEqn
(
    fvm::ddt(p)-fvm::laplacian(pCoeff,p)
               -pCoeff*dpdr/(r+rPlus)
               -R*T/(eps*Mt2)*St2
               -R*T/(eps*Mg)*Sg
 ==
    fvOptions(p)
);
    fvOptions.constrain(pEqn);
    pEqn.solve();
    fvOptions.correct(p);
