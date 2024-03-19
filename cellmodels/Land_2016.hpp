#ifndef LAND_2016_HPP
#define LAND_2016_HPP

#include "cellmodel.hpp"
#include "../enums/enum_Land_2016.hpp"

class Land_2016 : public Cellmodel
{
public:
  Land_2016();
  ~Land_2016();
  	void initConsts();
    void computeRates();
	// void initConsts(double type);
	// void initConsts(bool is_dutta);
	// void initConsts(double type, double conc, double *ic50, bool is_dutta );
    void initConsts( bool is_skinned, bool BETA, double* y);
	void computeRates(double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC);
	void solveEuler( double dt, double t, double *Cai_input );
	//static double set_time_step(double TIME,double time_point,double max_time_step,
//   double* CONSTANTS,
//   double* RATES,
//   double* STATES,
//   double* ALGEBRAIC);
// private:
	// void ___applyDrugEffect(double conc, double *ic50, double epsilon);
	// void ___applyDutta();
	// void ___initConsts(double type);

};


#endif