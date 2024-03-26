#include "Land_2016.hpp"
// #include <cmath>
#include <algorithm>
#include <math.h>
#include <cstdlib>
#include <cstdio>
#include "cellmodel.hpp"
// #include "../modules/glob_funct.hpp"
// #include <cuda_runtime.h>
// #include <cuda.h>

// next: create a file to dump this
Land_2016::Land_2016()
{


}

Land_2016::~Land_2016()
{

}


void Land_2016::initConsts()
{

}


void Land_2016::initConsts(bool is_skinned, bool BETA, double *y)
{
    // user input
    CONSTANTS[dlambda_dt] = 0; 
    CONSTANTS[lambda] = 1;
    CONSTANTS[Cai] = 0;
    // if (t == -1) {
        RATES[XS] = 0;
        RATES[XW] = 0;
        RATES[TRPN] = 0;
        RATES[TmBlocked] = 1;
        RATES[ZETAS] = 0;
        RATES[ZETAW] = 0;
        RATES[dCd_dt] = 0;
    //     return;
    // }

if (CONSTANTS[lambda] >= 1.2){
    CONSTANTS[lambda] = 1.2;
}
    CONSTANTS[perm50] = 0.35;
    CONSTANTS[TRPN_n] = 2;
    CONSTANTS[koff] = 0.1;
    CONSTANTS[dr] = 0.25;
    CONSTANTS[wfrac] = 0.5;

    CONSTANTS[TOT_A] = 25;
    CONSTANTS[ktm_unblock] = 1;

    CONSTANTS[beta_1] = -2.4;
    CONSTANTS[beta_0] = 2.3;
    CONSTANTS[gamma_idx] = 0.0085;
    CONSTANTS[gamma_wu] = 0.615;
    CONSTANTS[phi] = 2.23;  

    if (is_skinned == true){
    CONSTANTS[nperm] = 2.2;
    ALGEBRAIC[ca50] = 2.5;
    CONSTANTS[Tref] = 40.5;
    CONSTANTS[nu] = 1;
    CONSTANTS[mu] = 1;
    }
    else
    {
    CONSTANTS[nperm] = 5.0;
    ALGEBRAIC[ca50] = 0.805;
    CONSTANTS[Tref] = 120.0;
    CONSTANTS[nu] = 7;
    CONSTANTS[mu] = 3; 
    }
    if (BETA){
        CONSTANTS[beta_1] = -2.4;
        CONSTANTS[beta_0] = 2.3;
    }

    CONSTANTS[k_ws] = 0.004 * CONSTANTS[mu];
    CONSTANTS[k_uw] = 0.026 * CONSTANTS[nu];

    //STATES Variables
    if(y[0]>0) STATES[XS] = fmax(0,y[0]);
    if(y[1]>0) STATES[XW] = fmax(0,y[1]);
    if(y[2]>0) STATES[TRPN] = fmax(0,y[2]);
    STATES[TmBlocked] = y[3];
    STATES[ZETAS] = y[4];
    STATES[ZETAW] = y[5];
    STATES[dCd_dt] = 0.;
    printf("initialisation\n");
    for (int zz = 0; zz<7; zz++){
        printf("%lf\n", RATES[zz]);
    }

    // STATES[XS] = 0.;
    // STATES[XW] = 0.;
    // STATES[TRPN] = 1.0;
    // STATES[TmBlocked] = 0.;
    // STATES[ZETAS] = 0.;
    // STATES[ZETAW] = 0.;

    // seventh state is below, in passive model (dCd_dt)

    CONSTANTS[par_k] = 7;
    CONSTANTS[b] = 9.1;
    CONSTANTS[eta_l] = 200;
    CONSTANTS[eta_s] = 20;
    CONSTANTS[a] = 2.1;

}

// void initConsts(double *CONSTANTS, double *STATES, double type, double conc, double *ic50, double *cvar, bool is_dutta, bool is_cvar,  int offset)
// {
// 	___initConsts(CONSTANTS, STATES, type, offset); 

// 	if(is_dutta == true){
// 		___applyDutta(CONSTANTS, offset);
// 	}

//   if(is_cvar == true){
// 		___applyCvar(CONSTANTS, cvar, offset);
// 	}
	
// }

void Land_2016::computeRates(double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC)
{
// XB model

// lambda = min(1.2,lambda);
// Lfac =  max(0, 1 + beta_0 * (lambda + min(0.87,lambda) - 1.87) );

// double temp_lambda = CONSTANTS[lambda];
// double temp_lambda;
// if (temp_lambda > 0.87){
//     temp_lambda = 0.87;
// }

//  for (int zz = 0; zz<6; zz++){
//         printf("%lf\n", RATES[zz]);
//     }

CONSTANTS[lambda] = fmin(1.2, CONSTANTS[lambda]);
ALGEBRAIC[Lfac]  = fmax(0, 1 + CONSTANTS[beta_0] * (CONSTANTS[lambda] + fmin(0.87, CONSTANTS[lambda]) - 1.87));
// disini gak ngubah apa2 (nilai Lfac gak berubah karena temp lambda selalu pas gitu)
// printf("%lf = 1 + %lf * (%lf + %lf - 1.87)\n", ALGEBRAIC[Lfac], CONSTANTS[beta_0], CONSTANTS[lambda], fmin(0.87, CONSTANTS[lambda]) );
if (ALGEBRAIC[Lfac] < 0){
    ALGEBRAIC[Lfac] = 0 ;
}

ALGEBRAIC[cdw] = CONSTANTS[phi] * CONSTANTS[k_uw] * (1-CONSTANTS[dr])*(1-CONSTANTS[wfrac]) /  ((1-CONSTANTS[dr])*CONSTANTS[wfrac]);
ALGEBRAIC[cds] = CONSTANTS[phi] * CONSTANTS[k_ws] * (1-CONSTANTS[dr])*CONSTANTS[wfrac] / CONSTANTS[dr];

ALGEBRAIC[k_wu] = CONSTANTS[k_uw] * (1/CONSTANTS[wfrac] - 1) - CONSTANTS[k_ws];
ALGEBRAIC[k_su] = CONSTANTS[k_ws] * (1/CONSTANTS[dr] - 1) * CONSTANTS[wfrac]; 
ALGEBRAIC[A] = (0.25 * CONSTANTS[TOT_A]) / ((1-CONSTANTS[dr])*CONSTANTS[wfrac] + CONSTANTS[dr]) * (CONSTANTS[dr]/0.25);


ALGEBRAIC[XU] = (1 - STATES[TmBlocked]) - STATES[XW] - STATES[XS]; 
// printf("ALGEBRAIC[XU] = (1 - STATES[TmBlocked]) - STATES[XW] - STATES[XS] \n");
// printf("%lf = (1 - %lf) - %lf - %lf \n", ALGEBRAIC[XU], STATES[TmBlocked], STATES[XW], STATES[XS]);
// unattached available xb = all - tm blocked - already prepowerstroke - already post-poststroke - no overlap

ALGEBRAIC[xb_ws] = CONSTANTS[k_ws] * STATES[XW];
ALGEBRAIC[xb_uw] = CONSTANTS[k_uw] * ALGEBRAIC[XU];
// printf("ALGEBRAIC[xb_uw] = CONSTANTS[k_uw] * ALGEBRAIC[XU]; \n");
// printf("%lf = %lf * %lf \n", ALGEBRAIC[xb_uw],  CONSTANTS[k_uw],  ALGEBRAIC[XU]);
ALGEBRAIC[xb_wu] = ALGEBRAIC[k_wu] * STATES[XW];
ALGEBRAIC[xb_su] = ALGEBRAIC[k_su] * STATES[XS];

// element wise multiplication:
double temp_zetas1, temp_zetas2;
temp_zetas1=temp_zetas2=0;
if(STATES[ZETAS] > 0){
    temp_zetas1 = STATES[ZETAS];
}
if (STATES[ZETAS]<-1){
    temp_zetas2 = -1 * STATES[ZETAS] -1; 
}

ALGEBRAIC[gamma_rate] = CONSTANTS[gamma_idx] * fmax( temp_zetas1, temp_zetas2);
ALGEBRAIC[xb_su_gamma] = ALGEBRAIC[gamma_rate] * STATES[XS];

ALGEBRAIC[gamma_rate_w] = CONSTANTS[gamma_wu] * fabs(STATES[ZETAW]); //weak xbs don't like being strained
ALGEBRAIC[xb_wu_gamma] = ALGEBRAIC[gamma_rate_w] * STATES[XW];

        // RATES[XS] 0
        // RATES[XW] 1
        // RATES[TRPN] 2
        // RATES[TmBlocked] 3
        // RATES[ZETAS] 4
        // RATES[ZETAW] 5
        // RATES[dCd_dt] 6

RATES[XS] = ALGEBRAIC[xb_ws] - ALGEBRAIC[xb_su] - ALGEBRAIC[xb_wu_gamma];
RATES[XW] = ALGEBRAIC[xb_uw] - ALGEBRAIC[xb_wu] - ALGEBRAIC[xb_ws] - ALGEBRAIC[xb_wu_gamma];
// printf("RATES[XW] = ALGEBRAIC[xb_uw] - ALGEBRAIC[xb_wu] - ALGEBRAIC[xb_ws] - ALGEBRAIC[xb_wu_gamma]; \n");
// printf("%lf = %lf - %lf - %lf - %lf\n", RATES[XW], ALGEBRAIC[xb_uw], ALGEBRAIC[xb_wu],  ALGEBRAIC[xb_ws], ALGEBRAIC[xb_wu_gamma]);
ALGEBRAIC[ca50] = ALGEBRAIC[ca50] + ALGEBRAIC[beta_1] * fmin(0.2, CONSTANTS[lambda] - 1);
RATES[TRPN] = CONSTANTS[koff] * (pow((CONSTANTS[Cai] / CONSTANTS[ca50]), CONSTANTS[TRPN_n]) * (1 - STATES[TRPN]) - STATES[TRPN]);

ALGEBRAIC[XSSS] = CONSTANTS[dr] * 0.5;
ALGEBRAIC[XWSS] = (1 - CONSTANTS[dr]) * CONSTANTS[wfrac] * 0.5;
ALGEBRAIC[ktm_block]= CONSTANTS[ktm_unblock] * (pow(CONSTANTS[perm50], CONSTANTS[nperm]) * 0.5) / (0.5 - ALGEBRAIC[XSSS] - ALGEBRAIC[XWSS]);

RATES[TmBlocked] = CONSTANTS[ktm_block] * fmin(100, pow(STATES[TRPN], -(CONSTANTS[nperm] / 2))) * ALGEBRAIC[XU] - CONSTANTS[ktm_unblock]  * pow(STATES[TRPN], (CONSTANTS[nperm] / 2)) * STATES[TmBlocked];
//-------------------------------------------------------------------------------
// Velocity dependence -- assumes distortion resets on W->S

RATES[ZETAS] = CONSTANTS[A] * CONSTANTS[dlambda_dt] - CONSTANTS[cds] * STATES[ZETAS];
RATES[ZETAW] = CONSTANTS[A] * CONSTANTS[dlambda_dt] - CONSTANTS[cdw] * STATES[ZETAW];

 //-------------------------------------------------------------------------------
    // Passive model
    //-------------------------------------------------------------------------------

    double Cd = RATES[dCd_dt];
    double C = CONSTANTS[lambda] - 1;
    double eta;

    if ((C - Cd) < 0) {
        eta = CONSTANTS[eta_s];
    } else {
        eta = CONSTANTS[eta_l];
    }

    RATES[dCd_dt] = CONSTANTS[par_k] * (C - Cd) / eta;

    ALGEBRAIC[Fd] = eta * RATES[dCd_dt];
    ALGEBRAIC[F1] = (exp(CONSTANTS[b] * C) - 1);
    ALGEBRAIC[Tp] = CONSTANTS[a] * (ALGEBRAIC[F1] + ALGEBRAIC[Fd]);

    //-------------------------------------------------------------------------------
    // Active and Total Force
    //-------------------------------------------------------------------------------

    ALGEBRAIC[Ta] = ALGEBRAIC[Lfac] * (CONSTANTS[Tref] / CONSTANTS[dr]) * ((STATES[ZETAS] + 1) * STATES[XS] + (STATES[ZETAW])*STATES[XW]);
    // printf("%lf = %lf * (%lf / %lf) * ((%lf +1 ) * %lf + (%lf) * %lf)\n", ALGEBRAIC[Ta], ALGEBRAIC[Lfac], CONSTANTS[Tref], CONSTANTS[dr], STATES[ZETAS], STATES[XS], STATES[ZETAW], STATES[XW]);
    ALGEBRAIC[T] = ALGEBRAIC[Ta] + ALGEBRAIC[Tp];
    printf("%lf,%lf\n",TIME,ALGEBRAIC[T]);

}

void Land_2016::solveEuler(double dt, double t, double Cai_input)
{

    CONSTANTS[Cai] = Cai_input;
    printf("%f\n", CONSTANTS[Cai]);
    STATES[XS] = STATES[XS] + RATES[XS] * dt;
    STATES[XW] = STATES[XW] + RATES[XW] * dt;
    STATES[TRPN] = STATES[TRPN] + RATES[TRPN] * dt;
    STATES[TmBlocked] = STATES[TmBlocked] + RATES[TmBlocked] * dt;
    STATES[ZETAS] = STATES[ZETAS] + RATES[ZETAS] * dt;
    STATES[ZETAW] = STATES[ZETAW] + RATES[ZETAW] * dt;
    STATES[dCd_dt] = STATES[dCd_dt] + RATES[dCd_dt] * dt;
    printf("Lfac: %f Ta: %f Tp: %f\n",  ALGEBRAIC[Lfac], ALGEBRAIC[Ta] , ALGEBRAIC[Tp]);
    // karena Lfac 0, jadi Ta nya 0
    // printf("rates: %f %f %f\n",  RATES[XS] , RATES[XW], RATES[TRPN] );
}

// double set_time_step(double TIME, double time_point, double max_time_step, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC, int offset)
// {

// }