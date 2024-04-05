#include "cellmodels/Ohara_Rudy_2011.hpp"
#include "cellmodels/Land_2016.hpp"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <iostream>

#include <vector>
#include <string.h>

clock_t START_TIMER;

clock_t tic()
{
  return START_TIMER = clock();
}

void toc(clock_t start = START_TIMER)
{
  std::cout
      // << "Elapsed time: "
      // << (clock() - start) / (double)CLOCKS_PER_SEC << "s"
      << std::endl;
}

// int get_cai_data_from_file(const char* file_name, double *cai)
// {
//   //put them in as array of double
//   FILE *fp_cai;
  
//   char *token, buffer[255];
//   unsigned short idx;

//   if( (fp_cai = fopen(file_name, "r")) == NULL){
//     printf("Cannot open file %s\n",
//       file_name);
//     return 0;
//   }

//   idx = 0;
//   int sample_size = 0;

//   fgets(buffer, sizeof(buffer), fp_cai); // skip header
//   while( fgets(buffer, sizeof(buffer), fp_cai) != NULL )
//   { // begin line reading
//     token = strtok( buffer, "," );
//     while( token != NULL )
//     { // begin data tokenizing
//       cai[idx++] = strtod(token, NULL);
//       token = strtok(NULL, ",");
//     } // end data tokenizing
//      sample_size++;
//   } // end line reading

//   fclose(fp_cai);
//   return sample_size;
// }

int main(int argc, char **argv)
{
  // CVode variables
  double tnext, tcurr;
  int cvode_retval;
  unsigned int icount, imax;

  void* cvode_mem;

  // cell object pointer
  Cellmodel* chem_cell; 
  Cellmodel* contr_cell;

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

  printf("Using ORd x Land cell model\n");
  double y[7] = {0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0};
  contr_cell = new Land_2016();
  chem_cell = new Ohara_Rudy_2011();
  printf("Initialising\n");
  chem_cell->initConsts();
  contr_cell->initConsts(false, false, y);

  pace_max = 1;
  bcl = 1000.;
  tcurr = 0.0;
  dt = 0.001;
  // dt = 1.;
  tnext = tcurr+dt;
  
  tic();
  printf("Analytical method\n");
  double tmax = pace_max*bcl;
  // double tmax = 281.;
  double max_time_step = 1.0;
  double time_point = 25.0;
  double dt_set;

  while (tcurr<tmax){
    contr_cell->computeRates(tcurr,
		             contr_cell->CONSTANTS,
            		 contr_cell->RATES,
		             contr_cell->STATES,
            		 contr_cell->ALGEBRAIC,
                 y);

    dt_set = Ohara_Rudy_2011::set_time_step(tcurr,
               time_point,
               max_time_step,
               chem_cell->CONSTANTS,
               chem_cell->RATES,
               chem_cell->STATES,
               chem_cell->ALGEBRAIC);

    // compute accepted timestep
    if (floor((tcurr + dt_set) / bcl) == floor(tcurr / bcl)) {
      dt = dt_set;
    }
    else {
      dt = (floor(tcurr / bcl) + 1) * bcl - tcurr;
      inet = 0.;
      if(floor(tcurr)==floor(bcl*pace_max)) //printf("Qnet final value: %lf\n", qnet/1000.0);
      qnet = 0.;
    }

    contr_cell->solveEuler(dt, tcurr, chem_cell->STATES[cai]);
    chem_cell->solveAnalytical(dt, contr_cell->CONSTANTS[cai]);

    printf("%lf,%lf\n", tcurr,chem_cell->ALGEBRAIC[land_T]);

tcurr += dt;
}


toc();
}
