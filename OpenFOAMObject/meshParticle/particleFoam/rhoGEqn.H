#define drhoEq(name) \
volVectorField drho##name##Up = fvc::grad(rho##name * Up); \
volVectorField drho##name##Vp = fvc::grad(rho##name * Vp); \
volScalarField drho##name##Updz = drho##name##Up.component(1)/eps; \
volScalarField drho##name##Vpdr = drho##name##Vp.component(0)/eps;

#define createRhoEq(name) \
fvScalarMatrix rho##name##Eqn \
( \
    fvm::ddt(rho##name)  \
    -S##name \
 == \
    fvOptions(rho##name) \
); \
    fvOptions.constrain(rho##name##Eqn); \
    rho##name##Eqn.solve(); \
    fvOptions.correct(rho##name);

volScalarField eta = 1 - (rhos+rhois)/rhos0;
volScalarField B = (1-eta)*Bw + eta * Bc;
volVectorField dp = fvc::grad(p);
volScalarField dpdz = dp.component(1);
volScalarField dpdr = dp.component(0);
volScalarField Up = B/mu * dpdz;
volScalarField Vp = B/mu * dpdr;
volScalarField r = mesh.C().component(vector::X);
dimensionedScalar rPlus
(
  "rPlus",
  dimensionSet( 0, 1, 0, 0, 0, 0, 0),
  ROOTVSMALL//ROOTVSMALL
);

// if(runTime.timeOutputValue()==runTime.deltaTValue())
// {
  // r += rPlus;
// }


drhoEq(t1);drhoEq(t2);drhoEq(g);drhoEq(Ar);

//volVectorField drhot1Up = fvc::grad(rhot1*Up);
// volScalarField drhot1Updz = drhot1Up.component(1)/eps;
// volVectorField drhot1Vp = fvc::grad(rhot1*Vp);
// volScalarField drhot1Vpdr = drhot1Vp.component(0);

// Source terms
volScalarField Sg = (kList[0]*rhos + eps*kList[5]*a*rhot1)/eps;
volScalarField St1 = (kList[1]*rhos - eps*(kList[4]+kList[5])*rhot1)/eps;
volScalarField St2 = (eps*b*kList[5]*rhot1)/eps;

// Info << "rhot1*Vp/r " << kList[1] <<nl;

fvScalarMatrix rhoArEqn
(
    fvm::ddt(rhoAr) //+ drhoArUpdz + rhoAr*Vp/(r+rPlus) + drhoArVpdr
 ==
    fvOptions(rhoAr)
);
    fvOptions.constrain(rhoArEqn);
    rhoArEqn.solve();
    fvOptions.correct(rhoAr);


  createRhoEq(t1); createRhoEq(t2); createRhoEq(g);
