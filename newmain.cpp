#include "cellmodels/Ohara_Rudy_2011.hpp"
#include "cellmodels/Land_2016.hpp"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <iostream>

#include <vector>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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

typedef struct row_data { double data[14]; } row_data;
typedef std::vector< row_data > drug_t;

int get_drug_data_from_file(const char *file_name, drug_t &vec)
{
  FILE *fp_drugs;
  char *token, buffer[255];
  row_data temp_array;
  short idx;
  int sample_size=0;

  if( (fp_drugs = fopen(file_name, "r")) == NULL){
    printf("Cannot open file %s\n", file_name);
    return 1;
  }

  fgets(buffer, sizeof(buffer), fp_drugs); // skip header
  while( fgets(buffer, sizeof(buffer), fp_drugs) != NULL )
  { // begin line reading
    token = strtok( buffer, "," );
    idx = 0;
    while( token != NULL )
    { // begin data tokenizing
      temp_array.data[idx++] = strtod(token, NULL);
      token = strtok(NULL, ",");
    } // end data tokenizing
    vec.push_back(temp_array);
    sample_size++;
  } // end line reading

  return sample_size;
}

int main(int argc, char **argv)
{
  // CVode variables
  double tnext, tcurr;
  int cvode_retval;
  unsigned int icount, imax;

  // drug initialisation
  drug_t IC50;
  double conc = 38.0*0;
  double bcl = 500.;

  // cell object pointer
  Cellmodel* chem_cell; 
  Cellmodel* contr_cell;

  // input variables for cell simulation
  double dt;
  unsigned int pace_max;
  
  // qnet/inet values
  double inet, qnet;

  // variables for I/O
  char buffer[255];
  char number[10];
  char vmcheck[100], icurr[100], concent[100], timestep[100];
  
  FILE* fp_vm;
  FILE* fp_icurr;
  FILE* fp_conc;
  // FILE* fp_output;
  // FILE* fp_inet;
  // FILE* fp_qnet;
  FILE* fp_timestep;
  // FILE* fp_ikr_gates;
 
  // int idx=0;
  // double temp_Cai_input[2000],Cai_input[1000];
  
//   int length = get_cai_data_from_file("./bin/cai_input.csv", temp_Cai_input);
//   for(int a = 1; a<2000; a = a+2){
//     Cai_input[idx] = temp_Cai_input[a];
//     idx++;
// }
//   int cai_index;

  // printf("Using ORd x Land cell model\n");
  int sample_size;
  char drugname[100] = "chlorpromazine";
  char ic50_address[100] = "./drugs/";
  char result_address[100]= "./result/";

  strcat(ic50_address,drugname);
  strcat(ic50_address, ".csv");
  strcat(result_address,drugname);
  sample_size = get_drug_data_from_file(ic50_address,IC50);
  double y[7] = {0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0};
  int sample_idx;

  struct stat st = {0};
  if (stat(result_address, &st) == -1) {
    mkdir(result_address, 0700);
  }

  strcat(result_address,"/");
  sprintf(number, "%.2f", conc);
  strcat(result_address,number);

  struct stat st_2 = {0};
  if (stat(result_address, &st_2) == -1) {
    mkdir(result_address, 0700);
  }

  strcat(result_address,"/");


  
  // dt = 1.;
  tnext = tcurr+dt;
  // printf("%lf,%lf\n", tcurr,contr_cell->RATES[TRPN]);
  
  double tmax;
  // double tmax = 281.;
  double max_time_step = 1.0;
  double time_point = 25.0;
  double dt_set;
  int printer,pacer,pace_count;

  //sample loop
  tic();
  for (sample_idx = 0; sample_idx<sample_size; sample_idx++ ){
      // char filename[100]= "./bepridil/";
      
      char filename[100];
      strcpy(filename,result_address);

      sprintf(number, "%d", sample_idx);
      strcat(filename,number);
      strcpy(vmcheck,filename);strcpy(icurr,filename); strcpy(concent, filename); strcpy(timestep,filename);
      strcat(vmcheck, "vmcheck.csv");strcat(icurr, "icurr.csv");strcat(concent, "conc.csv");strcat(timestep, "timestep.csv");
      contr_cell = new Land_2016();
      chem_cell = new Ohara_Rudy_2011();
      // printf("Initialising\n");
      chem_cell->initConsts(0., bcl, conc, IC50[sample_idx].data, true);
      contr_cell->initConsts(false, false, y);
     
      snprintf(buffer, sizeof(buffer), vmcheck);
      fp_vm = fopen(buffer, "w");

      snprintf(buffer, sizeof(buffer), icurr);
      fp_icurr = fopen(buffer, "w");

      snprintf(buffer, sizeof(buffer), concent);
      fp_conc = fopen(buffer, "w");

      snprintf(buffer, sizeof(buffer), timestep);
      fp_timestep = fopen(buffer, "w");

      pace_max = 1000;
     
      tcurr = 0.0;
      dt = 0.001;
      tmax = pace_max*bcl; // TODO: Use this to display current pace
      printer=0;
      pacer=0; 
      pace_count=0;
      
      fprintf(fp_vm,"Time,v\n");
      fprintf(fp_conc, "Time,nai,cai\n");
      fprintf(fp_timestep, "Time,dt\n");
      fprintf(fp_icurr, "Time,INa,IKr,IKs,IK1,Ito,ICaL\n");
      while (tcurr<tmax) //pacing loop
      {
        // cai_index = tcurr;
          // compute ODE at tcurr
        chem_cell->computeRates(tcurr,
                    chem_cell->CONSTANTS,
                    chem_cell->RATES,
                    chem_cell->STATES,
                    chem_cell->ALGEBRAIC,
                    contr_cell->RATES[TRPN]
                    );

        contr_cell->computeRates(tcurr,
                    contr_cell->CONSTANTS,
                    contr_cell->RATES,
                    contr_cell->STATES,
                    contr_cell->ALGEBRAIC,
                    y);

        // dt_set = Ohara_Rudy_2011::set_time_step(tcurr,
        //            time_point,
        //            max_time_step,
        //            chem_cell->CONSTANTS,
        //            chem_cell->RATES,
        //            chem_cell->STATES,
        //            chem_cell->ALGEBRAIC);
        // // dt_set = dt;

        // // compute accepted timestep
        // if (floor((tcurr + dt_set) / bcl) == floor(tcurr / bcl)) {
        //   dt = dt_set;
        // }
        // else {
        //   dt = (floor(tcurr / bcl) + 1) * bcl - tcurr;
        //   inet = 0.;
        //   if(floor(tcurr)==floor(bcl*pace_max)) //printf("Qnet final value: %lf\n", qnet/1000.0);
        //   qnet = 0.;
        // }

        // if(tcurr==0.0){
          // chem_cell->solveAnalytical(dt);
          // contr_cell->solveEuler(dt, tcurr,Cai_input[cai_index]);
        // }
        // else{
          chem_cell->solveAnalytical(dt);
          contr_cell->solveEuler(dt, tcurr, (chem_cell->STATES[cai]*1000.));
        // }
        pacer++;
        if (pacer==bcl/dt){
          printf("Pace %d done\n",pace_count+1);
          pace_count++;
          pacer=0;
        }
        // fprintf(fp_vm, "%lf,%lf,%lf,%lf,%lf\n", tcurr, chem_cell->STATES[v], chem_cell->STATES[cai], contr_cell->ALGEBRAIC[land_T], contr_cell->ALGEBRAIC[land_T]*480*0.5652016963361872);
        // printf("%lf,%lf,%lf\n", tcurr,chem_cell->STATES[cai]*1000,Cai_input[cai_index]);
        if(tcurr >= tmax-bcl){
        printer++;
          if(printer == 333){
              fprintf(fp_vm, "%lf,%lf\n", tcurr, chem_cell->STATES[v]);
              fprintf(fp_conc,"%lf,%lf,%lf\n", tcurr,chem_cell->STATES[nai], chem_cell->STATES[cai] );
              fprintf(fp_timestep, "%lf,%lf\n", tcurr,dt);
              fprintf(fp_icurr,"%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",tcurr,chem_cell->ALGEBRAIC[INa],chem_cell->ALGEBRAIC[IKr], chem_cell->ALGEBRAIC[IKs], chem_cell->ALGEBRAIC[IKs], chem_cell->ALGEBRAIC[IK1], chem_cell->ALGEBRAIC[Ito], chem_cell->ALGEBRAIC[ICaL]);
              printer=0;
        }
        
        }
        tcurr += dt;
      }

  fclose(fp_vm);
  fclose(fp_icurr);
  fclose(fp_conc);
  fclose(fp_timestep);
} //sample loop

toc();

// delete contr_cell;
// delete chem_cell;
}