// Solve the T equation
volScalarField Tdimless(T/dimensionedScalar("dim",T.dimensions(),scalar(1)));
volScalarField Cpw = 1500+Tdimless;
volScalarField Cpc = 420 + 2.0*Tdimless + 6.58*pow(10,-4)*pow(Tdimless,2);
volScalarField Cpt = -100 + 4.4*Tdimless + 1.57*pow(10,-3)*pow(Tdimless,2);
volScalarField Cpg = 770 + 0.629*Tdimless - 1.91*pow(10,-4)*pow(Tdimless,2);
Cpw.dimensions().reset(dimensionSet(0,2,-2,-1,0,0,0));
Cpc.dimensions().reset(dimensionSet(0,2,-2,-1,0,0,0));
Cpt.dimensions().reset(dimensionSet(0,2,-2,-1,0,0,0));
Cpg.dimensions().reset(dimensionSet(0,2,-2,-1,0,0,0));

dimensionedScalar rhoCpPlus
(
  "rhoCpPlus",
  dimensionSet( 1, -1, -2, -1, 0, 0, 0),
  0.001
);

dimensionedScalar rhoCpRPlus
(
  "rhoCpRPlus",
  dimensionSet( 1, 0, -2, -1, 0, 0, 0),
  ROOTVSMALL//ROOTVSMALL
);

volScalarField rhoCp = Cpw*(rhos+rhois)
                      +Cpc*rhoc
                      +eps*Cpt*(rhot1+rhot2)
                      +eps*Cpg*rhog;
// if(runTime.timeOutputValue()==runTime.deltaTValue())
// {
  // rhoCp+=rhoCpPlus;
// }
// Info << rhoCp << nl;
volScalarField DTr = lambda * r;
volVectorField gradT=fvc::grad(T);

// Info << "gradT is " << gradT.component(0) << nl;
volScalarField TrByR = lambda*gradT.component(0)/(r*rhoCp+rhoCpRPlus);

volScalarField lambdaByCptot = lambda/(rhoCp+rhoCpPlus);
// Info << "rhoCp" << rhoCp <<nl;

// forAll(r,i)
// {
//   TrByR[i] = TrByR[i]/r[i];
// }
volScalarField Q = (-(kList[1]*dhListDim[1]
                    +kList[0]*dhListDim[0]
                    +kList[2]*dhListDim[2])
                    *rhos-kList[3]*dhListDim[3]*rhois
                   -eps*(kList[4]*dhListDim[4]+kList[5]*dhListDim[5])
                   *rhot1)/(rhoCp+rhoCpPlus);

fvScalarMatrix TEqn
(
    fvm::ddt(T)  -TrByR-Q -fvm::laplacian(lambdaByCptot, T) //
 ==
    fvOptions(T)
);
    fvOptions.constrain(TEqn);
    TEqn.solve();
    fvOptions.correct(T);
