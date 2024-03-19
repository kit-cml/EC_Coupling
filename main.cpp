#ifdef TOMEK_2019
#include "cellmodels/Tomek_model.hpp"
#else
#include "cellmodels/Ohara_Rudy_2011.hpp"
#endif
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <iostream>

clock_t START_TIMER;

clock_t tic()
{
  return START_TIMER = clock();
}

void toc(clock_t start = START_TIMER)
{
  std::cout
      << "Elapsed time: "
      << (clock() - start) / (double)CLOCKS_PER_SEC << "s"
      << std::endl;
}


int main(int argc, char **argv)
{
  // CVode variables
  double tnext, tcurr;
  int cvode_retval;
  unsigned int icount, imax;

  void* cvode_mem;

  // cell object pointer
  Cellmodel* p_cell;

  // input variables for cell simulation
  double bcl, dt;
  unsigned int pace_max;
  unsigned int pace_count;
  
  // qnet/inet values
  double inet, qnet;

  // variables for I/O
  char buffer[255];
  FILE* fp_vm;
  FILE* fp_icurr;
  FILE* fp_conc;
  FILE* fp_output;
  FILE* fp_inet;
  FILE* fp_qnet;
	FILE* fp_timestep;
	FILE* fp_ikr_gates;


	int idx;

#ifdef TOMEK_2019
  printf("Using Tomek cell model\n");
  p_cell = new Tomek_model();
#else
  printf("Using O'Hara Rudy cell model\n");
  p_cell = new Ohara_Rudy_2011();
#endif
  p_cell->initConsts();

// apply Dutta scaling
#ifndef TOMEK_2019 
  p_cell->CONSTANTS[GKs] *= 1.870;
  p_cell->CONSTANTS[GKr] *= 1.013;
  p_cell->CONSTANTS[GK1] *= 1.698;
  p_cell->CONSTANTS[PCa] *= 1.007;
  p_cell->CONSTANTS[GNaL] *= 2.661;
#endif

  pace_max = 1000;
  bcl = 2000.;
  tcurr = 0.0;
  dt = 0.001;
  tnext = tcurr+dt;

  p_cell->CONSTANTS[BCL] = bcl;
  double dtw = 2.0;
  const unsigned int print_freq = (1./dt) * dtw;


#ifdef TOMEK_2019
  CVodeSetMaxStep(cvode_mem, p_cell->CONSTANTS[i_Stim_PulseDuration]);
#else
  // CVodeSetMaxStep(cvode_mem, p_cell->CONSTANTS[duration]);
#endif
  // CVodeSetLinearSolver(cvode_mem, solver, matrix);

  snprintf(buffer, sizeof(buffer), "vmcheck.plt");
  fp_vm = fopen(buffer, "w");
  snprintf(buffer, sizeof(buffer), "icurr.plt");
  fp_icurr = fopen(buffer, "w");
  snprintf(buffer, sizeof(buffer), "concs.plt");
  fp_conc = fopen(buffer, "w");
  snprintf(buffer, sizeof(buffer), "inet.plt");
  fp_inet = fopen(buffer, "w");
  snprintf(buffer, sizeof(buffer), "qnet.plt");
  fp_qnet = fopen(buffer, "w");
  snprintf(buffer, sizeof(buffer), "timestep.plt");
  fp_timestep = fopen(buffer, "w");
  snprintf(buffer, sizeof(buffer), "ikr_gates.plt");
  fp_ikr_gates = fopen(buffer, "w");

#ifdef TOMEK_2019
  snprintf(buffer, sizeof(buffer), "output_tomek.dat");
#else
  snprintf(buffer, sizeof(buffer), "output_orudy.dat");
#endif
  fp_output = fopen(buffer, "w");


  fprintf(fp_vm, "Time,v\n");
  fprintf(fp_icurr, "Time,INa,IKr,IKs,IK1,Ito,ICaL\n");
  fprintf(fp_conc, "Time,nai,cai\n");
  fprintf(fp_inet, "Time,Inet\n");
  fprintf(fp_qnet, "Time,Qnet\n");
  fprintf(fp_timestep, "Time,dt\n");
  fprintf(fp_ikr_gates, "Time,O,I,C1,C2,C3\n");

  pace_count = 0;
  inet = 0.;
  qnet = 0.;

#ifdef ANALYTICAL
  tic();
  printf("Analytical method\n");
  //double tmax = pace_max*bcl;
  double tmax = 281.;
  double max_time_step = 1.0;
  double time_point = 25.0;
  double dt_set;
  while(tcurr < tmax)
  {
    // compute ODE at tcurr

    p_cell->computeRates(tcurr,
		         p_cell->CONSTANTS,
            		 p_cell->RATES,
		         p_cell->STATES,
            		 p_cell->ALGEBRAIC);

#ifdef TOMEK_2019
		dt_set = Tomek_model::set_time_step(tcurr,
               time_point,
               max_time_step,
                 p_cell->CONSTANTS,
               p_cell->RATES,
         p_cell->STATES,
               p_cell->ALGEBRAIC);
#else
    dt_set = Ohara_Rudy_2011::set_time_step(tcurr,
        		   time_point,
		           max_time_step,
  		           p_cell->CONSTANTS,
		           p_cell->RATES,
			   p_cell->STATES,
		           p_cell->ALGEBRAIC);
#endif
    // compute accepted timestep
    if (floor((tcurr + dt_set) / bcl) == floor(tcurr / bcl)) {
      dt = dt_set;
    }
    else {
      dt = (floor(tcurr / bcl) + 1) * bcl - tcurr;
      inet = 0.;
      if(floor(tcurr)==floor(bcl*pace_max)) printf("Qnet final value: %lf\n", qnet/1000.0);
      qnet = 0.;
    }

    //Compute the analytical solution
    p_cell->solveAnalytical(dt);
    //p_cell->solveRK4(tcurr, dt);
    if(p_cell->STATES[v] > -88.0){
      inet = (p_cell->ALGEBRAIC[INaL]+p_cell->ALGEBRAIC[ICaL]+p_cell->ALGEBRAIC[Ito]+p_cell->ALGEBRAIC[IKr]+p_cell->ALGEBRAIC[IKs]+p_cell->ALGEBRAIC[IK1]);
      qnet += inet * dt;
    }
#ifdef DEBUG
		//if(tcurr <= 300.0) printf("%lf,%lf,%lf\n", tcurr,dt, p_cell->STATES[v]);
#endif
    //if( tcurr > (bcl*(pace_max-1))  ){
      fprintf(fp_inet, "%lf,%lf\n", tcurr, inet);
      fprintf(fp_qnet, "%lf,%lf\n", tcurr, qnet/1000.);
      fprintf(fp_vm, "%lf,%lf,%lf\n", tcurr, p_cell->STATES[v], p_cell->RATES[v]);
      fprintf(fp_icurr, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n", tcurr,
                        p_cell->ALGEBRAIC[INa], p_cell->ALGEBRAIC[IKr], p_cell->ALGEBRAIC[IKs],
                        p_cell->ALGEBRAIC[IK1], p_cell->ALGEBRAIC[Ito], p_cell->ALGEBRAIC[ICaL]);
      fprintf(fp_conc, "%lf,%lf,%lf\n", tcurr, p_cell->STATES[nai], p_cell->STATES[cai]);
			fprintf(fp_timestep, "%lf,%lf\n", tcurr,dt);
			// fprintf(fp_ikr_gates, "%lf,%lf,%lf,%lf,%lf,%lf\n", 
			// 											tcurr,p_cell->STATES[O],p_cell->STATES[I],p_cell->STATES[C1],p_cell->STATES[C2],p_cell->STATES[C3]);
    //}
    tcurr += dt;
  }
  toc();
#else
  tic();
  printf("CVode method\n");
  icount = 0;
  imax = (pace_max*bcl)/dt;
  while (icount < imax)
  {
    if(p_cell->STATES[v] > -88.0){
      inet = (p_cell->ALGEBRAIC[INaL]+p_cell->ALGEBRAIC[ICaL]+p_cell->ALGEBRAIC[Ito]+p_cell->ALGEBRAIC[IKr]+p_cell->ALGEBRAIC[IKs]+p_cell->ALGEBRAIC[IK1]);
      qnet += inet * dt;
    }
    if(icount == (unsigned int)(bcl*pace_count/dt)){
      pace_count++;
      inet = 0.;
      if(pace_count==pace_max) printf("Qnet final value: %lf\n", qnet/1000.0);
      qnet = 0.;
    }
#ifdef DEBUG
    printf("%lf,%lf,%lf\n", tcurr,dt, p_cell->STATES[v]);
#endif
    if (cvode_retval) {
      //CVodeGetLastStep(cvode_mem, &dt);
      if(pace_count > pace_max-1 /*&& icount % print_freq == 0*/){
        fprintf(fp_inet, "%lf,%lf\n", tcurr, inet);
        fprintf(fp_qnet, "%lf,%lf\n", tcurr, qnet/1000.0);
        fprintf(fp_vm, "%lf,%lf\n", tcurr, p_cell->STATES[v]);
        fprintf(fp_icurr, "%lf,%lf,%lf,%lf,%lf,%lf,%lf\n", tcurr, 
                          p_cell->ALGEBRAIC[INa], p_cell->ALGEBRAIC[IKr], p_cell->ALGEBRAIC[IKs],
                          p_cell->ALGEBRAIC[IK1], p_cell->ALGEBRAIC[Ito], p_cell->ALGEBRAIC[ICaL]);
        fprintf(fp_conc, "%lf,%lf,%lf\n", tcurr, p_cell->STATES[nai], p_cell->STATES[cai]);
      }
        icount++;
        tnext += dt;
    }
    else {
      printf( "CVode error at %lf sec\n", tcurr);
      break;
    }
  }
  toc();
#endif

  for(icount = 0; icount < p_cell->states_size; icount++ ) fprintf( fp_output, "%lf\n", p_cell->STATES[icount] );

  printf("Qnet final value: %lf\n", qnet/1000.0);

  fclose(fp_output);
  fclose(fp_vm);
  fclose(fp_icurr);
  fclose(fp_conc);
  fclose(fp_qnet);
  fclose(fp_inet);
	fclose(fp_ikr_gates);
	fclose(fp_timestep);

  delete p_cell;

  return 0;
}
