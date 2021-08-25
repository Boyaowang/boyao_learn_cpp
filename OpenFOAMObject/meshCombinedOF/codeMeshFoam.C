#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "fvCFD.H"
// #include <iostream>
// #include <matrix2.h>

// C function declarations
#ifdef __cplusplus
extern "C"{
  #endif

  #include "matrix2.h"

  #ifdef __cplusplus
}
#endif

/* VERSION: discretized version */

/* constants */
#define SIGMA 5.670400e-8
// #define M_PI 3.141592653589793

/* molar masses */
#define M_C 12.011e-3			/* kg/mol */
#define M_O 15.999e-3			/* kg/mol */
#define M_H 1.008e-3			/* kg/mol */
#define M_H2O 18.01528e-3		/* kg/mol */
#define M_O2 (2.0*M_O)			/* kg/mol */
#define M_H2 (2.0*M_H)			/* kg/mol */
#define M_N2 (2.0*14.007e-3)	/* kg/mol */
#define M_CO2 (M_C + M_O2)		/* kg/mol */
#define M_CO (M_C + M_O)		/* kg/mol */
#define M_CH4 (M_C + 4.0*M_H)	/* kg/mol */


/* material data */
// #define MOISTURE_FRACTION_DB_ (6./94.) /* dry basis */
// #define MOISTURE_FRACTION_WB (MOISTURE_FRACTION_DB_/(1.0 + MOISTURE_FRACTION_DB_)) /* wet basis */
#define ASH_MASS_FRACTION 0.02 //0.0025
#define C_FRACTION 0.4941// daf in raw biomss the C H O ratios are from Neves review paper 2011 PECS (poplar wood), char is only C.
#define H_FRACTION 0.0609// daf in raw biomss
#define O_FRACTION 0.4353// daf in raw biomss

// #define DRYING_SHRINKAGE_VOLUME_ 0.1
#define DEVOL_SHRINKAGE_VOLUME 0.28
#define CHARCONVERSION_SHRINKAGE_VOLUME 0.95//0,95
// #define PARTICLE_RADIUS_ (9.5e-3/2.0) /* (m) */
// #define T_REACTOR_ 2150.0 /* (K) */
// #define T_RADIATION_ 1276.0 /* (K) */
#define P_ATM 101325.0 /* (Pa) */

/* case specific */
// #define MASS_FRAC_O2_ 0.23 //0.2 //0.0
#define MASS_FRAC_H2O 0.0
#define MASS_FRAC_H2 0.0
#define MASS_FRAC_CO2 0.0

/* model parameters */
#define MY_QUITE_SMALL 1.0e-3
#define MY_VERY_SMALL 1.0e-6
// #define MY_EXTREMELY_SMALL 1.0e-12
#define MY_EXTREMELY_SMALL 1.0e-20
#define MY_QUITE_LARGE 1.0e3
#define MY_VERY_LARGE 1.0e6
#define MY_MAXIMUM_NEWTON_ITER 500
#define T_P_INIT 300.0

/* drying kinetics parameters */
#define DryKinA 5.13e10/* (s-1) */
#define DryKinE 88000. /* (J/mol) */


/* static library variables */
#define N_SPECIES 12
static scalar LHV[N_SPECIES];
static scalar M[N_SPECIES-1]; /* no value for volatiles */

/* static interpolation lists */
static scalar X_list[50];
static scalar Y_list[50];

/* static message passing */
static scalar T_send[3];

/* model settings */
static scalar emissivity = 0.85; /* 0.86 URL ref in MatLab code - 0.8 char (Sven) - Lu et al. (2008) Energy & Fuels 22 says 0.95 */
// static scalar emissivityBiomass = 0.85; /*Lu, Hong PhD 2006 BYU*/
// static scalar emissivityChar = 0.95; /*Lu, Hong PhD 2006 BYU*/
// static scalar emissivityAsh = 0.7; /*Lu, Hong PhD 2006 BYU*/
static scalar view_factor = 1.;
static scalar m_init;
static scalar r_init;
static scalar L1, L2, L3;
static scalar particle_volume0;

/* read some parameters from file */
static label VERBOSITY_, SAVE_EVERY_, FINE_PARTICLE_MESH_;
static scalar TIME_DT_, TIME_TOTAL_, PARTICLE_RADIUS_, T_REACTOR_,
T_RADIATION_, MASS_FRAC_O2_, DENSITY_INITIAL_, MOISTURE_FRACTION_DB_,
MOISTURE_FRACTION_WB, FINE_PARTICLE_MESH_DOUBLE_, DRYING_SHRINKAGE_VOLUME_,
ASH_MASS_FRACTION_DB, K_P_WET_, K_P_DRY_, K_P_CHAR_/*DRY_DENSITY*/;
static scalar DevKinA1_, DevKinE1_, DevKinA2_, DevKinE2_, DevKinA3_, DevKinE3_;

clock_t start;


#define MESHINPUT particleInfoDict_.subDict("meshInput").lookup
#define SIGDEVKIN particleInfoDict_.subDict("sigDevKin").lookup

void readMeshInput(const dictionary& particleInfoDict_)
{
  MESHINPUT("VERBOSITY")>> VERBOSITY_;
  MESHINPUT("SAVE_EVERY")>> SAVE_EVERY_;
  MESHINPUT("TIME_DT")>> TIME_DT_;
  MESHINPUT("TIME_TOTAL")>> TIME_TOTAL_;
  MESHINPUT("MOISTURE_FRACTION_DB")>> MOISTURE_FRACTION_DB_;
  MESHINPUT("PARTICLE_RADIUS")>> PARTICLE_RADIUS_;
  MESHINPUT("DRYING_SHRINKAGE_VOLUME")>> DRYING_SHRINKAGE_VOLUME_;
  MESHINPUT("T_REACTOR")>> T_REACTOR_;
  MESHINPUT("T_RADIATION")>> T_RADIATION_;
  MESHINPUT("MASS_FRAC_O2")>> MASS_FRAC_O2_;
  MESHINPUT("DENSITY_INITIAL")>> DENSITY_INITIAL_;
  MESHINPUT("FINE_PARTICLE_MESH")>> FINE_PARTICLE_MESH_;
  MESHINPUT("FINE_PARTICLE_MESH_DOUBLE")>> FINE_PARTICLE_MESH_DOUBLE_;
  MESHINPUT("K_P_WET")>> K_P_WET_;
  MESHINPUT("K_P_DRY")>> K_P_DRY_;
  MESHINPUT("K_P_CHAR")>> K_P_CHAR_;
}

void readDevKin(const dictionary& particleInfoDict_)
{
  SIGDEVKIN("DevKinA1")>>DevKinA1_;
  SIGDEVKIN("DevKinE1")>>DevKinE1_;
  SIGDEVKIN("DevKinA2")>>DevKinA2_;
  SIGDEVKIN("DevKinE2")>>DevKinE2_;
  SIGDEVKIN("DevKinA3")>>DevKinA3_;
  SIGDEVKIN("DevKinE3")>>DevKinE3_;
}

void readCoeff(const Time & time) {
  IOdictionary particleInfoDict_
  (
    IOobject
    (
      "particleInfoDict",
      "constant",
      time,
      IOobject::MUST_READ_IF_MODIFIED,
      IOobject::NO_WRITE
    )
  );
  Info << particleInfoDict_ << nl;
  readMeshInput(particleInfoDict_);
  readDevKin(particleInfoDict_);

  MOISTURE_FRACTION_WB =MOISTURE_FRACTION_DB_/(1.0 + MOISTURE_FRACTION_DB_);
  ASH_MASS_FRACTION_DB = ASH_MASS_FRACTION/(1.0-MOISTURE_FRACTION_WB);
}


/* model indices */
enum{layer_1,layer_2,layer_3,layer_4};
enum{boundary_1,boundary_2,boundary_3,boundary_4};
enum{drying_front,devol_front,char_front,char_produced};
enum{evaporation,devolatilization,char_combustion};
enum{cylinder,sphere,parallelepiped};

/* property indices */
enum{index_CO2,index_H2,index_CO,index_H2O,index_CH4,index_C2H4,
  index_C10H8,index_C,index_C2H6,index_C3H8,index_C6H6O,index_volatiles};

  /* Redux statics */
  label material, shape;

  /* Same listing as species listing in mixture template in Fluent */
  enum{H2O_index,O2_index,CH4_index,H2_index,CO_index,CO2_index,N2_index};

  /* functions */
  /* ======================================================================== */
  #include "memberFunctions.H"


  /* fully discretized */
  void discretized_psm(void)
  {
    label i, j, iter_count, output_every;
    scalar t, t_stop;
    VEC *b, *T;
    MAT *A, *LU;
    PERM *pivot;
    scalar xi[4][FINE_PARTICLE_MESH_];
    scalar V_cell[FINE_PARTICLE_MESH_],V_char_last[FINE_PARTICLE_MESH_],V_char[FINE_PARTICLE_MESH_];
    scalar xc[FINE_PARTICLE_MESH_];
    scalar aw, ae, ap, ap0,Su_b,Sp_b;
    scalar Sp[FINE_PARTICLE_MESH_];
    scalar Su[FINE_PARTICLE_MESH_];
    scalar dt;
    scalar T_outer_boundary;
    FILE *fp;
    scalar Tf, Af;
    scalar xif[4];
    scalar rb, T_inf;
    scalar S, Q, q, a, d, e, delta_0, delta_1;
    scalar rho_g, mu, cp_g, k_g, vel_mag, h;
    //     scalar xi_t[4];
    scalar omega_c[FINE_PARTICLE_MESH_];
    scalar Q_reaction[3][FINE_PARTICLE_MESH_];
    scalar R_b[4][FINE_PARTICLE_MESH_];
    scalar R_char_reac[4][FINE_PARTICLE_MESH_];
    //     scalar R_char_reac1[FINE_PARTICLE_MESH_], R_char_reac2[FINE_PARTICLE_MESH_], R_char_reac3[FINE_PARTICLE_MESH_], R_char_reac4[FINE_PARTICLE_MESH_];
    scalar R_char_reac1S;//, R_char_reac2S, R_char_reac3S, R_char_reac4S;
    scalar m[4][FINE_PARTICLE_MESH_],m_last[4][FINE_PARTICLE_MESH_];
    //     scalar m_t[4];
    scalar total_mass;
    scalar S_star[FINE_PARTICLE_MESH_], dSdT_star[FINE_PARTICLE_MESH_];
    scalar char_from_devol[FINE_PARTICLE_MESH_];
    scalar total_devol[FINE_PARTICLE_MESH_];
    scalar R_product[7];
    scalar Q_equilibrate[3][FINE_PARTICLE_MESH_];
    //     scalar delta_V[FINE_PARTICLE_MESH_];
    scalar R_devol_reac[3][FINE_PARTICLE_MESH_];
    // scalar conc_CO2, conc_H2O, conc_H2;
    // scalar Y_H2=0.0, Y_CO=0.0,Y_CH4=0.0,Y_G=0.0, Y_CO2=0.0;//Y_H2O=0.0,
    scalar char_yield[FINE_PARTICLE_MESH_];
    scalar beta_r[4];
    scalar D_g, D_gAB;
    scalar hmi=0.0, hmia, beta_d, /*eta, conc,*/ alpha=0.0, conc_O2, conc_O2_correct, O2_diff_suface=0.0 ,omega_cS;
    scalar high=0.0, low=0.0;
    scalar dmdt[4][FINE_PARTICLE_MESH_];
    scalar volume_sum;
    label /*allow_combustion[FINE_PARTICLE_MESH_],*/ combustion_flag,combustion_layer;
    //     scalar heatFraction = 1.0; //the ratio between the heat absorbed by char to the total heat relased by char conversion
    //     scalar R_H2_Sum[FINE_PARTICLE_MESH_];
    scalar R_O2_mole_need = 0.;
    scalar R_O2_mole_need_list[FINE_PARTICLE_MESH_];

    // for source
    scalar R_drySourceimins1High, R_drySourceiHigh, R_devoSourceimins1High, R_devoSourceiHigh,R_devoSourceimins1HighChar, R_devoSourceiHighChar, R_drySourceimins1Low, R_drySourceiLow, R_devoSourceimins1Low, R_devoSourceiLow, R_devoSourceimins1LowChar, R_devoSourceiLowChar, density_drywood;

    scalar charFrontRaduis;
    scalar ThermalTimeScale[FINE_PARTICLE_MESH_];
    fp = fopen("codeMeshOutput.txt","w");


    /* ================================================= */

    /* Assemble matrix system */
    A = m_get(FINE_PARTICLE_MESH_,FINE_PARTICLE_MESH_);
    T = v_get(FINE_PARTICLE_MESH_);
    b = v_get(FINE_PARTICLE_MESH_);
    /* 	ap*Tp = aw*Tw + ae*Te + ap0*Tp0 + Su
    *        ap = ap0 + aw + aE - Sp
    *        ap0 = rho*cp*deltax/deltat
    *        aw = kw/deltax_wp
    *        ae = ke/deltax_pe
    *        b = S*deltax = Su + Sp*Tp		*/
    /* --- formulated as a matrix problem:
    *        aw*Tw - ap*Tp + ae*Te = - ap0*Tp0 - Su	*/

    /* Set some parameters */
    dt = TIME_DT_;
    output_every = SAVE_EVERY_;//((label) (1.0/dt));
    t_stop = TIME_TOTAL_;

    /* Initialize variables */
    t = 0.0;
    v_zero(T);
    iter_count = 0;
    rb = PARTICLE_RADIUS_;

    /*Print out KP*/
    printf("K_P_WET_: %f\n", K_P_WET_);
    printf("K_P_DRY_: %f\n", K_P_DRY_);
    printf("K_P_CHAR_: %f\n", K_P_CHAR_);

    /* Initialize fields */
    if (VERBOSITY_) { printf("Init T:\n"); }
    for (i = 1; i <= FINE_PARTICLE_MESH_; i++)
    {
      T->ve[i-1] = T_P_INIT;
      if (VERBOSITY_) { printf("%i: %f ",i,T->ve[i-1]); }
    }
    T_outer_boundary = T_P_INIT;
    if (VERBOSITY_) { printf("\n"); }

    /* Particle is meshed from the outside in */
    if (VERBOSITY_) { printf("Particle mesh:\n"); }
    volume_sum = 0.5*volume_of_element(0.0,rb)/FINE_PARTICLE_MESH_DOUBLE_;
    for (j = FINE_PARTICLE_MESH_; j >= 1; j--)
    {
      xc[j-1] = radius_from_volume(volume_sum);
      volume_sum = volume_sum +
      volume_of_element(0.0,rb)/FINE_PARTICLE_MESH_DOUBLE_;
      if (VERBOSITY_) { printf("%i: %e - ",j,xc[j-1]); }
      char_from_devol[j-1] = 0.0;
      total_devol[j-1] = 0.0;

    }
    if (VERBOSITY_) { printf("\n"); }

    total_mass = 0.0;
    for (i = 1; i <= 4; i++)
    {
      for (j = 1; j <= FINE_PARTICLE_MESH_; j++)
      {
        if (i == 1)
        {
          xi[i-1][j-1] = 1.0;
        }
        else
        {
          xi[i-1][j-1] = 0.0;
        }

        m[i-1][j-1] = xi[i-1][j-1]*rho(i-1,T->ve[i-1])*volume_of_element(0.0,rb)/FINE_PARTICLE_MESH_DOUBLE_;
        // printf("x %e ",xi[i-1][j-1]);
        // printf("m %e ",m[i-1][j-1]);
        total_mass = total_mass + m[i-1][j-1];
      }
    }


    printf("\n");

    /* Set gas phase data at the reactor temperature */
    T_inf = T_REACTOR_;
    rho_g = (3.550951e2*Foam::pow(T_inf,-1.000866));
    mu = 1.716e-5*Foam::pow((T_inf/273.11),3./2.)*(273.11+110.56)/(T_inf+110.56);
    cp_g = 1.0e3*((-0.000000000153767)*Foam::pow(T_inf,3.0)
    + 0.000000363209494*Foam::pow(T_inf,2.0)
    + (-0.000051486068111)*T_inf + 1.009174922600606);	/* polyfit from table data for N2 on the interval 500 - 1300 K */
    k_g = (-0.000000000003493)*Foam::pow(T_inf,3.0)
    + 0.000000003319264*Foam::pow(T_inf,2.0)
    + 0.000060059499759*T_inf + 0.008533051948052; /* polyfit from table data for N2 on the interval 500 - 1300 K */
    if (VERBOSITY_)
    {
      printf("Gas phase data to use at T = %f\n",T_inf);
      printf("  rho  = %e\n",rho_g);
      printf("  mu   = %e\n",mu);
      printf("  cp_g = %e\n",cp_g);
      printf("  k_g  = %e\n",k_g);
    }
    vel_mag = 0.5;	/* (m/s) */


    conc_O2 = MASS_FRAC_O2_*(M_O2/M_N2)*P_ATM/(8.3145*T_inf); /* molar concentration of O2 in the gas phase */
    // conc_CO2 = MASS_FRAC_CO2*(M_CO2/M_N2)*P_ATM/(8.3145*T_inf); /* molar concentration of CO2 in the gas phase */
    // conc_H2O = MASS_FRAC_H2O*(M_H2O/M_N2)*P_ATM/(8.3145*T_inf); /* molar concentration of H2O in the gas phase */
    // conc_H2 = MASS_FRAC_H2*(M_H2/M_N2)*P_ATM/(8.3145*T_inf); /* molar concentration of H2 in the gas phase */

    /*NOT USED IN THIS CODE!!!!*/
    /* Devolatilization product distribution */
    /* NEW TAKE 2016-10-10 - use Neves data at 900C */
    // Y_H2 = 0.015; /* (kg H2/kg daf fuel) */
    // Y_CO = 0.3; /* (kg CO/kg daf fuel) */
    // Y_CH4 = 0.05;   /* (kg CH4/kg daf fuel) */
    // Y_CO2 = 0.1; /* (kg CO2/kg daf fuel) */
    // Y_G = 0.55;
    // Y_H2O = Y_G - (Y_H2 + Y_CO + Y_CH4 + Y_CO2); /* (kg CO2/kg daf fuel) */


    for (j = FINE_PARTICLE_MESH_; j >= 1; j--)
    {
      V_cell[j-1] = volume_of_element(0.0,rb)/FINE_PARTICLE_MESH_DOUBLE_;
      V_char[j-1] = 0.0;
      V_char_last[j-1] = 0.0;
      for (i = 1; i <= 4; i++)
      {
        m_last[i-1][j-1] = m[i-1][j-1];
      }
      if (j==1)
      {

        ThermalTimeScale[j-1] =Foam::pow(rb-xc[0],2.0)
        /(k_p(layer_1,T->ve[j-1])/(c_p(layer_1,T->ve[j-1])
        *rho(layer_1,T->ve[j-1])));
      }
      else
      {
        ThermalTimeScale[j-1] =Foam::pow(xc[j-2]-xc[j-1],2.0)
        /(k_p(layer_1,T->ve[j-1])/(c_p(layer_1,T->ve[j-1])
        *rho(layer_1,T->ve[j-1])));
      }
    }

    density_drywood = DENSITY_INITIAL_*(1.0 - MOISTURE_FRACTION_WB)/(1.0-DRYING_SHRINKAGE_VOLUME_);
    combustion_layer = 99999999;

    fprintf(fp,"time %e ",t);
    fprintf(fp,"temperatures ");


    for (i = 1; i <= FINE_PARTICLE_MESH_; i++)
    {
      fprintf(fp,"%e ",T->ve[i-1]);

    }
    fprintf(fp,"%e ",T_outer_boundary);


    for (j = 1; j <= 4; j++)
    {
      fprintf(fp,"masses ");
      for (i = 1; i <= FINE_PARTICLE_MESH_; i++)
      {
        for (j = 1; j <= 4; j++)
        {
          fprintf(fp,"%e ",m[j-1][i-1]);
        }
      }
      fprintf(fp,"radius %e ",rb);
    }
    fprintf(fp,"R_b ");
    for (i = 1; i <= FINE_PARTICLE_MESH_; i++)
    {
      for (j = 1; j <= 4; j++)
      {
        fprintf(fp,"%e ",R_b[j-1][i-1]);
      }
    }
    fprintf(fp,"Thermal_time ");
    for (i = 1; i <= FINE_PARTICLE_MESH_; i++)
    {
      fprintf(fp,"%e ",ThermalTimeScale[i-1]);
    }
    fprintf(fp,"\n");

    while (t < t_stop)
    {

      /* Initialize matrix system */
      m_zero(A);
      v_zero(b);

      /* Update particle properties including particle volume */
      /* --------------------------------------------------------------------- */
      for (i = 1; i <= 4; i++)
      {
        for (j = 1; j <= FINE_PARTICLE_MESH_; j ++)
        {
          xi[i-1][j-1] = m[i-1][j-1]/(m[layer_1][j-1] + m[layer_2][j-1] + m[layer_3][j-1] + m[layer_4][j-1]);
        }
      }
      for (j = 1; j <= FINE_PARTICLE_MESH_; j ++)
      {
        V_cell[j-1] = V_cell[j-1] - DRYING_SHRINKAGE_VOLUME_*(m_last[layer_1][j-1] - m[layer_1][j-1])/DENSITY_INITIAL_ - DEVOL_SHRINKAGE_VOLUME*(m_last[layer_2][j-1] - (m[layer_2][j-1] - (m_last[layer_1][j-1] - m[layer_1][j-1])*(1.0 - MOISTURE_FRACTION_WB)))/density_drywood;
        V_char[j-1] = V_char[j-1] + (1.0 - DEVOL_SHRINKAGE_VOLUME)*(m_last[layer_2][j-1] - (m[layer_2][j-1] - (m_last[layer_1][j-1] - m[layer_1][j-1])*(1.0 - MOISTURE_FRACTION_WB)))/density_drywood;
      }

      if (combustion_layer != 99999999 && combustion_layer != 0)
      {
        V_cell[combustion_layer] = V_cell[combustion_layer]-CHARCONVERSION_SHRINKAGE_VOLUME*R_b[char_front][combustion_layer]*dt/(m_last[layer_3][combustion_layer]/V_char_last[combustion_layer]);
        V_char[combustion_layer] = V_char[combustion_layer] - R_b[char_front][combustion_layer]*dt/(m_last[layer_3][combustion_layer]/V_char_last[combustion_layer]);
      }

      for (j = 1; j <= FINE_PARTICLE_MESH_; j ++)
      {
        for (i = 1; i <= 4; i++)
        {
          V_char_last[j-1] = V_char[j-1];
          m_last[i-1][j-1] = m[i-1][j-1];
        }
      }

      volume_sum = 0.5*V_cell[FINE_PARTICLE_MESH_-1];

      for (j = FINE_PARTICLE_MESH_; j >= 2; j--)
      {
        xc[j-1] = radius_from_volume(volume_sum);

        volume_sum = volume_sum + 0.5*V_cell[j-1] + 0.5*V_cell[j-2];
      }
      xc[0] = radius_from_volume(volume_sum);
      volume_sum = volume_sum + 0.5*V_cell[0];
      rb = radius_from_volume(volume_sum);
      volume_sum = 0.0;


      /* --------------------------------------------------------------------- */
      /* Update reaction rates and heats of reaction based on current T */
      /* --------------------------------------------------------------------- */
      R_product[H2O_index] = 0.0;
      R_product[H2_index] = 0.0;
      R_product[CO_index] = 0.0;
      R_product[CH4_index] = 0.0;
      R_product[H2O_index] = 0.0;
      R_product[CO2_index] = 0.0;
      R_O2_mole_need = 0.0;

      combustion_flag = 0;
      combustion_layer = 99999999;
      /*Drying, Devolatilization and Char conversion*/
      for (i = FINE_PARTICLE_MESH_; i >= 1; i--)
      {
        /* Drying */
        // 			R_b[drying_front][i-1] = m[layer_1][i-1]*1.0e27*exp(-25000.0/T->ve[i-1]); /* J/s / J/kg = kg/s */
        R_b[drying_front][i-1] = m[layer_1][i-1]*MOISTURE_FRACTION_WB*DryKinA*Foam::exp(-DryKinE/(8.3145*T->ve[i-1])); /* J/s / J/kg = kg/s */
        if (m[layer_1][i-1] - R_b[drying_front][i-1]/MOISTURE_FRACTION_WB*dt <= MY_EXTREMELY_SMALL)
        {
          R_b[drying_front][i-1] = m[layer_1][i-1]*MOISTURE_FRACTION_WB/dt;
        }
        Q_reaction[evaporation][i-1] = deltaHvap(T->ve[i-1])*R_b[drying_front][i-1]; /* (J/kg)*(kg/s) = W */
        Q_equilibrate[drying_front][i-1] = R_b[drying_front][i-1]*gas_cp(index_H2O, 0.5*(T->ve[i-1]+T_outer_boundary))*(T_outer_boundary-T->ve[i-1]); /* (W) */
        R_product[H2O_index] = R_product[H2O_index] + R_b[drying_front][i-1]; /* (kg/s) */


        R_devol_reac[1-1][i-1] = DevKinA1_*Foam::exp(-DevKinE1_/(8.3145*T->ve[i-1]))*m[layer_2][i-1];
        R_devol_reac[2-1][i-1] = DevKinA2_*Foam::exp(-DevKinE2_/(8.3145*T->ve[i-1]))*m[layer_2][i-1];
        R_devol_reac[3-1][i-1] = DevKinA3_*Foam::exp(-DevKinE3_/(8.3145*T->ve[i-1]))*m[layer_2][i-1];


        R_b[devol_front][i-1] = R_devol_reac[1-1][i-1] + R_devol_reac[2-1][i-1] + R_devol_reac[3-1][i-1]; /* (kg/s) */
        R_b[char_produced][i-1] = R_devol_reac[3-1][i-1]; /* (kg/s) */
        Q_reaction[devolatilization][i-1] = 0.0*R_b[devol_front][i-1]; /* heat of devolatilization is equal to ZERO */
        Q_equilibrate[devol_front][i-1] = (R_devol_reac[1-1][i-1] + R_devol_reac[2-1][i-1])*cp_g*(T_outer_boundary-T->ve[i-1]); /* (W) */
        char_from_devol[i-1] = char_from_devol[i-1] + R_b[char_produced][i-1]*dt;
        total_devol[i-1] = total_devol[i-1] + R_b[devol_front][i-1]*dt;

        //             R_H2_Sum[i-1] = R_product[H2_index];
        R_O2_mole_need_list[i-1] = R_O2_mole_need;
        //             R_product[H2_index] = R_product[H2_index] + Y_H2/Y_G*(R_devol_reac[1-1][i-1] + R_devol_reac[2-1][i-1]); /* (kg/s) */
        R_O2_mole_need = R_O2_mole_need + (R_b[devol_front][i-1]*C_FRACTION-R_devol_reac[3-1][i-1])/M_C+R_b[devol_front][i-1]*H_FRACTION/M_H/4.- R_b[devol_front][i-1]*O_FRACTION/M_O/2.;//assume volatile gas is fully consumed by O2
        /* (mol/s) */
        //             R_product[CO_index] = R_product[CO_index] + Y_CO/Y_G*(R_devol_reac[1-1][i-1] + R_devol_reac[2-1][i-1]); /* (kg/s) */
        //             R_product[CH4_index] = R_product[CH4_index] + Y_CH4/Y_G*(R_devol_reac[1-1][i-1] + R_devol_reac[2-1][i-1]); /* (kg/s) */
        //             R_product[H2O_index] = R_product[H2O_index] + Y_H2O/Y_G*(R_devol_reac[1-1][i-1] + R_devol_reac[2-1][i-1]); /* (kg/s) */
        //             R_product[CO2_index] = R_product[CO2_index] + Y_CO2/Y_G*(R_devol_reac[1-1][i-1] + R_devol_reac[2-1][i-1]); /* (kg/s) */

        if (combustion_flag==0)
        {
          //get the char front location
          charFrontRaduis = charFrontLocation (rb, (i-1),V_cell,V_char,xc,xi[layer_3][0]);

          /*make sure only one char layer is converted, char will not start converting before dry wood is fully converted(in that layer)*/
          if (i == 1 && xi[layer_3][i-1] > MY_EXTREMELY_SMALL /*&& xi[layer_2][i-1]<=0.*/ )
          {

            D_g = 2.03e-10*Foam::pow((T_inf+T_outer_boundary)*0.5,2.0); /* Thunman et al., Comb. Flame 2001 */
            hmi = D_g/(2.0*rb)*(2.0 + 1.1*Foam::pow((mu/(rho_g*D_g)),1.0/3.0)*Foam::pow(rho_g*rb*vel_mag/mu,0.6));
            O2_diff_suface = surface_area(rb)*hmi*conc_O2;  //O2 transport to the surface(mol/s)=m^2*m/3*mol/m3
            alpha = (R_O2_mole_need)/(O2_diff_suface);
            if (alpha > 1.0)
            {
              alpha = 1.0;
            }
            conc_O2_correct = (1.-alpha)*conc_O2;

            omega_c[i-1] = 2.0*(1.0 + 4.3*Foam::exp(-3390.0/(T->ve[i-1])))/(2.0 + 4.3*Foam::exp(-3390.0/(T->ve[i-1])));
            beta_r[1-1] = 1.715*T->ve[i-1]*Foam::exp(-9000.0/T->ve[i-1]); //Henrik 2002
            //             beta_r[1-1] = 4000.*exp(-80000./(T->ve[i-1]*8.3145)); //Sven 2011
            //                     beta_r[2-1] = 3.42*T->ve[i-1]*exp(-15600.0/T->ve[i-1]); //Henrik 2002
            //                     beta_r[3-1] = beta_r[2-1];
            //                 beta_r[4-1] = beta_r[2-1]/1000.0;

            hmi = D_g/(2.0*rb)*(2.0 + 1.1*Foam::pow((mu/(rho_g*D_g)),1.0/3.0)*Foam::pow(rho_g*rb*vel_mag/mu,0.6));
            D_gAB = 2.03e-10*Foam::pow((T->ve[i-1]+T_outer_boundary)*0.5,2.0);
            hmia = D_gAB*Foam::pow(0.65,2.0)/(rb - charFrontRaduis);
            //             eta = 1.0; /* change this one!?! */

            beta_d = hmi*hmia/(hmi+hmia);
            R_char_reac[1-1][i-1] = M_C*omega_c[i-1]*conc_O2_correct*(beta_r[1-1]*beta_d/(beta_r[1-1]+beta_d))*surface_area(charFrontRaduis);      /* kg/mol*mol/m3*m/s*m2 = kg/s */
            /* this part is removed due to the uneven heat release at the end of the char conversion in each cell*/
            //                     if (omega_c[i-1]*R_char_reac[1-1][i-1]*dt>=m[layer_3][i-1])
            //                     {
              //                         testChar = R_char_reac[1-1][i-1];
              //                         R_char_reac[1-1][i-1] = m[layer_3][i-1]/omega_c[i-1]/dt;
              //                     }
              /*no char gasification*/
              //                     R_char_reac[2-1][i-1] = /*xi[layer_3][i-1]**/M_C*conc_CO2*(beta_r[2-1]*beta_d/(beta_r[2-1]+beta_d))*surface_area(xc[i-1]);                          /* kg/mol*mol/m3*m/s*m2 = kg/s */
              //                     R_char_reac[3-1][i-1] = /*xi[layer_3][i-1]**/M_C*conc_H2O*(beta_r[3-1]*beta_d/(beta_r[3-1]+beta_d))*surface_area(xc[i-1]);                          /* kg/mol*mol/m3*m/s*m2 = kg/s */
              //                 R_char_reac[4-1][i-1] = 0.0;
              //             R_char_reac[4-1][i-1] = /*xi[layer_3][i-1]**/M_C*conc_H2*(beta_r[4-1]*beta_d/(beta_r[4-1]+beta_d))*surface_area(xc[i-1]);                            /* kg/mol*mol/m3*m/s*m2 = kg/s */
              R_b[char_front][i-1] = R_char_reac[1-1][i-1] /*+ R_char_reac[2-1][i-1] + R_char_reac[3-1][i-1] + R_char_reac[4-1][i-1]*/;      /* rate of consumption of char (kg/s) */

              Q_reaction[char_combustion][i-1] = heatRatio(T->ve[i-1])*(R_char_reac[1-1][i-1]/M_C)*((2.0*(omega_c[i-1]-1.0)/omega_c[i-1])*LHV[index_CO]*M_CO+((2.0-omega_c[i-1])/omega_c[i-1])*LHV[index_CO2]*M_CO2-LHV[index_C]*M_C)/* + R_char_reac[2-1][i-1]*(2.0*LHV[index_CO]-LHV[index_C]-LHV[index_CO2]) + R_char_reac[3-1][i-1]*(LHV[index_CO]+LHV[index_H2]-LHV[index_C]-LHV[index_H2O]) + R_char_reac[4-1][i-1]*(LHV[index_CH4]-LHV[index_C]-2.0*LHV[index_H2])*/; /* kg/s*J/kg = W */
              //                     R_char_reac[2-1][i-1]*(2.0*LHV[index_CO]-LHV[index_C]-LHV[index_CO2]) + R_char_reac[3-1][i-1]*(LHV[index_CO]+LHV[index_H2]-LHV[index_C]-LHV[index_H2O]) + R_char_reac[4-1][i-1]*(LHV[index_CH4]-LHV[index_C]-2.0*LHV[index_H2])*/; /* kg/s*J/kg = W */
              //             Q_equilibrate[char_front][i-1] = R_b[char_front][i-1]*cp_g*(T_outer_boundary-T->ve[i-1]); /* (W) */
              Q_equilibrate[char_front][i-1] = 0.0;
              //             R_product[O2_index] = -R_char_reac[1-1][i-1]*M_O2/(M_C*omega_c[i-1]); /* (kg/s) */
              //             R_product[CO_index] = R_product[CO_index] + 2.0*(omega_c[i-1] - 1.0)*R_char_reac[1-1][i-1]*M_CO/(M_C*omega_c[i-1]) + 2.0*R_char_reac[2-1][i-1]*M_CO/M_C + R_char_reac[3-1][i-1]*M_CO/M_C;   /* (kg/s) */
              //             R_product[CO2_index] = R_product[CO2_index] + (2.0 - omega_c[i-1])*R_char_reac[1-1][i-1]*M_CO2/(M_C*omega_c[i-1]) - R_char_reac[2-1][i-1]*M_CO2/M_C; /* (kg/s) */
              //             R_product[H2O_index] = R_product[H2O_index] - R_char_reac[3-1][i-1]*M_H2O/M_C; /* (kg/s) */
              //             R_product[H2_index] = R_product[H2_index] + R_char_reac[3-1][i-1]*M_H2/M_C - 2.0*R_char_reac[4-1][i-1]*M_H2/M_C; /* (kg/s) */
              //             R_product[CH4_index] = R_product[CH4_index] + R_char_reac[4-1][i-1]*M_CH4/M_C; /* (kg/s) */
              if (R_b[char_front][i-1] != 0.)
              {
                combustion_layer = i-1;
                combustion_flag = 1;
              }

            }
            else if (i != 1 && xi[layer_3][i-1] > MY_EXTREMELY_SMALL/* && xi[layer_2][i-1]<=0.*/ && xi[layer_3][i-2] <= MY_EXTREMELY_SMALL && xi[layer_2][i-2] <= MY_EXTREMELY_SMALL && xi[layer_1][i-2] <= MY_EXTREMELY_SMALL)
            {

              D_g = 2.03e-10*Foam::pow((T_inf+T_outer_boundary)*0.5,2.0); /* Thunman et al., Comb. Flame 2001 */
              hmi = D_g/(2.0*rb)*(2.0 + 1.1*Foam::pow((mu/(rho_g*D_g)),1.0/3.0)*Foam::pow(rho_g*rb*vel_mag/mu,0.6));
              O2_diff_suface = surface_area(rb)*hmi*conc_O2;  //O2 transport to the surface(mol/s)=m^2*m/3*mol/m3
              alpha = (R_O2_mole_need)/(O2_diff_suface);
              if (alpha > 1.0)
              {
                alpha = 1.0;
              }
              conc_O2_correct = (1.-alpha)*conc_O2;

              omega_c[i-1] = 2.0*(1.0 + 4.3*Foam::exp(-3390.0/(T->ve[i-1])))/(2.0 + 4.3*Foam::exp(-3390.0/(T->ve[i-1])));
              beta_r[1-1] = 1.715*T->ve[i-1]*Foam::exp(-9000.0/T->ve[i-1]); //Henrik 2002
              //             beta_r[1-1] = 4000.*exp(-80000./(T->ve[i-1]*8.3145)); //Sven 2011
              //                     beta_r[2-1] = 3.42*T->ve[i-1]*exp(-15600.0/T->ve[i-1]); //Henrik 2002
              //                     beta_r[3-1] = beta_r[2-1];
              //                 beta_r[4-1] = beta_r[2-1]/1000.0;

              hmi = D_g/(2.0*rb)*(2.0 + 1.1*Foam::pow((mu/(rho_g*D_g)),1.0/3.0)*Foam::pow(rho_g*rb*vel_mag/mu,0.6));
              D_gAB = 2.03e-10*Foam::pow((T->ve[i-1]+T_outer_boundary)*0.5,2.0);


              hmia = D_gAB*Foam::pow(0.65,2.0)/(rb - charFrontRaduis);
              //                     eta = 1.0; /* change this one!?! */

              beta_d = hmi*hmia/(hmi+hmia);
              R_char_reac[1-1][i-1] = M_C*omega_c[i-1]*conc_O2_correct*(beta_r[1-1]*beta_d/(beta_r[1-1]+beta_d))*surface_area(charFrontRaduis);      /* kg/mol*mol/m3*m/s*m2 = kg/s */     /* kg/mol*mol/m3*m/s*m2 = kg/s */

              //                     if (omega_c[i-1]*R_char_reac[1-1][i-1]*dt>=m[layer_3][i-1])
              //                     {
                //                         testChar = R_char_reac[1-1][i-1];
                //                         R_char_reac[1-1][i-1] = m[layer_3][i-1]/omega_c[i-1]/dt;
                //                     }
                //                     R_char_reac[2-1][i-1] = /*xi[layer_3][i-1]**/M_C*conc_CO2*(beta_r[2-1]*beta_d/(beta_r[2-1]+beta_d))*surface_area(xc[i-1]);                          /* kg/mol*mol/m3*m/s*m2 = kg/s */
                //                     R_char_reac[3-1][i-1] = /*xi[layer_3][i-1]**/M_C*conc_H2O*(beta_r[3-1]*beta_d/(beta_r[3-1]+beta_d))*surface_area(xc[i-1]);                          /* kg/mol*mol/m3*m/s*m2 = kg/s */
                //                 R_char_reac[4-1][i-1] = 0.0;
                //             R_char_reac[4-1][i-1] = /*xi[layer_3][i-1]**/M_C*conc_H2*(beta_r[4-1]*beta_d/(beta_r[4-1]+beta_d))*surface_area(xc[i-1]);                            /* kg/mol*mol/m3*m/s*m2 = kg/s */
                R_b[char_front][i-1] = R_char_reac[1-1][i-1] /*+ R_char_reac[2-1][i-1] + R_char_reac[3-1][i-1] + R_char_reac[4-1][i-1]*/;      /* rate of consumption of char (kg/s) */
                Q_reaction[char_combustion][i-1] = heatRatio(T->ve[i-1])*(R_char_reac[1-1][i-1]/M_C)*((2.0*(omega_c[i-1]-1.0)/omega_c[i-1])*LHV[index_CO]*M_CO+((2.0-omega_c[i-1])/omega_c[i-1])*LHV[index_CO2]*M_CO2-LHV[index_C]*M_C)/* + R_char_reac[2-1][i-1]*(2.0*LHV[index_CO]-LHV[index_C]-LHV[index_CO2]) + R_char_reac[3-1][i-1]*(LHV[index_CO]+LHV[index_H2]-LHV[index_C]-LHV[index_H2O]) + R_char_reac[4-1][i-1]*(LHV[index_CH4]-LHV[index_C]-2.0*LHV[index_H2])*/; /* kg/s*J/kg = W */
                //                     R_char_reac[2-1][i-1]*(2.0*LHV[index_CO]-LHV[index_C]-LHV[index_CO2]) + R_char_reac[3-1][i-1]*(LHV[index_CO]+LHV[index_H2]-LHV[index_C]-LHV[index_H2O]) + R_char_reac[4-1][i-1]*(LHV[index_CH4]-LHV[index_C]-2.0*LHV[index_H2])*/; /* kg/s*J/kg = W */
                //             Q_equilibrate[char_front][i-1] = R_b[char_front][i-1]*cp_g*(T_outer_boundary-T->ve[i-1]); /* (W) */
                Q_equilibrate[char_front][i-1] = 0.0;
                //             R_product[O2_index] = -R_char_reac[1-1][i-1]*M_O2/(M_C*omega_c[i-1]); /* (kg/s) */
                //             R_product[CO_index] = R_product[CO_index] + 2.0*(omega_c[i-1] - 1.0)*R_char_reac[1-1][i-1]*M_CO/(M_C*omega_c[i-1]) + 2.0*R_char_reac[2-1][i-1]*M_CO/M_C + R_char_reac[3-1][i-1]*M_CO/M_C;   /* (kg/s) */
                //             R_product[CO2_index] = R_product[CO2_index] + (2.0 - omega_c[i-1])*R_char_reac[1-1][i-1]*M_CO2/(M_C*omega_c[i-1]) - R_char_reac[2-1][i-1]*M_CO2/M_C; /* (kg/s) */
                //             R_product[H2O_index] = R_product[H2O_index] - R_char_reac[3-1][i-1]*M_H2O/M_C; /* (kg/s) */
                //             R_product[H2_index] = R_product[H2_index] + R_char_reac[3-1][i-1]*M_H2/M_C - 2.0*R_char_reac[4-1][i-1]*M_H2/M_C; /* (kg/s) */
                //             R_product[CH4_index] = R_product[CH4_index] + R_char_reac[4-1][i-1]*M_CH4/M_C; /* (kg/s) */

                if (R_b[char_front][i-1] != 0.)
                {
                  combustion_layer = i-1;
                  combustion_flag = 1;
                }
              }
              else
              {
                R_b[char_front][i-1] = 0.0;
                Q_reaction[char_combustion][i-1] = 0.0;
                Q_equilibrate[char_front][i-1] = 0.0;
              }

            }
            else
            {
              R_b[char_front][i-1] = 0.0;
              Q_reaction[char_combustion][i-1] = 0.0;
              Q_equilibrate[char_front][i-1] = 0.0;
            }

          }



          /* Source term information storage part 1*/

          R_drySourceimins1High = 0.;
          R_drySourceiHigh = 0.;
          R_devoSourceimins1High = 0.;
          R_devoSourceimins1HighChar = 0.;
          R_devoSourceiHigh = 0.;
          R_devoSourceiHighChar = 0.;


          R_drySourceimins1Low = 0.;
          R_drySourceiLow = 0.;
          R_devoSourceimins1Low = 0.;
          R_devoSourceimins1LowChar = 0.;
          R_devoSourceiLow = 0.;
          R_devoSourceiLowChar = 0.;


          for (i = FINE_PARTICLE_MESH_; i >= 1; i--)
          {
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~S_star~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            if (i == FINE_PARTICLE_MESH_)
            {
              S_star[i-1] = 0.0;
            }
            else if (i == 1)
            {
              S_star[i-1] = Q_reaction[devolatilization][i] - Q_reaction[evaporation][i] - Q_reaction[char_combustion][i] - Q_equilibrate[char_front][i] - Q_equilibrate[devol_front][i] - Q_equilibrate[drying_front][i] + Q_reaction[devolatilization][i-1] - Q_reaction[evaporation][i-1] - Q_reaction[char_combustion][i-1] - Q_equilibrate[char_front][i-1] - Q_equilibrate[devol_front][i-1] - Q_equilibrate[drying_front][i-1];
            }
            else
            {
              S_star[i-1] = Q_reaction[devolatilization][i] - Q_reaction[evaporation][i] - Q_reaction[char_combustion][i] - Q_equilibrate[char_front][i] - Q_equilibrate[devol_front][i] - Q_equilibrate[drying_front][i];
            }

            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~dSdT_star~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            if (i == FINE_PARTICLE_MESH_)
            {
              dSdT_star[i-1] = 0.0;
            }
            else if (i == 1)
            {

              //Dry Devo high~~~~~~~~~~~~~~~~~~~~~
              R_drySourceimins1High = m[layer_1][i-1]*DryKinA*Foam::exp(-DryKinE/(8.3145*T->ve[i-1]+1.0));
              //                 if (m[layer_1][i-1] - R_drySourceimins1High/MOISTURE_FRACTION_WB*dt <= MY_EXTREMELY_SMALL)
              //                 {
                //                     R_drySourceimins1High = m[layer_1][i-1]*MOISTURE_FRACTION_WB/dt;
                //                 }
                R_devoSourceimins1High = (DevKinA1_*Foam::exp(-DevKinE1_/(8.3145*(T->ve[i-1]+1.0))) + DevKinA2_*Foam::exp(-DevKinE2_/(8.3145*(T->ve[i-1]+1.0))))*m[layer_2][i-1];
                R_devoSourceimins1HighChar = DevKinA3_*Foam::exp(-DevKinE3_/(8.3145*(T->ve[i-1]+1.0)))*m[layer_2][i-1];

                R_drySourceiHigh = m[layer_1][i]*DryKinA*Foam::exp(-DryKinE/(8.3145*T->ve[i]+1.0));
                //                 if (m[layer_1][i-1] - R_drySourceiHigh/MOISTURE_FRACTION_WB*dt <= MY_EXTREMELY_SMALL)
                //                 {
                  //                     R_drySourceiHigh = m[layer_1][i-1]*MOISTURE_FRACTION_WB/dt;
                  //                 }
                  R_devoSourceiHigh = (DevKinA1_*Foam::exp(-DevKinE1_/(8.3145*(T->ve[i]+1.0))) + DevKinA2_*Foam::exp(-DevKinE2_/(8.3145*(T->ve[i]+1.0))))*m[layer_2][i];
                  R_devoSourceiHighChar = DevKinA3_*Foam::exp(-DevKinE3_/(8.3145*(T->ve[i]+1.0)))*m[layer_2][i];
                  high = -(deltaHvap(T->ve[i-1]+1.0) + gas_cp(index_H2O, 0.5*((T->ve[i-1]+1.0)+T_outer_boundary))*(T_outer_boundary-(T->ve[i-1]+1.0)))*R_drySourceimins1High- R_devoSourceimins1High*cp_g*(T_outer_boundary-(T->ve[i-1]+1.0)) - (deltaHvap(T->ve[i]+1.0) + gas_cp(index_H2O, 0.5*((T->ve[i]+1.0)+T_outer_boundary))*(T_outer_boundary-(T->ve[i]+1.0)))*R_drySourceiHigh - R_devoSourceiHigh*cp_g*(T_outer_boundary-(T->ve[i]+1.0));

                  //Dry Devo low~~~~~~~~~~~~~~~~~~~~~
                  R_drySourceimins1Low = m[layer_1][i-1]*DryKinA*Foam::exp(-DryKinE/(8.3145*T->ve[i-1]-1.0));
                  //                 if (m[layer_1][i-1] - R_drySourceimins1Low/MOISTURE_FRACTION_WB*dt <= MY_EXTREMELY_SMALL)
                  //                 {
                    //                     R_drySourceimins1Low = m[layer_1][i-1]*MOISTURE_FRACTION_WB/dt;
                    //                 }
                    R_devoSourceimins1Low = (DevKinA1_*Foam::exp(-DevKinE1_/(8.3145*(T->ve[i-1]-1.0))) + DevKinA2_*Foam::exp(-DevKinE2_/(8.3145*(T->ve[i-1]-1.0))))*m[layer_2][i-1];
                    R_devoSourceimins1LowChar = DevKinA3_*Foam::exp(-DevKinE3_/(8.3145*(T->ve[i-1]-1.0)))*m[layer_2][i-1];
                    R_drySourceiLow = m[layer_1][i]*DryKinA*Foam::exp(-DryKinE/(8.3145*T->ve[i]-1.0));
                    //                 if (m[layer_1][i-1] - R_drySourceiLow/MOISTURE_FRACTION_WB*dt <= MY_EXTREMELY_SMALL)
                    //                 {
                      //                     R_drySourceiLow = m[layer_1][i-1]*MOISTURE_FRACTION_WB/dt;
                      //                 }
                      R_devoSourceiLow = (DevKinA1_*Foam::exp(-DevKinE1_/(8.3145*(T->ve[i]-1.0))) + DevKinA2_*Foam::exp(-DevKinE2_/(8.3145*(T->ve[i]-1.0))))*m[layer_2][i];
                      R_devoSourceiLowChar = DevKinA3_*Foam::exp(-DevKinE3_/(8.3145*(T->ve[i]-1.0)))*m[layer_2][i];
                      low = -(deltaHvap(T->ve[i-1]-1.0) + gas_cp(index_H2O, 0.5*((T->ve[i-1]-1.0)+T_outer_boundary))*(T_outer_boundary-(T->ve[i-1]-1.0)))*R_drySourceimins1Low- R_devoSourceimins1Low*cp_g*(T_outer_boundary-(T->ve[i-1]-1.0)) - (deltaHvap(T->ve[i]-1.0) + gas_cp(index_H2O, 0.5*((T->ve[i]-1.0)+T_outer_boundary))*(T_outer_boundary-(T->ve[i]-1.0)))*R_drySourceiLow - R_devoSourceiLow*cp_g*(T_outer_boundary-(T->ve[i]-1.0));


                      //Char conversion~~~~~~~~~~
                      if (i == combustion_layer+1)// combustion at i-1, NO combustion at i
                      {

                        charFrontRaduis = charFrontLocation (rb, (i-1),V_cell,V_char,xc,xi[layer_3][0]);
                        //HIGH~~~~~~~~~~~~~~~~~~~~~~~~~~~

                        //                     alpha = ((R_H2_Sum[i]+(R_devoSourceimins1High+R_devoSourceiHigh)*Y_H2/Y_G)/M_H2/2.)/(O2_diff_suface);
                        R_O2_mole_need = R_O2_mole_need_list[i] + ((R_devoSourceimins1High+R_devoSourceiHigh+R_devoSourceimins1HighChar+R_devoSourceiHighChar)*C_FRACTION-(R_devoSourceimins1HighChar+R_devoSourceiHighChar))/M_C+(R_devoSourceimins1High+R_devoSourceiHigh+R_devoSourceimins1HighChar+R_devoSourceiHighChar)*(H_FRACTION/M_H/4.-O_FRACTION/M_O/2.);

                        alpha = (R_O2_mole_need)/(O2_diff_suface);
                        if (alpha > 1.0)
                        {
                          alpha = 1.0;
                        }
                        conc_O2_correct = (1.-alpha)*conc_O2; /* molar concentration of O2 in the gas phase */

                        D_gAB = 2.03e-10*Foam::pow((T->ve[i-1]+1.0+T_outer_boundary)*0.5,2.0);
                        hmia = D_gAB*Foam::pow(0.65,2.0)/(rb - charFrontRaduis);
                        beta_d = hmi*hmia/(hmi+hmia);

                        omega_cS = 2.0*(1.0 + 4.3*Foam::exp(-3390.0/(T->ve[i-1]+1.0)))/(2.0 + 4.3*Foam::exp(-3390.0/(T->ve[i-1]+1.0)));
                        R_char_reac1S = M_C*omega_cS*conc_O2_correct*(1.715*(T->ve[i-1]+1.0)*Foam::exp(-9000.0/(T->ve[i-1]+1.0))*beta_d/(1.715*(T->ve[i-1]+1.0)*Foam::exp(-9000.0/(T->ve[i-1]+1.0))+beta_d))*
                        surface_area(charFrontRaduis);      /* kg/mol*mol/m3*m/s*m2 = kg/s */     /* kg/mol*mol/m3*m/s*m2 = kg/s */
                        //                     R_char_reac2S = M_C*conc_CO2*(3.42*(T->ve[i-1]+1.0)*exp(-15600.0/(T->ve[i-1]+1.0))*beta_d/(3.42*(T->ve[i-1]+1.0)*exp(-15600.0/(T->ve[i-1]+1.0))+beta_d))*surface_area(xc[i-1]);
                        //                     R_char_reac3S = M_C*conc_H2O*(3.42*(T->ve[i-1]+1.0)*exp(-15600.0/(T->ve[i-1]+1.0))*beta_d/(3.42*(T->ve[i-1]+1.0)*exp(-15600.0/(T->ve[i-1]+1.0))+beta_d))*surface_area(xc[i-1]);
                        //                     R_char_reac4S = 0.0;

                        high =  high - heatRatio(T->ve[i-1]+1.0)*((R_char_reac1S/M_C)*((2.0*(omega_cS-1.0)/omega_cS)*LHV[index_CO]*M_CO+((2.0-omega_cS)/omega_cS)*LHV[index_CO2]*M_CO2-LHV[index_C]*M_C));
                        /*+ R_char_reac2S*(2.0*LHV[index_CO]-LHV[index_C]-LHV[index_CO2]) + R_char_reac3S*(LHV[index_CO]+LHV[index_H2]-LHV[index_C]-LHV[index_H2O]) + R_char_reac4S*(LHV[index_CH4]-LHV[index_C]-2.0*LHV[index_H2])*/

                        //LOW~~~~~~~~~~~~~~~~~~~~~~~~~~~

                        //                     alpha = ((R_H2_Sum[i]+(R_devoSourceimins1Low+R_devoSourceiLow)*Y_H2/Y_G)/M_H2/2.)/(O2_diff_suface);
                        R_O2_mole_need = R_O2_mole_need_list[i] + ((R_devoSourceimins1Low+R_devoSourceiLow+R_devoSourceimins1LowChar+R_devoSourceiLowChar)*C_FRACTION-(R_devoSourceimins1LowChar+R_devoSourceiLowChar))/M_C+(R_devoSourceimins1Low+R_devoSourceiLow+R_devoSourceimins1LowChar+R_devoSourceiLowChar)*(H_FRACTION/M_H/4.-O_FRACTION/M_O/2.);

                        alpha = (R_O2_mole_need)/(O2_diff_suface);
                        if (alpha > 1.0)
                        {
                          alpha = 1.0;
                        }
                        conc_O2_correct = (1.-alpha)*conc_O2; /* molar concentration of O2 in the gas phase */

                        D_gAB = 2.03e-10*Foam::pow((T->ve[i-1]-1.0+T_outer_boundary)*0.5,2.0);
                        hmia = D_gAB*Foam::pow(0.65,2.0)/(rb - charFrontRaduis);
                        beta_d = hmi*hmia/(hmi+hmia);

                        omega_cS = 2.0*(1.0 + 4.3*Foam::exp(-3390.0/(T->ve[i-1]-1.0)))/(2.0 + 4.3*Foam::exp(-3390.0/(T->ve[i-1]-1.0)));
                        R_char_reac1S = M_C*omega_cS*conc_O2_correct*(1.715*(T->ve[i-1]-1.0)*Foam::exp(-9000.0/(T->ve[i-1]-1.0))*beta_d/(1.715*(T->ve[i-1]-1.0)*Foam::exp(-9000.0/(T->ve[i-1]-1.0))+beta_d))*surface_area(charFrontRaduis);      /* kg/mol*mol/m3*m/s*m2 = kg/s */     /* kg/mol*mol/m3*m/s*m2 = kg/s */;
                        //                     R_char_reac2S = M_C*conc_CO2*(3.42*(T->ve[i-1]-1.0)*exp(-15600.0/(T->ve[i-1]-1.0))*beta_d/(3.42*(T->ve[i-1]-1.0)*exp(-15600.0/(T->ve[i-1]-1.0))+beta_d))*surface_area(xc[i-1]);
                        //                     R_char_reac3S = M_C*conc_H2O*(3.42*(T->ve[i-1]-1.0)*exp(-15600.0/(T->ve[i-1]-1.0))*beta_d/(3.42*(T->ve[i-1]-1.0)*exp(-15600.0/(T->ve[i-1]-1.0))+beta_d))*surface_area(xc[i-1]);
                        //                     R_char_reac4S = 0.0;

                        low =  low - heatRatio(T->ve[i-1]-1.0)*((R_char_reac1S/M_C)*((2.0*(omega_cS-1.0)/omega_cS)*LHV[index_CO]*M_CO+((2.0-omega_cS)/omega_cS)*LHV[index_CO2]*M_CO2-LHV[index_C]*M_C))/* + R_char_reac2S*(2.0*LHV[index_CO]-LHV[index_C]-LHV[index_CO2]) + R_char_reac3S*(LHV[index_CO]+LHV[index_H2]-LHV[index_C]-LHV[index_H2O]) + R_char_reac4S*(LHV[index_CH4]-LHV[index_C]-2.0*LHV[index_H2])*/;


                      }
                      else if (i == combustion_layer)// no combustion at i-1, combustion at i
                      {
                        charFrontRaduis = charFrontLocation (rb, (i),V_cell,V_char,xc,xi[layer_3][0]);
                        //HIGH~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        //                     alpha = ((R_H2_Sum[i]+(R_devoSourceimins1High+R_devoSourceiHigh)*Y_H2/Y_G)/M_H2/2.)/(O2_diff_suface);
                        R_O2_mole_need = R_O2_mole_need_list[i] + ((R_devoSourceimins1High+R_devoSourceiHigh+R_devoSourceimins1HighChar+R_devoSourceiHighChar)*C_FRACTION-(R_devoSourceimins1HighChar+R_devoSourceiHighChar))/M_C+(R_devoSourceimins1High+R_devoSourceiHigh+R_devoSourceimins1HighChar+R_devoSourceiHighChar)*(H_FRACTION/M_H/4.-O_FRACTION/M_O/2.);

                        alpha = (R_O2_mole_need)/(O2_diff_suface);
                        if (alpha > 1.0)
                        {
                          alpha = 1.0;
                        }
                        conc_O2_correct = (1.-alpha)*conc_O2; /* molar concentration of O2 in the gas phase */

                        D_gAB = 2.03e-10*Foam::pow((T->ve[i]+1.0+T_outer_boundary)*0.5,2.0);
                        hmia = D_gAB*Foam::pow(0.65,2.0)/(rb - charFrontRaduis);
                        beta_d = hmi*hmia/(hmi+hmia);

                        omega_cS = 2.0*(1.0 + 4.3*Foam::exp(-3390.0/(T->ve[i]+1.0)))/(2.0 + 4.3*Foam::exp(-3390.0/(T->ve[i]+1.0)));
                        R_char_reac1S = M_C*omega_cS*conc_O2_correct*(1.715*(T->ve[i]+1.0)*Foam::exp(-9000.0/(T->ve[i]+1.0))*beta_d/(1.715*(T->ve[i]+1.0)*Foam::exp(-9000.0/(T->ve[i]+1.0))+beta_d))*surface_area(charFrontRaduis);      /* kg/mol*mol/m3*m/s*m2 = kg/s */     /* kg/mol*mol/m3*m/s*m2 = kg/s */;
                        //                     R_char_reac2S = M_C*conc_CO2*(3.42*(T->ve[i]+1.0)*exp(-15600.0/(T->ve[i]+1.0))*beta_d/(3.42*(T->ve[i]+1.0)*exp(-15600.0/(T->ve[i]+1.0))+beta_d))*surface_area(xc[i]);
                        //                     R_char_reac3S = M_C*conc_H2O*(3.42*(T->ve[i]+1.0)*exp(-15600.0/(T->ve[i]+1.0))*beta_d/(3.42*(T->ve[i]+1.0)*exp(-15600.0/(T->ve[i]+1.0))+beta_d))*surface_area(xc[i]);
                        //                     R_char_reac4S = 0.0;

                        high =  high - heatRatio(T->ve[i]+1.0)*((R_char_reac1S/M_C)*((2.0*(omega_cS-1.0)/omega_cS)*LHV[index_CO]*M_CO+((2.0-omega_cS)/omega_cS)*LHV[index_CO2]*M_CO2-LHV[index_C]*M_C))/* + R_char_reac2S*(2.0*LHV[index_CO]-LHV[index_C]-LHV[index_CO2]) + R_char_reac3S*(LHV[index_CO]+LHV[index_H2]-LHV[index_C]-LHV[index_H2O]) + R_char_reac4S*(LHV[index_CH4]-LHV[index_C]-2.0*LHV[index_H2])*/;

                        //LOW~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        //                     alpha = ((R_H2_Sum[i]+(R_devoSourceimins1Low+R_devoSourceiLow)*Y_H2/Y_G)/M_H2/2.)/(O2_diff_suface);
                        R_O2_mole_need = R_O2_mole_need_list[i] + ((R_devoSourceimins1Low+R_devoSourceiLow+R_devoSourceimins1LowChar+R_devoSourceiLowChar)*C_FRACTION-(R_devoSourceimins1LowChar+R_devoSourceiLowChar))/M_C+(R_devoSourceimins1Low+R_devoSourceiLow+R_devoSourceimins1LowChar+R_devoSourceiLowChar)*(H_FRACTION/M_H/4.-O_FRACTION/M_O/2.);
                        alpha = (R_O2_mole_need)/(O2_diff_suface);
                        if (alpha > 1.0)
                        {
                          alpha = 1.0;
                        }
                        conc_O2_correct = (1.-alpha)*conc_O2; /* molar concentration of O2 in the gas phase */

                        D_gAB = 2.03e-10*Foam::pow((T->ve[i]-1.0+T_outer_boundary)*0.5,2.0);
                        hmia = D_gAB*Foam::pow(0.65,2.0)/(rb - charFrontRaduis);
                        beta_d = hmi*hmia/(hmi+hmia);

                        omega_cS = 2.0*(1.0 + 4.3*Foam::exp(-3390.0/(T->ve[i]-1.0)))/(2.0 + 4.3*Foam::exp(-3390.0/(T->ve[i]-1.0)));
                        R_char_reac1S = M_C*omega_cS*conc_O2_correct*(1.715*(T->ve[i]-1.0)*Foam::exp(-9000.0/(T->ve[i]-1.0))*beta_d/(1.715*(T->ve[i]-1.0)*Foam::exp(-9000.0/(T->ve[i]-1.0))+beta_d))*surface_area(charFrontRaduis);      /* kg/mol*mol/m3*m/s*m2 = kg/s */     /* kg/mol*mol/m3*m/s*m2 = kg/s */;
                        //                     R_char_reac2S = M_C*conc_CO2*(3.42*(T->ve[i]-1.0)*exp(-15600.0/(T->ve[i]-1.0))*beta_d/(3.42*(T->ve[i]-1.0)*exp(-15600.0/(T->ve[i]-1.0))+beta_d))*surface_area(xc[i]);
                        //                     R_char_reac3S = M_C*conc_H2O*(3.42*(T->ve[i]-1.0)*exp(-15600.0/(T->ve[i]-1.0))*beta_d/(3.42*(T->ve[i]-1.0)*exp(-15600.0/(T->ve[i]-1.0))+beta_d))*surface_area(xc[i]);
                        //                     R_char_reac4S = 0.0;

                        low =  low - heatRatio(T->ve[i]-1.0)*((R_char_reac1S/M_C)*((2.0*(omega_cS-1.0)/omega_cS)*LHV[index_CO]*M_CO+((2.0-omega_cS)/omega_cS)*LHV[index_CO2]*M_CO2-LHV[index_C]*M_C))/* + R_char_reac2S*(2.0*LHV[index_CO]-LHV[index_C]-LHV[index_CO2]) + R_char_reac3S*(LHV[index_CO]+LHV[index_H2]-LHV[index_C]-LHV[index_H2O]) + R_char_reac4S*(LHV[index_CH4]-LHV[index_C]-2.0*LHV[index_H2])*/;
                      }
                      else//no combustion
                      {
                        //do nothing
                      }

                    }
                    else
                    {
                      //Dry Devo high~~~~~~~~~~~~~~~~~~~~~
                      R_drySourceiHigh = m[layer_1][i]*DryKinA*Foam::exp(-DryKinE/(8.3145*T->ve[i]+1.0));
                      R_devoSourceiHigh = (DevKinA1_*Foam::exp(-DevKinE1_/(8.3145*(T->ve[i]+1.0))) + DevKinA2_*Foam::exp(-DevKinE2_/(8.3145*(T->ve[i]+1.0))))*m[layer_2][i];
                      R_devoSourceiHighChar = DevKinA3_*Foam::exp(-DevKinE3_/(8.3145*(T->ve[i]+1.0)))*m[layer_2][i];
                      high = -(deltaHvap(T->ve[i]+1.0) + gas_cp(index_H2O, 0.5*((T->ve[i]+1.0)+T_outer_boundary))*(T_outer_boundary-(T->ve[i]+1.0)))*R_drySourceiHigh - R_devoSourceiHigh*cp_g*(T_outer_boundary-(T->ve[i]+1.0));

                      //Dry Devo low~~~~~~~~~~~~~~~~~~~~~
                      R_drySourceiLow = m[layer_1][i]*DryKinA*Foam::exp(-DryKinE/(8.3145*T->ve[i]-1.0));
                      R_devoSourceiLow = (DevKinA1_*Foam::exp(-DevKinE1_/(8.3145*(T->ve[i]-1.0))) + DevKinA2_*Foam::exp(-DevKinE2_/(8.3145*(T->ve[i]-1.0))))*m[layer_2][i];
                      R_devoSourceiLowChar = DevKinA3_*Foam::exp(-DevKinE3_/(8.3145*(T->ve[i]-1.0)))*m[layer_2][i];
                      low = -(deltaHvap(T->ve[i]-1.0) + gas_cp(index_H2O, 0.5*((T->ve[i]-1.0)+T_outer_boundary))*(T_outer_boundary-(T->ve[i]-1.0)))*R_drySourceiLow - R_devoSourceiLow*cp_g*(T_outer_boundary-(T->ve[i]-1.0));

                      //Char conversion~~~~~~~~~~
                      if (i == combustion_layer)// no combustion at i-1, combustion at i
                      {
                        charFrontRaduis = charFrontLocation (rb, (i),V_cell,V_char,xc,xi[layer_3][0]);
                        //HIGH~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        //                     alpha = ((R_H2_Sum[i]+R_devoSourceiHigh*Y_H2/Y_G)/M_H2/2.)/(O2_diff_suface);
                        R_O2_mole_need = R_O2_mole_need_list[i] + ((R_devoSourceiHigh+R_devoSourceiHighChar)*C_FRACTION-(R_devoSourceiHighChar))/M_C+(R_devoSourceiHigh+R_devoSourceiHighChar)*(H_FRACTION/M_H/4.-O_FRACTION/M_O/2.);

                        alpha = (R_O2_mole_need)/(O2_diff_suface);
                        if (alpha > 1.0)
                        {
                          alpha = 1.0;
                        }
                        conc_O2_correct = (1.-alpha)*conc_O2; /* molar concentration of O2 in the gas phase */

                        D_gAB = 2.03e-10*Foam::pow((T->ve[i]+1.0+T_outer_boundary)*0.5,2.0);
                        hmia = D_gAB*Foam::pow(0.65,2.0)/(rb - charFrontRaduis);
                        beta_d = hmi*hmia/(hmi+hmia);

                        omega_cS = 2.0*(1.0 + 4.3*Foam::exp(-3390.0/(T->ve[i]+1.0)))/(2.0 + 4.3*Foam::exp(-3390.0/(T->ve[i]+1.0)));

                        R_char_reac1S = M_C*omega_cS*conc_O2_correct*(1.715*(T->ve[i]+1.0)*Foam::exp(-9000.0/(T->ve[i]+1.0))*beta_d/(1.715*(T->ve[i]+1.0)*Foam::exp(-9000.0/(T->ve[i]+1.0))+beta_d))*surface_area(charFrontRaduis);      /* kg/mol*mol/m3*m/s*m2 = kg/s */     /* kg/mol*mol/m3*m/s*m2 = kg/s */;

                        //                     R_char_reac2S = M_C*conc_CO2*(3.42*(T->ve[i]+1.0)*Foam::exp(-15600.0/(T->ve[i]+1.0))*beta_d/(3.42*(T->ve[i]+1.0)*Foam::exp(-15600.0/(T->ve[i]+1.0))+beta_d))*surface_area(xc[i]);
                        //                     R_char_reac3S = M_C*conc_H2O*(3.42*(T->ve[i]+1.0)*Foam::exp(-15600.0/(T->ve[i]+1.0))*beta_d/(3.42*(T->ve[i]+1.0)*Foam::exp(-15600.0/(T->ve[i]+1.0))+beta_d))*surface_area(xc[i]);
                        //                     R_char_reac4S = 0.0;

                        high =  high - heatRatio(T->ve[i]+1.0)*((R_char_reac1S/M_C)*((2.0*(omega_cS-1.0)/omega_cS)*LHV[index_CO]*M_CO+((2.0-omega_cS)/omega_cS)*LHV[index_CO2]*M_CO2-LHV[index_C]*M_C))/* + R_char_reac2S*(2.0*LHV[index_CO]-LHV[index_C]-LHV[index_CO2]) + R_char_reac3S*(LHV[index_CO]+LHV[index_H2]-LHV[index_C]-LHV[index_H2O]) + R_char_reac4S*(LHV[index_CH4]-LHV[index_C]-2.0*LHV[index_H2])*/;

                        //LOW~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        //                     alpha = ((R_H2_Sum[i]+R_devoSourceiLow*Y_H2/Y_G)/M_H2/2.)/(O2_diff_suface);
                        R_O2_mole_need = R_O2_mole_need_list[i] + ((R_devoSourceiLow+R_devoSourceiLowChar)*C_FRACTION-(R_devoSourceiLowChar))/M_C+(R_devoSourceiLow+R_devoSourceiLowChar)*(H_FRACTION/M_H/4.-O_FRACTION/M_O/2.);
                        alpha = (R_O2_mole_need)/(O2_diff_suface);
                        if (alpha > 1.0)
                        {
                          alpha = 1.0;
                        }
                        conc_O2_correct = (1.-alpha)*conc_O2; /* molar concentration of O2 in the gas phase */

                        D_gAB = 2.03e-10*Foam::pow((T->ve[i]-1.0+T_outer_boundary)*0.5,2.0);
                        hmia = D_gAB*Foam::pow(0.65,2.0)/(rb - charFrontRaduis);
                        beta_d = hmi*hmia/(hmi+hmia);

                        omega_cS = 2.0*(1.0 + 4.3*Foam::exp(-3390.0/(T->ve[i]-1.0)))/(2.0 + 4.3*Foam::exp(-3390.0/(T->ve[i]-1.0)));

                        R_char_reac1S = M_C*omega_cS*conc_O2_correct*(1.715*(T->ve[i]-1.0)*Foam::exp(-9000.0/(T->ve[i]-1.0))*beta_d/(1.715*(T->ve[i]-1.0)*Foam::exp(-9000.0/(T->ve[i]-1.0))+beta_d))*surface_area(charFrontRaduis);

                        //                     R_char_reac2S = M_C*conc_CO2*(3.42*(T->ve[i]-1.0)*Foam::exp(-15600.0/(T->ve[i]-1.0))*beta_d/(3.42*(T->ve[i]-1.0)*Foam::exp(-15600.0/(T->ve[i]-1.0))+beta_d))*surface_area(xc[i]);
                        //                     R_char_reac3S = M_C*conc_H2O*(3.42*(T->ve[i]-1.0)*Foam::exp(-15600.0/(T->ve[i]-1.0))*beta_d/(3.42*(T->ve[i]-1.0)*Foam::exp(-15600.0/(T->ve[i]-1.0))+beta_d))*surface_area(xc[i]);
                        //                     R_char_reac4S = 0.0;

                        low =  low - heatRatio(T->ve[i]-1.0)*((R_char_reac1S/M_C)*((2.0*(omega_cS-1.0)/omega_cS)*LHV[index_CO]*M_CO+((2.0-omega_cS)/omega_cS)*LHV[index_CO2]*M_CO2-LHV[index_C]*M_C)) /*+ R_char_reac2S*(2.0*LHV[index_CO]-LHV[index_C]-LHV[index_CO2]) + R_char_reac3S*(LHV[index_CO]+LHV[index_H2]-LHV[index_C]-LHV[index_H2O]) + R_char_reac4S*(LHV[index_CH4]-LHV[index_C]-2.0*LHV[index_H2])*/;
                      }
                      else
                      {
                        //do nothing
                      }

                    }

                    dSdT_star[i-1] = (high - low)/2.0;
                  }

                  /* --------------------------------------------------------------------- */

                  /* Update source term components Su and Sp */
                  /* --------------------------------------------------------------------- */
                  /* Picard's method:
                  *        Su = S* - (dS/dT)* * T*
                  *        Sp = (dS/dT)*
                  *        where * denoted current iteration/time level */
                  for (i = 1; i <= FINE_PARTICLE_MESH_; i++)
                  {
                    Su[i-1] = S_star[i-1] - dSdT_star[i-1]*T->ve[i-1];
                    Sp[i-1] = dSdT_star[i-1];
                  }
                  /* --------------------------------------------------------------------- */

                  /* Update boundary temperature */
                  /* --------------------------------------------------------------------- */
                  h = k_g/(2.0*rb)*(2.0 + 1.1*Foam::pow((cp_g*mu/k_g),1.0/3.0)
                  *Foam::pow((rho_g*2.0*rb*vel_mag/mu),0.6));
                  a = view_factor*emissivity*SIGMA;
                  d = h + (xi[layer_1][0]*k_p(layer_1, T->ve[0]) + xi[layer_2][0]*k_p(layer_2, T->ve[0]) + xi[layer_3][0]*k_p(layer_3, T->ve[0]) + xi[layer_4][0]*k_p(layer_4, T->ve[0]))/(rb - xc[0]);
                  e = - (view_factor*emissivity*SIGMA*Foam::pow(T_RADIATION_,4.0) + h*T_inf + (xi[layer_1][0]*k_p(layer_1, T->ve[0]) + xi[layer_2][0]*k_p(layer_2, T->ve[0]) + xi[layer_3][0]*k_p(layer_3, T->ve[0]) + xi[layer_4][0]*k_p(layer_4, T->ve[0]))*T->ve[0]/(rb - xc[0]));
                  q = d/a;
                  delta_0 = 12.0*a*e;
                  delta_1 = 27.0*a*Foam::pow(d,2.0);
                  Q = Foam::pow(0.5*(delta_1 + Foam::sqrt(Foam::pow(delta_1,2.0) - 4.0*Foam::pow(delta_0,3.0))),(1.0/3.0));
                  S = 0.5*Foam::sqrt(1.0/(3.0*a)*(Q + delta_0/Q));
                  T_outer_boundary = - S + 0.5*Foam::sqrt(-4.0*Foam::pow(S,2.0) + q/S);

                  if (iter_count % output_every == 0)
                  {
                    if (VERBOSITY_)
                    {
                      printf("Outer boundary temperature: %f\n",T_outer_boundary);
                    }
                  }
                  /* --------------------------------------------------------------------- */

                  /* Boundary node solution (outer node) */
                  /* --------------------------------------------------------------------- */
                  //east
                  Tf = 0.5*(T->ve[0] + T->ve[1]);
                  xif[layer_1] = 0.5*(xi[layer_1][0] + xi[layer_1][1]);
                  xif[layer_2] = 0.5*(xi[layer_2][0] + xi[layer_2][1]);
                  xif[layer_3] = 0.5*(xi[layer_3][0] + xi[layer_3][1]);
                  xif[layer_4] = 0.5*(xi[layer_4][0] + xi[layer_4][1]);
                  Af = surface_area(xc[1] + 0.5*(xc[0] - xc[1]));
                  ae = Af*(xif[layer_1]*k_p(layer_1, Tf) + xif[layer_2]*k_p(layer_2, Tf) + xif[layer_3]*k_p(layer_3, Tf) + xif[layer_4]*k_p(layer_4, Tf))/(xc[0] - xc[1]);
                  ap0 = (m[layer_1][0]*c_p(layer_1, T->ve[0]) + m[layer_2][0]*c_p(layer_2, T->ve[0]) + m[layer_3][0]*c_p(layer_3, T->ve[0]) + m[layer_4][0]*c_p(layer_4, T->ve[0]))/dt;
                  //west, Sp_b = -kA/dx  Su_b = (kA/dx)*T_boundary
                  Af = surface_area(rb);
                  Sp_b = -Af*(xi[layer_1][0]*k_p(layer_1, T->ve[0]) + xi[layer_2][0]*k_p(layer_2, T->ve[0])+ xi[layer_3][0]*k_p(layer_3, T->ve[0]) + xi[layer_4][0]*k_p(layer_4, T->ve[0]))/(rb - xc[0]);
                  ap = ap0 /*+ aw*/ + ae - Sp_b - Sp[0];//no west point
                  A->me[0][0] = -ap;
                  A->me[0][1] = ae;
                  Su_b = Af*(T_outer_boundary*(xi[layer_1][0]*k_p(layer_1, T->ve[0]) + xi[layer_2][0]*k_p(layer_2, T->ve[0])+ xi[layer_3][0]*k_p(layer_3, T->ve[0]) + xi[layer_4][0]*k_p(layer_4, T->ve[0]))/(rb - xc[0]));
                  b->ve[0] = -ap0*T->ve[0] - Su_b - Su[0]; //-ap*Tp0-Su, Su = Af*.... from heat transfer + Su[0] from reaction
                  /* --------------------------------------------------------------------- */
                  /* Loop over interior nodes */
                  /* --------------------------------------------------------------------- */
                  j = 2;
                  for (i = 2; i <= (FINE_PARTICLE_MESH_-1); i++)
                  {
                    Tf = 0.5*(T->ve[j-2] + T->ve[j-1]);
                    xif[layer_1] = 0.5*(xi[layer_1][j-2] + xi[layer_1][j-1]);
                    xif[layer_2] = 0.5*(xi[layer_2][j-2] + xi[layer_2][j-1]);
                    xif[layer_3] = 0.5*(xi[layer_3][j-2] + xi[layer_3][j-1]);
                    xif[layer_4] = 0.5*(xi[layer_4][j-2] + xi[layer_4][j-1]);
                    Af = surface_area(0.5*(xc[j-2] + xc[j-1]));
                    aw = Af*(xif[layer_1]*k_p(layer_1, Tf) + xif[layer_2]*k_p(layer_2, Tf) + xif[layer_3]*k_p(layer_3, Tf) + xif[layer_4]*k_p(layer_4, Tf))/(xc[j-2] - xc[j-1]);
                    Tf = 0.5*(T->ve[j-1] + T->ve[j]);
                    xif[layer_1] = 0.5*(xi[layer_1][j-1] + xi[layer_1][j]);
                    xif[layer_2] = 0.5*(xi[layer_2][j-1] + xi[layer_2][j]);
                    xif[layer_3] = 0.5*(xi[layer_3][j-1] + xi[layer_3][j]);
                    xif[layer_4] = 0.5*(xi[layer_4][j-1] + xi[layer_4][j]);
                    Af = surface_area(0.5*(xc[j-1] + xc[j]));
                    ae = Af*(xif[layer_1]*k_p(layer_1, Tf) + xif[layer_2]*k_p(layer_2, Tf) + xif[layer_3]*k_p(layer_3, Tf) + xif[layer_4]*k_p(layer_4, Tf))/(xc[j-1] - xc[j]);
                    ap0 = (m[layer_1][j-1]*c_p(layer_1, T->ve[j-1]) + m[layer_2][j-1]*c_p(layer_2, T->ve[j-1]) + m[layer_3][j-1]*c_p(layer_3, T->ve[j-1]) + m[layer_4][j-1]*c_p(layer_4, T->ve[j-1]))/dt;
                    ap = ap0 + aw + ae - Sp[j-1];

                    A->me[i-1][j-2] = aw;
                    A->me[i-1][j-1] = -ap;
                    A->me[i-1][j] = ae;
                    b->ve[i-1] = -ap0*T->ve[j-1] - Su[j-1];
                    j = j + 1;
                  }
                  /* --------------------------------------------------------------------- */

                  /* Boundary node solution (inner node) */
                  /* --------------------------------------------------------------------- */
                  Tf = 0.5*(T->ve[FINE_PARTICLE_MESH_-2] + T->ve[FINE_PARTICLE_MESH_-1]);
                  xif[layer_1] = 0.5*(xi[layer_1][FINE_PARTICLE_MESH_-2] + xi[layer_1][FINE_PARTICLE_MESH_-1]);
                  xif[layer_2] = 0.5*(xi[layer_2][FINE_PARTICLE_MESH_-2] + xi[layer_2][FINE_PARTICLE_MESH_-1]);
                  xif[layer_3] = 0.5*(xi[layer_3][FINE_PARTICLE_MESH_-2] + xi[layer_3][FINE_PARTICLE_MESH_-1]);
                  xif[layer_4] = 0.5*(xi[layer_4][FINE_PARTICLE_MESH_-2] + xi[layer_4][FINE_PARTICLE_MESH_-1]);
                  Af = surface_area(0.5*(xc[FINE_PARTICLE_MESH_-2] + xc[FINE_PARTICLE_MESH_-1]));
                  aw = Af*(xif[layer_1]*k_p(layer_1, Tf) + xif[layer_2]*k_p(layer_2, Tf) + xif[layer_3]*k_p(layer_3, Tf) + xif[layer_4]*k_p(layer_4, Tf))/(xc[FINE_PARTICLE_MESH_-2] - xc[FINE_PARTICLE_MESH_-1]);
                  ap0 = (m[layer_1][FINE_PARTICLE_MESH_-1]*c_p(layer_1, T->ve[FINE_PARTICLE_MESH_-1]) + m[layer_2][FINE_PARTICLE_MESH_-1]*c_p(layer_2, T->ve[FINE_PARTICLE_MESH_-1]) + m[layer_3][FINE_PARTICLE_MESH_-1]*c_p(layer_3, T->ve[FINE_PARTICLE_MESH_-1]) + m[layer_4][FINE_PARTICLE_MESH_-1]*c_p(layer_4, T->ve[FINE_PARTICLE_MESH_-1]))/dt;
                  ap = ap0 + aw /*+ ae*/ - Sp[FINE_PARTICLE_MESH_-1];
                  A->me[FINE_PARTICLE_MESH_-1][FINE_PARTICLE_MESH_-2] = aw;
                  A->me[FINE_PARTICLE_MESH_-1][FINE_PARTICLE_MESH_-1] = -ap;
                  b->ve[FINE_PARTICLE_MESH_-1] = -ap0*T->ve[FINE_PARTICLE_MESH_-1] - Su[FINE_PARTICLE_MESH_-1];
                  /* --------------------------------------------------------------------- */

                  for (j = 1; j <= FINE_PARTICLE_MESH_; j++)
                  {
                    if (j==1)
                    {
                      ThermalTimeScale[j-1] =Foam::pow(rb-xc[j-1],2.0)/((xi[layer_1][j-1]*k_p(layer_1, T->ve[j-1]) + xi[layer_2][j-1]*k_p(layer_2, T->ve[j-1]) + xi[layer_3][j-1]*k_p(layer_3, T->ve[j-1]) + xi[layer_4][j-1]*k_p(layer_4, T->ve[j-1]))/((m[layer_1][j-1]*c_p(layer_1, T->ve[j-1]) + m[layer_2][j-1]*c_p(layer_2, T->ve[j-1]) + m[layer_3][j-1]*c_p(layer_3, T->ve[j-1]) + m[layer_4][j-1]*c_p(layer_4, T->ve[j-1]))/V_cell[j-1]));
                    }
                    else
                    {
                      ThermalTimeScale[j-1] =Foam::pow(xc[j-2]-xc[j-1],2.0)/((xi[layer_1][j-1]*k_p(layer_1, T->ve[j-1]) + xi[layer_2][j-1]*k_p(layer_2, T->ve[j-1]) + xi[layer_3][j-1]*k_p(layer_3, T->ve[j-1]) + xi[layer_4][j-1]*k_p(layer_4, T->ve[j-1]))/((m[layer_1][j-1]*c_p(layer_1, T->ve[j-1]) + m[layer_2][j-1]*c_p(layer_2, T->ve[j-1]) + m[layer_3][j-1]*c_p(layer_3, T->ve[j-1]) + m[layer_4][j-1]*c_p(layer_4, T->ve[j-1]))/V_cell[j-1]));
                    }

                  }


                  /* Solve matrix system */
                  /* --------------------------------------------------------------------- */
                  LU = m_get(A->m,A->n);
                  LU = m_copy(A,LU);
                  pivot = px_get(A->m);
                  LUfactor(LU,pivot);
                  T = LUsolve(LU,pivot,b,T);
                  PX_FREE(pivot);
                  M_FREE(LU);
                  t = t + dt;
                  iter_count = iter_count + 1;
                  /* --------------------------------------------------------------------- */

                  /* Update the masses */
                  /* --------------------------------------------------------------------- */
                  for (i = 1; i <= FINE_PARTICLE_MESH_; i++)
                  {
                    if (t==dt) {
                      char_yield[i-1] = char_from_devol[i-1]/(total_devol[i-1]+VSMALL);
                    }
                    else
                    {
                      char_yield[i-1] = char_from_devol[i-1]/(total_devol[i-1]);
                      dmdt[layer_1][i-1] = -R_b[drying_front][i-1]/MOISTURE_FRACTION_WB;
                    }
                    if (m[layer_2][i-1] - R_b[devol_front][i-1]*dt <= 0.)
                    {
                      R_b[devol_front][i-1] = m[layer_2][i-1]/dt;
                    }
                    dmdt[layer_2][i-1] = R_b[drying_front][i-1]/MOISTURE_FRACTION_DB_ - R_b[devol_front][i-1];
                    if (combustion_flag == 1)
                    {
                      if (m[layer_3][combustion_layer]- R_b[char_front][combustion_layer]*dt <= 0. )
                      {
                        R_b[char_front][combustion_layer] = m[layer_3][combustion_layer]/dt;
                      }

                    }

                    dmdt[layer_3][i-1] = R_b[char_produced][i-1] - R_b[char_front][i-1];

                    if (char_yield[i-1] > 0.0)
                    {
                      dmdt[layer_4][i-1] = R_b[char_front][i-1]*ASH_MASS_FRACTION/char_yield[i-1];
                    }
                    else
                    {
                      dmdt[layer_4][i-1] = 0.0;
                    }

                    m[layer_1][i-1] = m[layer_1][i-1] + dmdt[layer_1][i-1]*dt;
                    m[layer_2][i-1] = m[layer_2][i-1] + dmdt[layer_2][i-1]*dt;
                    m[layer_3][i-1] = m[layer_3][i-1] + dmdt[layer_3][i-1]*dt;
                    m[layer_4][i-1] = m[layer_4][i-1] + dmdt[layer_4][i-1]*dt;

                    for (j = 1; j <= 4; j++)
                    {
                      if (m[j-1][i-1] < 0.0)
                      {
                        m[j-1][i-1] = 0.0;
                      }
                    }
                  }


                  /* --------------------------------------------------------------------- */

                  /* Output to file (and possibly to screen) */
                  /* --------------------------------------------------------------------- */
                  if ((iter_count % output_every) == 0)
                  {
                    if (VERBOSITY_)
                    {
                      printf("T at time = %e s:\n",t);
                      for (i = 1; i <= FINE_PARTICLE_MESH_; i++)
                      {
                        printf("%i %f - ",i,T->ve[i-1]);
                      }
                      printf("\n");
                      printf("T at time = %e s:\n",t);
                      for (j = 1; j <= FINE_PARTICLE_MESH_; j++)
                      {
                        printf(" | ");
                        for (i = 1; i <= 4; i++)
                        {
                          printf("%e ",m[i-1][j-1]);
                        }
                      }
                      printf("\n");
                    }


                    fprintf(fp,"time %e ",t);
                    fprintf(fp,"temperatures ");

                    for (i = 1; i <= FINE_PARTICLE_MESH_; i++)
                    {
                      fprintf(fp,"%e ",T->ve[i-1]);
                    }
                    fprintf(fp,"%e ",T_outer_boundary);


                    for (j = 1; j <= 4; j++)
                    {
                      fprintf(fp,"masses ");
                      for (i = 1; i <= FINE_PARTICLE_MESH_; i++)
                      {
                        for (j = 1; j <= 4; j++)
                        {
                          fprintf(fp,"%e ",m[j-1][i-1]);
                        }
                      }
                      fprintf(fp,"radius %e ",rb);

                    }
                    fprintf(fp,"R_b ");
                    for (i = 1; i <= FINE_PARTICLE_MESH_; i++)
                    {
                      for (j = 1; j <= 4; j++)
                      {
                        fprintf(fp,"%e ",R_b[j-1][i-1]);
                      }
                    }
                    fprintf(fp,"Thermal_time ");
                    for (i = 1; i <= FINE_PARTICLE_MESH_; i++)
                    {
                      fprintf(fp,"%e ",ThermalTimeScale[i-1]);
                    }
                    fprintf(fp,"\n");

                  }
                  /* -------------------------------------------------------- */
                  // scalar sumFrac=0.0;
                  // for (size_t i = 0; i <= 3; i++) {
                  //   for (size_t j = 0; j < FINE_PARTICLE_MESH_; j++) {
                  //     Info << "xi" << i << j << " " << xi[i][j] << "...";
                  //     sumFrac+=xi[i][j];
                  //   }
                  //   Info << "layer " << i << nl;
                  // }
                  // Info << "sumFrac " << sumFrac << nl;
                }

                    exit(EXIT_FAILURE);
                fclose(fp);
                /* ================================================= */

              }

              int main(int argc, char *argv[])
              {
                #include "setRootCase.H"
                #include "createTime.H"
                // OpenFOAM style code
                readCoeff(runTime);


                scalar Temp = 2.0;
                scalar testA = 3.0*Foam::pow(Temp,2.0);
                Info << testA << nl;

                material = 1;
                shape = sphere;
                r_init = PARTICLE_RADIUS_;
                L1 = 2.0*r_init;
                L2 = 2.0*r_init;
                L3 = 2.0*r_init;
                m_init = rho(layer_1,T_P_INIT)*volume_of_element(0.0, r_init);
                particle_volume0 = volume_of_element(0.0, r_init);
                initialize_LHVs_and_Ms(0.18); /* assumes a char fraction of 0.18 (only relevant for volatile LHV) */
                Info << "code start" << nl;
                discretized_psm();

                // clock_t end = clock();
                // scalar elapsed_time = (end - start)/(scalar)CLOCKS_PER_SEC;
                // printf("Elapsed time: %.2f.\n", elapsed_time);

                return 0;
              }
