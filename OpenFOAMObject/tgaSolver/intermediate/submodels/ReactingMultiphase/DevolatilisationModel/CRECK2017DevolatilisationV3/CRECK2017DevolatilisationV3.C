/*---------------------------------------------------------------------------*\
=========                 |
\\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
\\    /   O peration     |
\\  /    A nd           | Copyright (C) 2011-2015 OpenFOAM Foundation
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

#include "CRECK2017DevolatilisationV3.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
Foam::CRECK2017DevolatilisationV3<CloudType>::CRECK2017DevolatilisationV3
(
  const dictionary& dict,
  CloudType& owner
)
:
DevolatilisationModel<CloudType>(dict, owner, typeName),
volatileData_(this->coeffDict().lookup("volatileData")),
solidMolarMass_(this->coeffDict().lookup("solidMolarMass")),
gasMolarMass_(this->coeffDict().lookup("gasMolarMass")),
volatileToGasMap_(volatileData_.size()),
residualCoeff_(readScalar(this->coeffDict().lookup("residualCoeff")))
{
  // read data from the constant/reactionProperties
  this->readReactionDict(owner.mesh());

  if (volatileData_.empty())
  {
    WarningInFunction
    << "Devolatilisation model selected, but no volatiles defined"
    << nl << endl;
  }
  else
  {
    Info<< "Participating volatile species:" << endl;

    // Determine mapping between active volatiles and cloud gas components
    const label idGas = owner.composition().idGas();
    forAll(volatileData_, i)
    {
      const word& specieName = volatileData_[i].name();
      const label id = owner.composition().localId(idGas, specieName);
      volatileToGasMap_[i] = id;

      Info<< "    " << specieName  << endl;
    }
  }

  if (solidMolarMass_.empty() || gasMolarMass_.empty() )
  {
    WarningInFunction
    << "Devolatilisation model selected, but no solid/gas molar mass defined"
    << nl << endl;
  }
  else
  {
    Info<< "Participating solid species:" << endl;

  // Determine mapping between active volatiles and cloud gas components
  //  const label idGas = owner.composition().idGas();
    forAll(solidMolarMass_, i)
    {
      const word& specieName1 = solidMolarMass_[i].name();
      const scalar MM = solidMolarMass_[i].W();

      Info<< "    " << specieName1  << "   "<< MM << endl;
    }

    forAll(gasMolarMass_, i)
    {
      const word& specieName1 = gasMolarMass_[i].name();
      const scalar MM = gasMolarMass_[i].W();

      Info<< "    " << specieName1  << "   "<< MM << endl;
    }
  }

}


template<class CloudType>
Foam::CRECK2017DevolatilisationV3<CloudType>::CRECK2017DevolatilisationV3
(
  const CRECK2017DevolatilisationV3<CloudType>& dm
)
:
DevolatilisationModel<CloudType>(dm),
volatileData_(dm.volatileData_),
solidMolarMass_(dm.solidMolarMass_),
gasMolarMass_(dm.gasMolarMass_),
volatileToGasMap_(dm.volatileToGasMap_),
residualCoeff_(dm.residualCoeff_)
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
Foam::CRECK2017DevolatilisationV3<CloudType>::~CRECK2017DevolatilisationV3()
{}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// Main calculatioon function

template<class CloudType>
void Foam::CRECK2017DevolatilisationV3<CloudType>::calculate
(
  const scalar dt,
  const scalar age,
  const scalar mass0,
  const scalar mass,
  const scalar T,
  const scalarField& YGasEff,
  const scalarField& YLiquidEff,
  const scalarField& YSolidEff,
  label& canCombust,
  scalarField& dMassDV,
  scalarField& dMassSOLID
) const
{

  //- Get id for wood char tar
  const label idGas = this->owner().composition().idGas();
  const label idSolid = this->owner().composition().idSolid();

  scalar dmassSolid = 0.0;
  scalar kappa = 0.0;
  scalar reactantMolarMass = 0.0;
  scalar productMolarMass = 0.0;
  word reactantName;

  for (label i = 0; i < reactionNum; i++)
  {
    reactantName = reactantsList[i];

    const label idReactants =
    this->owner().composition().localId(idSolid, reactantName);

    kappa = AList[i]*pow(T,bList[i])*exp(-EaList[i]*4184./(RR*T));

    dmassSolid = dt*kappa*mass*YSolidEff[idReactants];

    // readMolarMass
    forAll(solidMolarMass_,i)
    {
      if (solidMolarMass_[i].name() == reactantName) {
        reactantMolarMass = solidMolarMass_[i].W();
      }
    }

    // reactants reduce
    dMassSOLID[idReactants] += dmassSolid;

    // solid products
    forAll(solidStoiDatas_[i], j)
    {
      word productName = (solidStoiDatas_[i])[j].first();
      label productId =
      this->owner().composition().localId(idSolid, productName);

      // search product molar mass
      forAll(solidMolarMass_,i)
      {
        if (solidMolarMass_[i].name() == productName) {
          productMolarMass = solidMolarMass_[i].W();
        }
      }

      // calculate the increase of the product
      dMassSOLID[productId]-=
      (dmassSolid/reactantMolarMass)*solidStoiDatas_[i][j].second()
      *productMolarMass;
    }

    // gas products
    forAll(gasStoiDatas_[i], j)
    {
      word productName = (gasStoiDatas_[i])[j].first();
      label productId =
      this->owner().composition().localId(idGas, productName);

      // search product molar mass
      forAll(gasMolarMass_,i)
      {
        if (gasMolarMass_[i].name() == productName) {
          productMolarMass = gasMolarMass_[i].W();
        }
      }

      // calculate the increase of the product
      dMassDV[volatileToGasMap_[productId]]-=
      (dmassSolid/reactantMolarMass)*gasStoiDatas_[i][j].second()
      *productMolarMass;
    }

  }

};


// read reaction data from constant folder
template<class CloudType>
void Foam::CRECK2017DevolatilisationV3<CloudType>::readReactionDict
(
  const fvMesh& mesh
)
{

  IOdictionary reactionDict_
  (
    IOobject
    (
      "reactionProperties",
      mesh.time().constant(),
      mesh,
      IOobject::MUST_READ_IF_MODIFIED,
      IOobject::NO_WRITE
    )
  );

  reactionNum = reactionDict_.size();

  word reactionNameTest;

  forAll(reactionDict_,i)
  {

    reactionNameTest = "reaction" + std::to_string(i);

    // read solid phase stoichiomery
    List<Tuple2<word, scalar>> solidStoiData_
    (
      reactionDict_.subDict(reactionNameTest).lookup("solidProducts")
    );
    solidStoiDatas_.append(solidStoiData_);

    // read gas phase stoichiomery
    List<Tuple2<word, scalar>> gasStoiData_
    (
      reactionDict_.subDict(reactionNameTest).lookup("gasProducts")
    );
    gasStoiDatas_.append(gasStoiData_);

    // reaction rate coeff
    scalar Ea = 0.0, A = 0.0, b = 0.0;
    reactionDict_.subDict(reactionNameTest).lookup("Ea") >> Ea;
    reactionDict_.subDict(reactionNameTest).lookup("A") >> A;
    reactionDict_.subDict(reactionNameTest).lookup("b") >> b;
    EaList.append(Ea);
    AList.append(A);
    bList.append(b);

    // read reactants Names in each reactions
    word reactantsName;

    reactionDict_.subDict(reactionNameTest).lookup("reactants")
    >> reactantsName;

    reactantsList.append(reactantsName);
  }

}
// ************************************************************************* //
