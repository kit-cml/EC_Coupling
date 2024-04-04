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


}