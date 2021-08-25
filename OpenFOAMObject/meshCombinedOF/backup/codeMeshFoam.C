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


// /*Read file parameters*/
// #define CONFIG_LINE_BUFFER_SIZE 100
// #define CONFIG_LINE_SIZE 50

/* VERSION: discretized version */

// #define VERBOSITY_ 1		/* turn on or off printout to screen: 0 - suppress most printout, 1 - allow printout */
// #define SAVE_EVERY_ 1000 //100000

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

/* sovler time parameters */
// #define TIME_DT_     1.0e-3           /* s */
// #define TIME_TOTAL_  100.0            /* s */

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


/* devolatilization kinetics parameters */
//1:wood to gas, 2:wood to tar, 3:wood to char
// H. Strom H. Thunman 2013
// #define DevKinA1 1.30e+08 /* (s-1) */
// #define DevKinE1 1.40e+05 /* (J/mol) */
// #define DevKinA2 2.00e+08 /* (s-1) */
// #define DevKinE2 1.33e+05 /* (J/mol) */
// #define DevKinA3 1.08e+07 /* (s-1) */
// #define DevKinE3 1.21e+05 /* (J/mol) */

// Wagenaar 1994
#define DevKinA1 1.10e+11 /* (s-1) */
#define DevKinE1 1.77e+05 /* (J/mol) */
#define DevKinA2 9.28e+09 /* (s-1) */
#define DevKinE2 1.49e+05 /* (J/mol) */
#define DevKinA3 3.05e+07 /* (s-1) */
#define DevKinE3 1.25e+05 /* (J/mol) */


// #define DevKinA1 0. /* (s-1) */
// #define DevKinA2 0. /* (s-1) */
// #define DevKinA3 0. /* (s-1) */

// #define FINE_PARTICLE_MESH_ 40
// #define FINE_PARTICLE_MESH_DOUBLE_ 40.0
// // OpenFOAM style code
// IOdictionary particleInfoDict_
// (
//   IOobject
//   (
//     "particleInfoDict",
//     mesh.time().constant(),
//     mesh,
//     IOobject::MUST_READ_IF_MODIFIED,
//     IOobject::NO_WRITE
//   )
// );

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

clock_t start;

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
  particleInfoDict_.lookup("VERBOSITY")>> VERBOSITY_;
  particleInfoDict_.lookup("SAVE_EVERY")>> SAVE_EVERY_;
  particleInfoDict_.lookup("TIME_DT")>> TIME_DT_;
  particleInfoDict_.lookup("TIME_TOTAL")>> TIME_TOTAL_;
  particleInfoDict_.lookup("MOISTURE_FRACTION_DB")>> MOISTURE_FRACTION_DB_;
  particleInfoDict_.lookup("PARTICLE_RADIUS")>> PARTICLE_RADIUS_;
  particleInfoDict_.lookup("DRYING_SHRINKAGE_VOLUME")>> DRYING_SHRINKAGE_VOLUME_;
  particleInfoDict_.lookup("T_REACTOR")>> T_REACTOR_;
  particleInfoDict_.lookup("T_RADIATION")>> T_RADIATION_;
  particleInfoDict_.lookup("MASS_FRAC_O2")>> MASS_FRAC_O2_;
  particleInfoDict_.lookup("DENSITY_INITIAL")>> DENSITY_INITIAL_;
  particleInfoDict_.lookup("FINE_PARTICLE_MESH")>> FINE_PARTICLE_MESH_;
  particleInfoDict_.lookup("FINE_PARTICLE_MESH_DOUBLE")
                    >> FINE_PARTICLE_MESH_DOUBLE_;
  particleInfoDict_.lookup("K_P_WET")>> K_P_WET_;
  particleInfoDict_.lookup("K_P_DRY")>> K_P_DRY_;
  particleInfoDict_.lookup("K_P_CHAR")>> K_P_CHAR_;

  MOISTURE_FRACTION_WB =MOISTURE_FRACTION_DB_/(1.0 + MOISTURE_FRACTION_DB_);
  ASH_MASS_FRACTION_DB = ASH_MASS_FRACTION/(1.0-MOISTURE_FRACTION_WB);
}
// void __attribute__ ((constructor)) premain()
// {
//     // start = clock();
//     FILE *fpinput;
//     char buf[CONFIG_LINE_BUFFER_SIZE];
//     char buf2[CONFIG_LINE_BUFFER_SIZE];
//     char buf3[CONFIG_LINE_BUFFER_SIZE];
//     float tempData[CONFIG_LINE_SIZE];
//
//     label index_line=0;
//     if((fopen("codeMeshInput.txt", "rt")) == NULL)
//     {
//         printf("file codeMeshInput.txt is not found\n");
//         exit(EXIT_FAILURE);
//     }
//     fpinput= fopen("codeMeshInput.txt", "rt");
//     while(! feof(fpinput))
//     {
//         fgets(buf, CONFIG_LINE_BUFFER_SIZE, fpinput);
//         sscanf(buf, "%s %s", buf2, buf3);
//         tempData[index_line]=atof(buf3);
//         index_line++;
//     }
//
//     VERBOSITY_= tempData[0];
//     SAVE_EVERY_ = tempData[1];
//     TIME_DT_ = tempData[2];
//     TIME_TOTAL_ = tempData[3];
//     MOISTURE_FRACTION_DB_ = tempData[4];
//     PARTICLE_RADIUS_ = tempData[5];
//     DRYING_SHRINKAGE_VOLUME_ = tempData[6];
//     T_REACTOR_ = tempData[7];
//     T_RADIATION_ = tempData[8];
//     MASS_FRAC_O2_ = tempData[9];
//     DENSITY_INITIAL_ = tempData[10];
//     FINE_PARTICLE_MESH_ = tempData[11];
//     FINE_PARTICLE_MESH_DOUBLE_ = tempData[12];
//     K_P_WET_ = tempData[13];
//     K_P_DRY_ = tempData[14];
//     K_P_CHAR_ = tempData[15];
//
//
//     MOISTURE_FRACTION_WB =MOISTURE_FRACTION_DB_/(1.0 + MOISTURE_FRACTION_DB_);
//     ASH_MASS_FRACTION_DB = ASH_MASS_FRACTION/(1.0-MOISTURE_FRACTION_WB);
//
// //     DRY_DENSITY = DENSITY_INITIAL_*(1.-MOISTURE_FRACTION_WB)*(1./(1.-DRYING_SHRINKAGE_VOLUME_));
//     fclose(fpinput);
// }

/* model indices */
enum{layer_1,layer_2,layer_3,layer_4};
enum{boundary_1,boundary_2,boundary_3,boundary_4};
enum{drying_front,devol_front,char_front,char_produced};
enum{evaporation,devolatilization,char_combustion};
enum{cylinder,sphere,parallelepiped};

/* property indices */
enum{index_CO2,index_H2,index_CO,index_H2O,index_CH4,index_C2H4,index_C10H8,index_C,index_C2H6,index_C3H8,index_C6H6O,index_volatiles};

/* Redux statics */
label material, shape;

/* Same listing as species listing in mixture template in Fluent */
enum{H2O_index,O2_index,CH4_index,H2_index,CO_index,CO2_index,N2_index};

/* functions */
/* ======================================================================== */
void initialize_LHVs_and_Ms(scalar char_fraction)
{
    /* Lower heating values (LHVs) */
    LHV[index_CO2] = 0.0;				/* per definition */
    LHV[index_H2] = 120.0e6;			/* J/kg D&D p. 26 */
    LHV[index_CO] = 10.25e6;			/* J/kg D&D p. 26 */
    LHV[index_H2O] = 0.0;				/* per definition */
    LHV[index_CH4] = 50.0e6;			/* J/kg D&D p. 26 */
    LHV[index_C2H4] = 47.7e6;			/* J/kg D&D p. 26 */
    LHV[index_C10H8] = 39.48e6;		/* J/kg Alberto's code */
    LHV[index_C] = 32.79e6;			/* J/kg Alberto's code */
    LHV[index_C2H6] = 47.6e6;			/* J/kg D&D p. 26 */
    LHV[index_C3H8] = 46.3e6;			/* J/kg D&D p. 26 */
    LHV[index_C6H6O] = 32.45e6;		/* J/kg http://www.nist.gov/data/PDFfiles/jpcrd6.pdf OR http://pac.iupac.org/publications/pac/pdf/1961/pdf/0201x0125.pdf */
    LHV[index_volatiles] = (18.93e6 - 32.57e6*char_fraction)/(1.0 - char_fraction);	/* J/kg Alberto's code */
    /* Molar masses */
    M[index_CO2] = 44.01e-3;			/* kg/mole */
    M[index_H2] = 2.0*1.008e-3;		/* kg/mole */
    M[index_CO] = 28.010e-3;			/* kg/mole */
    M[index_H2O] = 18.01528e-3;		/* kg/mole */
    M[index_CH4] = 16.04e-3;			/* kg/mole */
    M[index_C2H4] = 28.05e-3;			/* kg/mole */
    M[index_C10H8] = 128.17e-3;		/* kg/mole */
    M[index_C] = 12.011e-3;			/* kg/mole */
    M[index_C2H6] = 30.07e-3;			/* kg/mole */
    M[index_C3H8] = 44.1e-3;			/* kg/mole */
    M[index_C6H6O] = 94.11e-3;		/* kg/mole */
}

scalar linear_interpolation(scalar X, label n_elements_in_list)
{
    label i = 0;
    scalar my_value;

    if (X <= X_list[0])
    {
        my_value = Y_list[0];
    }
    else if (X >= X_list[n_elements_in_list-1])
    {
        my_value = Y_list[n_elements_in_list-1];
    }
    else
    {
        while (!((X >= X_list[i-1]) && (X < X_list[i])))
        {
            i = i + 1;
        }
        my_value = Y_list[i-1] + (Y_list[i] - Y_list[i-1])*(X - X_list[i-1])/(X_list[i] - X_list[i-1]);
    }

    return my_value;
}

scalar c_p(label layer, scalar T)
{
    /* returns c_p in J/kg,K for the particle layer */
    /* N.B.: currently, all materials use the same expressions! */
    scalar heat_capacity=0.0;
    scalar c_p_wood;
    scalar c_p_water = 4.309e3;			/* c_p for water in J/kg,K */
    scalar A;								/* correction factor in J/kg,K */
    scalar Y_mois = 1.0 - 1.0/(1.0 + MOISTURE_FRACTION_DB_);
    //     scalar hcgas;

    if (layer == layer_1)
    {
        /* moist wood */
        c_p_wood = 4.206*T - 37.7; /* eq. (24.i) Thunman et al., Energy & Fuels 2001 */
        A = 1.0e3*((0.02355*T - 1.320*Y_mois/(1.0 - Y_mois) - 6.191)*Y_mois/(1.0 - Y_mois));
        heat_capacity = c_p_wood*(1.0 - Y_mois) + c_p_water*Y_mois + A;

//         heat_capacity = 1000.*(0.1031+0.003867*T+4.19*MOISTURE_FRACTION_DB_)/(1.+MOISTURE_FRACTION_DB_); /* Properties of Wood for Combustion Analysis */
    }
    else if (layer == layer_2)
    {
        /* dry wood */
        heat_capacity = 4.206*T - 37.7; /* eq. (24.i) Thunman et al., Energy & Fuels 2001 */
//         heat_capacity = 1000.*(0.1031+0.003867*T); /* Properties of Wood for Combustion Analysis */
    }
    else if (layer == layer_3)
    {
        /* char */
        heat_capacity = -334.0 + 4410.0e-3*T - 3160.0e-6*Foam::pow(T,2.0)
         + 1010.0e-9*Foam::pow(T,3.0) - 119.0e-12*Foam::pow(T,4.0); /* Table 5 Thunman et al., Energy & Fuels 2001 */
//         heat_capacity = 1000.*(1.39+0.00036*T); /* Properties of Wood for Combustion Analysis */
    }
    else if (layer == layer_4)
    {
        heat_capacity = 754.0 + 0.586*(T-273.15);	/* Sven */
    }
    else
    {
        printf("ERROR in c_p function!!!\n");
    }

    return heat_capacity;
}

scalar k_p(label layer, scalar T)
{
    /* returns heat conductivity (W/m,K) for each layer as a function of temperature */
    scalar heat_conductivity=0.0, kgas=0.0;
//
//     if (layer == layer_1)
//     {
//         heat_conductivity = 0.13;
//     }
//     else if (layer == layer_2)
//     {
//         heat_conductivity = 0.1;
//     }
//     else if (layer == layer_3)
//     {
//         heat_conductivity = 0.063;
//     }
//     else if (layer == layer_4)
//     {
//         kgas = (-0.000000000003493)*pow(T,3.0) + 0.000000003319264*pow(T,2.0) + 0.000060059499759*T + 0.008533051948052;
//         heat_conductivity = 1.03*(1.0-0.65) + 0.65*kgas;	/* Sven */
//     }
//     else
//     {
//         printf("ERROR in heat conductivity function!!\n");
//     }


    /*Lu PhD 2006*/
    //wet, dry, and char

    //Perr and Degiovanni 1990, Control-volume formulation of simultaneous transfers in anisotropic porous media: Simulations of softwood drying at low and high temperature
    //*k_parallell=2*k_perpendicular

//     if (layer == layer_1)
//     {
//         if (MOISTURE_FRACTION_DB_ <= 0.4)
//         {
//             heat_conductivity =  (0.129 - 0.0049*MOISTURE_FRACTION_DB_)*(1.0 + 0.001*(2.05 + 4.*MOISTURE_FRACTION_DB_)*(T - 273.))*(0.986 + 2.695*MOISTURE_FRACTION_DB_)*1.5;
//         }
//         else
//         {
//             heat_conductivity =  (0.0932 + 0.0065*MOISTURE_FRACTION_DB_)*(1.0 + 0.00365*(T - 273.))*(0.986 + 2.695*MOISTURE_FRACTION_DB_)*1.5;
//         }
//         heat_conductivity = 0.13;
//     }
//     else if (layer == layer_2)
//     {
//         heat_conductivity =  (0.129 )*(1.0 + 0.001*(2.05 )*(T - 273.))*(0.986)*1.5;



    /*MacLean 1941 from Morten PhD Thesis*/
    /*k_parallell=2.5k_perpendicular*/
//         if (MOISTURE_FRACTION_DB_ < 0.4)
//         {
//             heat_conductivity =  (2.37e-2 + 2.0e-4*DRY_DENSITY*(1.0 + 2.0*MOISTURE_FRACTION_DB_))*(1.0+2.5)/2.0;
//         }
//         else
//         {
//             heat_conductivity =  (2.37e-2 + 2.0e-4*DRY_DENSITY*(1.0 + 2.5*MOISTURE_FRACTION_DB_))*(1.0+2.5)/2.0;
//         }

    if (layer == layer_1)
    {
        heat_conductivity = K_P_WET_; //
    }
    else if (layer == layer_2)
    {
        heat_conductivity =  K_P_DRY_; //
    }
    else if (layer == layer_3)
    {
//         heat_conductivity = 0.052; //K. W. Ragland, D. J. Aerts, Properties of Wood for Combustion Analysis Wheast cites "R. C. (1976). Handbook of Chemistry and Physics, CRC Press, Cleveland, Ohio, p. E-5."
        heat_conductivity = K_P_CHAR_;
    }
    else if (layer == layer_4)
    {
        kgas = (-0.000000000003493)*Foam::pow(T,3.0)
         + 0.000000003319264*Foam::pow(T,2.0)
         + 0.000060059499759*T + 0.008533051948052;
        heat_conductivity = 1.03*(1.0-0.65) + 0.65*kgas;	/* Sven */
    }
    else
    {
        printf("ERROR in heat conductivity function!!\n");
    }


    return heat_conductivity;
}

scalar rho(label layer, scalar T)
{
    /* returns density (kg/m3) for each layer as a function of temperature */
    scalar density = 0.0;
    scalar dgas;

    if (material == 1)  /* in this version of the code there is only one material implemented in this function */
    {
        if (layer == layer_1)
        {
            density = DENSITY_INITIAL_;
        }
        else if (layer == layer_2)
        {
            density = (1.0 - MOISTURE_FRACTION_WB)*DENSITY_INITIAL_;
        }
        else if (layer == layer_3)
        {
            density = 350.0;
        }
        else if (layer == layer_4)
        {
            dgas = 101325.0*(2.0*14.00672*1.0e-3)/(8.3145*T);
            density = 2000.0*(1.0-0.65) + 0.65*dgas;	/* Sven */
        }
        else
        {
            printf("ERROR in density function!!\n");
        }
    }
    else
    {
        printf("ERROR in density function!!\n");
    }

    return density;
}

scalar gas_cp(label index, scalar T)
{
    /* returns heat capacity of the gas in J/mol,K */
    label i;
    scalar A, B, C, D, E;
    scalar temp=0.0;
    scalar cp=0.0;
    scalar T_list_C10H8[19] = {50.0,100.0,150.0,200.0,273.15,298.15,300.0,400.0,500.0,600.0,700.0,800.0,900.0,1000.0,1100.0,1200.0,1300.0,1400.0,1500.0};
    scalar Cp_list_C10H8[19] = {36.18,47.50,63.89,84.99,120.52,133.02,133.94,181.16,220.70,252.37,277.77,298.43,315.50,329.77,341.8,352.0,360.8,368.2,374.7};
    scalar T_list_C2H6[31] = {100.0,200.0,298.15,300.0,400.0,500.0,600.0,700.0,800.0,900.0,1000.0,1100.0,1200.0,1300.0,1400.0,1500.0,1600.0,1700.0,1800.0,1900.0,2000.0,2100.0,2200.0,2300.0,2400.0,2500.0,2600.0,2700.0,2800.0,2900.0,3000.0};
    scalar Cp_list_C2H6[31] = {35.70,42.30,52.49,52.71,65.46,77.94,89.19,99.14,107.94,115.71,122.55,128.55,133.80,138.39,142.40,145.90,148.98,151.67,154.04,156.14,158.00,159.65,161.12,162.43,163.61,164.67,165.63,166.49,167.28,168.00,168.65};
    scalar T_list_C3H8[19] = {50.0,100.0,150.0,200.0,273.15,298.15,300.0,400.0,500.0,600.0,700.0,800.0,900.0,1000.0,1100.0,1200.0,1300.0,1400.0,1500.0};
    scalar Cp_list_C3H8[19] = {34.06,41.30,48.79,56.07,68.74,73.60,73.93,94.01,112.59,128.70,142.67,154.77,165.35,174.60,182.67,189.74,195.85,201.21,205.89};
    scalar T_list_C6H6O[19] = {50.0,100.0,150.0,200.0,273.15,298.15,300.0,400.0,500.0,600.0,700.0,800.0,900.0,1000.0,1100.0,1200.0,1300.0,1400.0,1500.0};
    scalar Cp_list_C6H6O[19] = {33.91,41.38,54.19,69.65,94.61,103.22,103.86,135.79,161.91,182.48,198.84,212.14,223.19,232.49,240.41,247.20,253.06,258.12,262.52};
    //     scalar BensonBuss_H = 0.85;
    //     scalar BensonBuss_C = 3.75;
    //     scalar BensonBuss_O = 3.40;

    if (index == index_CO2)
    {
        if (T < 1200.0)
        {
            /* valid to 1200K */
            A = 24.99735;
            B = 55.18696;
            C = -33.69137;
            D = 7.948387;
            E = -0.136638;
        }
        else
        {
            /* valid from 1200 to 6000 K */
            A = 58.16639;
            B = 2.720074;
            C = -0.492289;
            D = 0.038844;
            E = -6.447293;
        }
        /* Shomate Equation from NIST Webbook */
        temp = T/1000.0;
        cp = A + B*temp + C*Foam::pow(temp,2.0) + D*Foam::pow(temp,3.0)
        + E/Foam::pow(temp,2.0);
    }
    else if (index == index_H2)
    {
        if (T < 1000.0)
        {
            /* valid from 298 to 1000K */
            A = 33.066178;
            B = -11.363417;
            C = 11.432816;
            D = -2.772874;
            E = -0.158558;
        }
        else
        {
            /* valid from 1000 to 2500K */
            A = 18.563083;
            B = 12.257357;
            C = -2.859786;
            D = 0.268238;
            E = 1.977990;
        }
        /* Shomate Equation from NIST Webbook */
        temp = T/1000.0;
        cp = A + B*temp + C*Foam::pow(temp,2.0) + D*Foam::pow(temp,3.0)
        + E/Foam::pow(temp,2.0);
    }
    else if (index == index_CO)
    {
        /* valid to 1300K */
        A = 25.56759;
        B = 6.096130;
        C = 4.054656;
        D = -2.671301;
        E = 0.131021;
        /* Shomate Equation from NIST Webbook */
        temp = T/1000.0;
        cp = A + B*temp + C*Foam::pow(temp,2.0) + D*Foam::pow(temp,3.0)
        + E/Foam::pow(temp,2.0);
    }
    else if (index == index_H2O)
    {
        /* valid from 500 to 1700 K */
        A = 30.09200;
        B = 6.832514;
        C = 6.793435;
        D = -2.534480;
        E = 0.082139;
        /* Shomate Equation from NIST Webbook */
        temp = T/1000.0;
        cp = A + B*temp + C*Foam::pow(temp,2.0) + D*Foam::pow(temp,3.0)
         + E/Foam::pow(temp,2.0);
    }
    else if (index == index_CH4)
    {
        /* valid to 1300K */
        A = -0.703029;
        B = 108.4773;
        C = -42.52157;
        D = 5.862788;
        E = 0.678565;
        /* Shomate Equation from NIST Webbook */
        temp = T/1000.0;
        cp = A + B*temp + C*Foam::pow(temp,2.0) + D*Foam::pow(temp,3.0)
        + E/Foam::pow(temp,2.0);
    }
    else if (index == index_C2H4)
    {
        if (T < 1200.0)
        {
            /* valid from 298 to 1200K */
            A = -6.387880;
            B = 184.4019;
            C = -112.9718;
            D = 28.49593;
            E = 0.315540;
        }
        else
        {
            /* valid from 1200 K to 6000 K */
            A = 106.5104;
            B = 13.73260;
            C = -2.628481;
            D = 0.174595;
            E = -26.14469;
        }
        /* Shomate Equation from NIST Webbook */
        temp = T/1000.0;
        cp = A + B*temp + C*Foam::pow(temp,2.0) + D*Foam::pow(temp,3.0)
        + E/Foam::pow(temp,2.0);
    }
    else if (index == index_C10H8)
    {
        for (i = 1; i <= 19; i++)
        {
            X_list[i-1] = T_list_C10H8[i-1];
            Y_list[i-1] = Cp_list_C10H8[i-1];
        }
        cp = linear_interpolation(T, 19);
    }
    else if (index == index_C)
    {
        /* specific heat of graphite (solid) - valid from 250 to 3000 K (taken from NIST Webbook)
         *        %     cp = 0.538657 + 9.11129e-6*T - 90.2725*T^(-1) - 43449.3*T^(-2) + 1.59309e7*T^(-3) - 1.43688e9*T^(-4); % cal/g*K
         *        %     cp = cp*12.0107;    % (*g/mol) --> cal/mol,K
         *        %     cp = cp*4.184;      % (*J/cal) --> J/mol,K */
        cp = (0.538657 + 9.11129e-6*T - 90.2725*Foam::pow(T,-1.0)
        - 43449.3*Foam::pow(T,-2.0) + 1.59309e7*Foam::pow(T,-3.0)
        - 1.43688e9*Foam::pow(T,-4.0))*12.0107*4.184; /* J/mol*K */
    }
    else if (index == index_C2H6)
    {
        for (i = 1; i <= 31; i++)
        {
            X_list[i-1] = T_list_C2H6[i-1];
            Y_list[i-1] = Cp_list_C2H6[i-1];
        }
        cp = linear_interpolation(T, 31);
    }
    else if (index == index_C3H8)
    {
        for (i = 1; i <= 19; i++)
        {
            X_list[i-1] = T_list_C3H8[i-1];
            Y_list[i-1] = Cp_list_C3H8[i-1];
        }
        cp = linear_interpolation(T, 19);
    }
    else if (index == index_C6H6O)
    {
        for (i = 1; i <= 19; i++)
        {
            X_list[i-1] = T_list_C6H6O[i-1];
            Y_list[i-1] = Cp_list_C6H6O[i-1];
        }
        cp = linear_interpolation(T, 19);
    }
    else
    {
        printf("ERROR in gas_cp function!!! (1)\n");
    }

    return cp;
}
/* ======================================================================== */

scalar deltaHvap(scalar T)
{
    /* returns heat of vaporization of water in J/kg for T in Kelvin */
    /* on the interval 273-433K */
    label i;
    scalar T_list[9] = {273.15,298.15,313.15,333.15,353.15,373.15,393.15,413.15,433.15};
    scalar dH_list[9] = {45.054e3,43.99e3,43.35e3,42.482e3,41.585e3,40.657e3,39.684e3,38.643e3,37.518e3};
    scalar dH;

    for (i = 1; i <= 9; i++)
    {
        X_list[i-1] = T_list[i-1];
        Y_list[i-1] = dH_list[i-1];
    }
    dH = linear_interpolation(T, 9);
    dH = dH/18.0e-3; /* convert J/mol to J/kg */

    return dH;
    //     return 2264000.705;
}

scalar deltaHdevol(label i, scalar T, scalar char_fraction)
{
    /* returns heat of devolatilization in J/mole for T in Kelvin */
    scalar dH = 0.0;

    return dH;
}

scalar volume_of_element(scalar r1, scalar r2)
{
    /* returns volume in m3 of element */
    /* 1 = cylinder, 2 = sphere, 3 = parallelepiped */
    scalar vol=0.0;
    scalar eta=0.0;

    if (shape == cylinder)
    {
        eta = L1 - L3;
        if (L3 == L1)
        {
            vol = 2*M_PI*(Foam::pow(r2,3.0) - Foam::pow(r1,3.0));
        }
        else if (L3 > L1)
        {
            vol = 2*M_PI*(Foam::pow(r2,3.0) - Foam::pow(r2,2.0)*eta/2)
            - 2*M_PI*(Foam::pow(r1,3.0) - Foam::pow(r1,2.0)*eta/2);
        }
        else if (L3 < L1)
        {
            vol = 2*M_PI*(Foam::pow(r2,3.0) + Foam::pow(r2,2.0)*eta
            + 0.25*Foam::pow(eta,2.0)) - 2*M_PI*(Foam::pow(r1,3.0)
            + Foam::pow(r1,2.0)*eta + 0.25*Foam::pow(eta,2.0));
        }
    }
    else if (shape == sphere)
    {
        vol = 4.0*M_PI*(Foam::pow(r2,3.0))/3.0
            - 4.0*M_PI*(Foam::pow(r1,3.0))/3.0;
    }
    else if (shape == parallelepiped)
    {
        vol = 8*Foam::pow(r2,3.0)
        + 4*Foam::pow(r2,2.0)*((L2-L1) + (L3-L1) + 2*(L2-L1)*(L3-L1))
        - (8*Foam::pow(r1,3.0) + 4*Foam::pow(r1,2.0)*((L2-L1) + (L3-L1)
        + 2*(L2-L1)*(L3-L1)));
    }
    else
    {
        printf("ERROR in volume of element function!!!\n");
    }

    return vol;
}

scalar surface_area(scalar r)
{
    /* returns surface area in m2 for the surface */
    /* 1 = cylinder, 2 = sphere, 3 = parallellepiped */
    scalar surf=0.0;
    scalar eta=0.0;

    if (shape == cylinder)
    {
        eta = L1 - L3;
        if (L3 == L1)
        {
            surf = 6.0*M_PI*Foam::pow(r,2.0);
        }
        else if (L3 > L1)
        {
            surf = 2.0*M_PI*(3.0*Foam::pow(r,2.0) - r*eta);
        }
        else
        {
            surf = 2.0*M_PI
            *(3.0*Foam::pow(r,2.0) + 2.0*r*eta + 0.25*Foam::pow(eta,2.0));
        }
    }
    else if (shape == sphere)
    {
        surf = 4.0*M_PI*(Foam::pow(r,2.0));
    }
    else if (shape == parallelepiped)
    {
        surf = 24.0*Foam::pow(r,2.0)
        + 8.0*r*((L2-L1) + (L3-L1) + 2.0*(L2-L1)*(L3-L1));
    }
    else
    {
        printf("ERROR in surface area function!!!\n");
    }

    return surf;
}

scalar radius_from_volume(scalar V)
{
    scalar r0, r1;
    scalar f=0.0, f_prime=0.0;
    scalar eta = L1 - L3;
    label i = 0;

    r0 = 1.0*L1;	/* initial guess */
    r1 = 0.5*L1;

    while ( (fabs((r0-r1)/r0) > MY_QUITE_SMALL) && (i <= MY_MAXIMUM_NEWTON_ITER) )
    {
        i = i + 1;
        r0 = r1;

        if (shape == cylinder)
        {
            if (eta == 0)
            {
                f = (2.0*M_PI*Foam::pow(r0,3.0) - V);
                f_prime = 6.0*M_PI*Foam::pow(r0,2.0);
            }
            else if (L3 > L1)
            {
                f = (2.0*M_PI*(Foam::pow(r0,3.0)
                - Foam::pow(r0,2.0)*eta/2.0) - V);
                f_prime = 2.0*M_PI*(3.0*Foam::pow(r0,2.0) - r0*eta);
            }
            else
            {
                f = (2.0*M_PI*(Foam::pow(r0,3.0)
                + Foam::pow(r0,2.0)*eta + 0.25*Foam::pow(eta,2.0)) - V);
                f_prime = 2.0*M_PI*(3.0*Foam::pow(r0,2.0) + 2.0*r0*eta);
            }
        }
        else if (shape == sphere)
        {
            f = (4.0*M_PI*Foam::pow(r0,3.0)/3.0 - V);
            f_prime = 4.0*M_PI*Foam::pow(r0,2.0);
        }
        else if (shape == parallelepiped)
        {
            f = (8.0*Foam::pow(r0,3.0)
            + 4.0*Foam::pow(r0,2.0)*((L2-L1) + (L3-L1) + 2*(L2-L1)*(L3-L1)) - V);
            f_prime = 8.0*3.0*Foam::pow(r0,2.0)
            + 4.0*2.0*r0*((L2-L1) + (L3-L1) + 2*(L2-L1)*(L3-L1));
        }
        else
        {
            printf("ERROR in radius from volume function!!\n");
        }

        r1 = r0 - f/f_prime;
    }

    return r1;
}

scalar radius_from_volume_element(scalar V, scalar r_inner)
{
    scalar r0, r1;
    scalar f=0.0, f_prime=0.0;
    scalar eta = L1 - L3;
    label i = 0;

    r0 = 1.0*L1;	/* initial guess */
    r1 = 0.5*L1;

    while ( (fabs((r0-r1)/r0) > MY_QUITE_SMALL) && (i <= MY_MAXIMUM_NEWTON_ITER) )
    {
        i = i + 1;
        r0 = r1;

        if (shape == cylinder)
        {
            if (eta == 0)
            {
                f = (2.0*M_PI*Foam::pow(r0,3.0) - V);
                f_prime = 6.0*M_PI*Foam::pow(r0,2.0);
            }
            else if (L3 > L1)
            {
                f = (2.0*M_PI*(Foam::pow(r0,3.0) - Foam::pow(r0,2.0)*eta/2.0) - V);
                f_prime = 2.0*M_PI*(3.0*Foam::pow(r0,2.0) - r0*eta);
            }
            else
            {
                f = (2.0*M_PI*(Foam::pow(r0,3.0)
                + Foam::pow(r0,2.0)*eta + 0.25*Foam::pow(eta,2.0)) - V);
                f_prime = 2.0*M_PI*(3.0*Foam::pow(r0,2.0) + 2.0*r0*eta);
            }
            printf("ERROR in radius from volume element function -- NOT PREPARED\n");
        }
        else if (shape == sphere)
        {
            f = (4.0*M_PI*Foam::pow(r0,3.0)/3.0
            - 4.0*M_PI*Foam::pow(r_inner,3.0)/3.0 - V);
            f_prime = 4.0*M_PI*Foam::pow(r0,2.0);
        }
        else if (shape == parallelepiped)
        {
            f = (8.0*Foam::pow(r0,3.0)
            + 4.0*Foam::pow(r0,2.0)*((L2-L1) + (L3-L1) + 2*(L2-L1)*(L3-L1)) - V);
            f_prime = 8.0*3.0*Foam::pow(r0,2.0)
            + 4.0*2.0*r0*((L2-L1) + (L3-L1) + 2*(L2-L1)*(L3-L1));
            printf("ERROR in radius from volume element function -- NOT PREPARED\n");
        }
        else
        {
            printf("ERROR in radius from volume element function!!\n");
        }

        r1 = r0 - f/f_prime;
    }

    return r1;
}

scalar temperature_gradient(scalar Ti, scalar Tj, scalar ri, scalar rj)
{
    scalar dTdr = 0.0;
    //     scalar eta;

    /* currently only for spheres in this version of the code */
    if (shape == sphere)
    {
        /* dTdr = (Ti - Tj)/(ri*(ri/rj - 1.0)); */
        dTdr = (Ti - Tj)/(ri - rj);
    }
    else
    {
        printf("Error in temperature gradient function!\n");
    }

    return dTdr;
}

void update_surface_temperatures(scalar nextT_p3, scalar k_p3, scalar A, scalar r_b3, scalar r_c3, scalar Q_particle_conduction, scalar T_inf, scalar h)
{
    /* currently only for spheres */
	label i = 0;
	scalar f=0.0, f_prime=0.0;
	scalar T0, T1;
	// scalar eta = L1 - L3;

	T0 = T_inf;
	T1 = (T_inf+nextT_p3);

	while ( (fabs((T0-T1)/T0) > MY_QUITE_SMALL) && (i <= MY_MAXIMUM_NEWTON_ITER) )
	{
		i = i + 1;
		T0 = T1;

		if (shape == sphere)
		{
			f = (h*A*(T_inf - T0) + view_factor*emissivity*SIGMA*A
      *(Foam::pow(T_inf,4.0) - Foam::pow(T0,4.0))
      - k_p3*A*(T0 - nextT_p3)/(r_b3 - r_c3));
			f_prime = (-h*A + view_factor*emissivity*SIGMA*A
        *(-4.0*Foam::pow(T0,3.0)) - k_p3*A/(r_b3 - r_c3));

		}
		else
		{
			printf("ERROR in update surface temperatures function!!\n");
		}

		T1 = T0 - f/f_prime;
	}

	T_send[0] = T1;
}

//heat recived by soild, from ANSYS Fluent Theory Guide 18.1, eq16.178
scalar heatRatio(scalar temperature)
{
    // scalar COCO2Ratio = 4.3*Foam::exp(-3390./temperature);
//     return (COCO2Ratio+0.3)/(COCO2Ratio+1.);
    return 1.;//strange
}

scalar charFrontLocation (scalar rb, label i, scalar *V_cell, scalar *V_char, scalar *xc, scalar xi)
{
    scalar rCharFront;

    if (i == FINE_PARTICLE_MESH_-1)
    {
        rCharFront = radius_from_volume(V_char[i]);
    }
    else if (i == 0)
    {
        rCharFront = radius_from_volume(volume_of_element(0.,xc[i+1])+0.5*V_cell[i+1]+xi*V_char[i]);
    }
    else
    {
        rCharFront = radius_from_volume(volume_of_element(0.,xc[i+1])+0.5*V_cell[i+1]+V_char[i]);
    }

    return rCharFront;
}

void update_boundary_temperatures(scalar k_p1, scalar k_p2, scalar k_p3, scalar k_p4, scalar A[4], scalar rb[4], scalar rp[4], scalar T_p[4], scalar T_b[4], scalar Q_evap, scalar Q_devol, scalar Q_char_comb)
{
    //     scalar T0 = 0.0;
    scalar T1 = 0.0;
    scalar T2 = 0.0;
    scalar T3 = 0.0;
    //     scalar eta = L1 - L3;
    scalar nextT_b1;
    scalar nextT_b2;
    scalar nextT_b3;
    scalar CA, CB;

    /* currently only for spheres */

    if (shape == sphere)
    {
        /* new Tb3: */
        CA = A[boundary_3]*k_p4/(rp[layer_4]-rb[boundary_3]);
        CB = A[boundary_3]*k_p3/(rb[boundary_3]-rp[layer_3]);
        T3 = (CA*T_p[layer_4] + CB*T_p[layer_3] - Q_char_comb)/(CA+CB);
        /* new Tb2: */
        CA = A[boundary_2]*k_p3/(rp[layer_3]-rb[boundary_2]);
        CB = A[boundary_2]*k_p2/(rb[boundary_2]-rp[layer_2]);
        T2 = (CA*T_p[layer_3] + CB*T_p[layer_2] - Q_devol)/(CA+CB);
        /* new Tb1: */
        CA = A[boundary_1]*k_p2/(rp[layer_2]-rb[boundary_1]);
        CB = A[boundary_1]*k_p1/(rb[boundary_1]-rp[layer_1]);
        T1 = (CA*T_p[layer_2] + CB*T_p[layer_1] - Q_evap)/(CA+CB);
    }
    else
    {
        printf("ERROR in update boundary temperatures function!!\n");
    }

    nextT_b3 = T3;
    nextT_b2 = T2;
    nextT_b1 = T1;

    /* return temperatures in array T_send */
    T_send[0] = nextT_b1;
    T_send[1] = nextT_b2;
    T_send[2] = nextT_b3;
}


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
        volume_sum = volume_sum + volume_of_element(0.0,rb)/FINE_PARTICLE_MESH_DOUBLE_;
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
            //             if ((j > 1) && (j < FINE_PARTICLE_MESH_))
            //             {
            //                 m[i-1][j-1] = xi[i-1][j-1]*rho(i-1,T->ve[i-1])*volume_of_element(0.5*(xc[j-1]+xc[j]), 0.5*(xc[j-1]+xc[j-2]));
            //             }
            //             else if (j == 1)
            //             {
            //                 m[i-1][j-1] = xi[i-1][j-1]*rho(i-1,T->ve[i-1])*volume_of_element(0.5*(xc[j-1]+xc[j]), 0.5*(xc[j-1]+rb));
            //             }
            //             else
            //             {
            //                 m[i-1][j-1] = xi[i-1][j-1]*rho(i-1,T->ve[i-1])*volume_of_element(0.5*(xc[j-1]+0.0), 0.5*(xc[j-1]+xc[j-2]));
            //             }
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
    exit(EXIT_FAILURE);

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


            R_devol_reac[1-1][i-1] = DevKinA1*Foam::exp(-DevKinE1/(8.3145*T->ve[i-1]))*m[layer_2][i-1];
            R_devol_reac[2-1][i-1] = DevKinA2*Foam::exp(-DevKinE2/(8.3145*T->ve[i-1]))*m[layer_2][i-1];
            R_devol_reac[3-1][i-1] = DevKinA3*Foam::exp(-DevKinE3/(8.3145*T->ve[i-1]))*m[layer_2][i-1];


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
                R_devoSourceimins1High = (DevKinA1*Foam::exp(-DevKinE1/(8.3145*(T->ve[i-1]+1.0))) + DevKinA2*Foam::exp(-DevKinE2/(8.3145*(T->ve[i-1]+1.0))))*m[layer_2][i-1];
                R_devoSourceimins1HighChar = DevKinA3*Foam::exp(-DevKinE3/(8.3145*(T->ve[i-1]+1.0)))*m[layer_2][i-1];

                R_drySourceiHigh = m[layer_1][i]*DryKinA*Foam::exp(-DryKinE/(8.3145*T->ve[i]+1.0));
                //                 if (m[layer_1][i-1] - R_drySourceiHigh/MOISTURE_FRACTION_WB*dt <= MY_EXTREMELY_SMALL)
                //                 {
                //                     R_drySourceiHigh = m[layer_1][i-1]*MOISTURE_FRACTION_WB/dt;
                //                 }
                R_devoSourceiHigh = (DevKinA1*Foam::exp(-DevKinE1/(8.3145*(T->ve[i]+1.0))) + DevKinA2*Foam::exp(-DevKinE2/(8.3145*(T->ve[i]+1.0))))*m[layer_2][i];
                R_devoSourceiHighChar = DevKinA3*Foam::exp(-DevKinE3/(8.3145*(T->ve[i]+1.0)))*m[layer_2][i];
                high = -(deltaHvap(T->ve[i-1]+1.0) + gas_cp(index_H2O, 0.5*((T->ve[i-1]+1.0)+T_outer_boundary))*(T_outer_boundary-(T->ve[i-1]+1.0)))*R_drySourceimins1High- R_devoSourceimins1High*cp_g*(T_outer_boundary-(T->ve[i-1]+1.0)) - (deltaHvap(T->ve[i]+1.0) + gas_cp(index_H2O, 0.5*((T->ve[i]+1.0)+T_outer_boundary))*(T_outer_boundary-(T->ve[i]+1.0)))*R_drySourceiHigh - R_devoSourceiHigh*cp_g*(T_outer_boundary-(T->ve[i]+1.0));

                //Dry Devo low~~~~~~~~~~~~~~~~~~~~~
                R_drySourceimins1Low = m[layer_1][i-1]*DryKinA*Foam::exp(-DryKinE/(8.3145*T->ve[i-1]-1.0));
                //                 if (m[layer_1][i-1] - R_drySourceimins1Low/MOISTURE_FRACTION_WB*dt <= MY_EXTREMELY_SMALL)
                //                 {
                //                     R_drySourceimins1Low = m[layer_1][i-1]*MOISTURE_FRACTION_WB/dt;
                //                 }
                R_devoSourceimins1Low = (DevKinA1*Foam::exp(-DevKinE1/(8.3145*(T->ve[i-1]-1.0))) + DevKinA2*Foam::exp(-DevKinE2/(8.3145*(T->ve[i-1]-1.0))))*m[layer_2][i-1];
                R_devoSourceimins1LowChar = DevKinA3*Foam::exp(-DevKinE3/(8.3145*(T->ve[i-1]-1.0)))*m[layer_2][i-1];
                R_drySourceiLow = m[layer_1][i]*DryKinA*Foam::exp(-DryKinE/(8.3145*T->ve[i]-1.0));
                //                 if (m[layer_1][i-1] - R_drySourceiLow/MOISTURE_FRACTION_WB*dt <= MY_EXTREMELY_SMALL)
                //                 {
                //                     R_drySourceiLow = m[layer_1][i-1]*MOISTURE_FRACTION_WB/dt;
                //                 }
                R_devoSourceiLow = (DevKinA1*Foam::exp(-DevKinE1/(8.3145*(T->ve[i]-1.0))) + DevKinA2*Foam::exp(-DevKinE2/(8.3145*(T->ve[i]-1.0))))*m[layer_2][i];
                R_devoSourceiLowChar = DevKinA3*Foam::exp(-DevKinE3/(8.3145*(T->ve[i]-1.0)))*m[layer_2][i];
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
                R_devoSourceiHigh = (DevKinA1*Foam::exp(-DevKinE1/(8.3145*(T->ve[i]+1.0))) + DevKinA2*Foam::exp(-DevKinE2/(8.3145*(T->ve[i]+1.0))))*m[layer_2][i];
                R_devoSourceiHighChar = DevKinA3*Foam::exp(-DevKinE3/(8.3145*(T->ve[i]+1.0)))*m[layer_2][i];
                high = -(deltaHvap(T->ve[i]+1.0) + gas_cp(index_H2O, 0.5*((T->ve[i]+1.0)+T_outer_boundary))*(T_outer_boundary-(T->ve[i]+1.0)))*R_drySourceiHigh - R_devoSourceiHigh*cp_g*(T_outer_boundary-(T->ve[i]+1.0));

                //Dry Devo low~~~~~~~~~~~~~~~~~~~~~
                R_drySourceiLow = m[layer_1][i]*DryKinA*Foam::exp(-DryKinE/(8.3145*T->ve[i]-1.0));
                R_devoSourceiLow = (DevKinA1*Foam::exp(-DevKinE1/(8.3145*(T->ve[i]-1.0))) + DevKinA2*Foam::exp(-DevKinE2/(8.3145*(T->ve[i]-1.0))))*m[layer_2][i];
                R_devoSourceiLowChar = DevKinA3*Foam::exp(-DevKinE3/(8.3145*(T->ve[i]-1.0)))*m[layer_2][i];
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
        /* --------------------------------------------------------------------- */

      }
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
