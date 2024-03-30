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
    if (BETA == true){
        // // input an array of beta, 
        // CONSTANTS[beta_1] = beta[1];
        // CONSTANTS[beta_0] = beta[0];
    }
    
    // k_ws = 0.004 * mu;
    // k_uw = 0.026  * nu;
    CONSTANTS[k_ws] = 0.004 * CONSTANTS[mu];
    CONSTANTS[k_uw] = 0.026 * CONSTANTS[nu];

    //STATES Variables
    if(y[0]>0) STATES[XS] = fmax(0,y[0]);
    if(y[1]>0) STATES[XW] = fmax(0,y[1]);
    if(y[2]>0) STATES[TRPN] = fmax(0,y[2]);
    STATES[TmBlocked] = y[3];
    STATES[ZETAS] = y[4];
    STATES[ZETAW] = y[5];
    STATES[dCd_dt] = y[6];
    // printf("initialisation\n");


    // seventh state is below, in passive model (dCd_dt)

    CONSTANTS[par_k] = 7;
    CONSTANTS[b] = 9.1;
    CONSTANTS[eta_l] = 200;
    CONSTANTS[eta_s] = 20;
    CONSTANTS[a] = 2.1;

}

void Land_2016::computeRates(double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC, double *y)
{
// XB model

// lambda = min(1.2,lambda);
// Lfac =  max(0, 1 + beta_0 * (lambda + min(0.87,lambda) - 1.87) );

CONSTANTS[lambda] = fmin(1.2, CONSTANTS[lambda]);
ALGEBRAIC[Lfac]  = fmax(0, 1 + CONSTANTS[beta_0] * (CONSTANTS[lambda] + fmin(0.87, CONSTANTS[lambda]) - 1.87));

if (ALGEBRAIC[Lfac] < 0){
    ALGEBRAIC[Lfac] = 0 ;
}
// cdw = phi * k_uw * (1-dr)*(1-wfrac) /  ((1-dr)*wfrac);
// cds = phi * k_ws * (1-dr)*wfrac / dr;
ALGEBRAIC[cdw] = CONSTANTS[phi] * CONSTANTS[k_uw] * (1-CONSTANTS[dr])*(1-CONSTANTS[wfrac]) /  ((1-CONSTANTS[dr])*CONSTANTS[wfrac]);
ALGEBRAIC[cds] = CONSTANTS[phi] * CONSTANTS[k_ws] * (1-CONSTANTS[dr])*CONSTANTS[wfrac] / CONSTANTS[dr];

// k_wu = k_uw * (1/wfrac - 1) - k_ws;
// k_su = k_ws * (1/dr - 1) * wfrac; 
// A = (0.25 * TOT_A) / ((1-dr)*wfrac + dr) * (dr/0.25);
ALGEBRAIC[k_wu] = CONSTANTS[k_uw] * (1/CONSTANTS[wfrac] - 1) - CONSTANTS[k_ws];
ALGEBRAIC[k_su] = CONSTANTS[k_ws] * (1/CONSTANTS[dr] - 1) * CONSTANTS[wfrac]; 
ALGEBRAIC[A] = (0.25 * CONSTANTS[TOT_A]) / ((1-CONSTANTS[dr])*CONSTANTS[wfrac] + CONSTANTS[dr]) * (CONSTANTS[dr]/0.25);

// XU   = (1 - TmBlocked) - XW - XS;
ALGEBRAIC[XU] = (1 - STATES[TmBlocked]) - STATES[XW] - STATES[XS]; 
// unattached available xb = all - tm blocked - already prepowerstroke - already post-poststroke - no overlap

// xb_ws = k_ws * XW;
// xb_uw = k_uw * XU ;
// xb_wu = k_wu * XW;
// xb_su = k_su * XS;
ALGEBRAIC[xb_ws] = CONSTANTS[k_ws] * STATES[XW];
ALGEBRAIC[xb_uw] = CONSTANTS[k_uw] * ALGEBRAIC[XU];
ALGEBRAIC[xb_wu] = ALGEBRAIC[k_wu] * STATES[XW];
ALGEBRAIC[xb_su] = ALGEBRAIC[k_su] * STATES[XS];

//gamma_rate  = gamma * max( (ZETAS > 0) .* ZETAS , (ZETAS < -1) .* (-ZETAS-1) );
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

// xb_su_gamma = gamma_rate * XS;
ALGEBRAIC[xb_su_gamma] = ALGEBRAIC[gamma_rate] * STATES[XS];

// gamma_rate_w  = gamma_wu * abs(ZETAW);
ALGEBRAIC[gamma_rate_w] = CONSTANTS[gamma_wu] * fabs(STATES[ZETAW]); //weak xbs don't like being strained
// xb_wu_gamma = gamma_rate_w * XW; 
ALGEBRAIC[xb_wu_gamma] = ALGEBRAIC[gamma_rate_w] * STATES[XW];

// dydt(1)  = xb_ws - xb_su - xb_su_gamma;
// dydt(2)  = xb_uw - xb_wu - xb_ws - xb_wu_gamma;
RATES[XS] = ALGEBRAIC[xb_ws] - ALGEBRAIC[xb_su] - ALGEBRAIC[xb_wu_gamma];
RATES[XW] = ALGEBRAIC[xb_uw] - ALGEBRAIC[xb_wu] - ALGEBRAIC[xb_ws] - ALGEBRAIC[xb_wu_gamma];

// ca50 = ca50 + beta_1*min(0.2,lambda - 1);
// dydt(3)  = koff * ( (Cai/ca50)^TRPN_n * (1-TRPN) - TRPN);
ALGEBRAIC[ca50] = ALGEBRAIC[ca50] + ALGEBRAIC[beta_1] * fmin(0.2, CONSTANTS[lambda] - 1);
RATES[TRPN] = CONSTANTS[koff] * (pow((CONSTANTS[Cai] / ALGEBRAIC[ca50]), CONSTANTS[TRPN_n]) * (1 - STATES[TRPN]) - STATES[TRPN]);

// XSSS = dr * 0.5;
// XWSS = (1-dr) * wfrac * 0.5;
// ktm_block = ktm_unblock * (perm50^nperm) *  0.5 / (0.5 - XSSS - XWSS);
ALGEBRAIC[XSSS] = CONSTANTS[dr] * 0.5;
ALGEBRAIC[XWSS] = (1 - CONSTANTS[dr]) * CONSTANTS[wfrac] * 0.5;
ALGEBRAIC[ktm_block]= CONSTANTS[ktm_unblock] * (pow(CONSTANTS[perm50], CONSTANTS[nperm]) * 0.5) / (0.5 - ALGEBRAIC[XSSS] - ALGEBRAIC[XWSS]);

// dydt(4)  = ktm_block * min(100, (TRPN^-(nperm/2))) * XU  - ktm_unblock * (TRPN^(nperm/2)) *  TmBlocked;
RATES[TmBlocked] = CONSTANTS[ktm_block] * fmin(100, pow(STATES[TRPN], -(CONSTANTS[nperm] / 2))) * ALGEBRAIC[XU] - CONSTANTS[ktm_unblock]  * pow(STATES[TRPN], (CONSTANTS[nperm] / 2)) * STATES[TmBlocked];
//-------------------------------------------------------------------------------
// Velocity dependence -- assumes distortion resets on W->S
// dydt(5) = A * dlambda_dt - cds * ZETAS;% - gamma_rate * ZETAS;
// dydt(6) = A * dlambda_dt - cdw * ZETAW;% - gamma_rate_w * ZETAW;
RATES[ZETAS] = CONSTANTS[A] * CONSTANTS[dlambda_dt] - ALGEBRAIC[cds] * STATES[ZETAS];
RATES[ZETAW] = CONSTANTS[A] * CONSTANTS[dlambda_dt] - ALGEBRAIC[cdw] * STATES[ZETAW];

//-------------------------------------------------------------------------------
// Passive model
// this is quite scary, did not fix the problem but Cd actually y[6] aka y(7)
//-------------------------------------------------------------------------------

// Cd = y(7);
// C = lambda - 1;

// CONSTANTS[Cd] = STATES[dCd_dt]; 
CONSTANTS[Cd] = y[6];
CONSTANTS[C] = CONSTANTS[lambda] - 1;

// if (C - Cd) < 0
//  eta = eta_s;
// else
//  eta = eta_l;
// end
if ((CONSTANTS[C] - CONSTANTS[Cd]) < 0) {
        CONSTANTS[eta] = CONSTANTS[eta_s];
    } else {
        CONSTANTS[eta] = CONSTANTS[eta_l];
    }

// dCd_dt = par_k * (C - Cd) / eta; % F2=Fd
STATES[dCd_dt] = CONSTANTS[par_k] * (CONSTANTS[C] - CONSTANTS[Cd]) / CONSTANTS[eta];
// dydt(7) = dCd_dt;
RATES[dCd_dt] = STATES[dCd_dt];

// Fd = eta * dCd_dt;
ALGEBRAIC[Fd] = eta * STATES[dCd_dt];
// F1 = (exp( b * C) - 1);
ALGEBRAIC[F1] = (exp(CONSTANTS[b] * CONSTANTS[C]) - 1);
// Tp = a * (F1 + Fd);
ALGEBRAIC[Tp] = CONSTANTS[a] * (ALGEBRAIC[F1] + ALGEBRAIC[Fd]);

//-------------------------------------------------------------------------------
// Active and Total Force
//-------------------------------------------------------------------------------

// Ta = Lfac * (Tref/dr) * ( (ZETAS+1) * XS + (ZETAW) * XW );
// T = Ta + Tp;
ALGEBRAIC[Ta] = ALGEBRAIC[Lfac] * (CONSTANTS[Tref] / CONSTANTS[dr]) * ((STATES[ZETAS] + 1) * STATES[XS] + (STATES[ZETAW])*STATES[XW]);
ALGEBRAIC[T] = ALGEBRAIC[Ta] + ALGEBRAIC[Tp];

}

void Land_2016::solveEuler(double dt, double t, double Cai_input)
{

    CONSTANTS[Cai] = Cai_input;
    printf("%lf,%lf\n", t,ALGEBRAIC[T]);
    STATES[XS] = STATES[XS] + RATES[XS] * dt;
    STATES[XW] = STATES[XW] + RATES[XW] * dt;
    STATES[TRPN] = STATES[TRPN] + RATES[TRPN] * dt;
    STATES[TmBlocked] = STATES[TmBlocked] + RATES[TmBlocked] * dt;
    STATES[ZETAS] = STATES[ZETAS] + RATES[ZETAS] * dt;
    STATES[ZETAW] = STATES[ZETAW] + RATES[ZETAW] * dt;
    STATES[dCd_dt] = STATES[dCd_dt] + RATES[dCd_dt] * dt;
    // printf("Lfac: %f Ta: %f Tp: %f\n",  ALGEBRAIC[Lfac], ALGEBRAIC[Ta] , ALGEBRAIC[Tp]);
    // karena Lfac 0, jadi Ta nya 0
    // printf("rates: %f %f %f\n",  RATES[XS] , RATES[XW], RATES[TRPN] );
}

// double set_time_step(double TIME, double time_point, double max_time_step, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC, int offset)
// {

// }