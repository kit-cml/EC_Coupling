#ifndef TOMEK_MODEL_ENDO_HPP
#define TOMEK_MODEL_ENDO_HPP

#include "cellmodel.hpp"
#include "../enums/enum_Tomek_model.hpp"

class Tomek_model : public Cellmodel
{
public:
  Tomek_model();
  ~Tomek_model();
  void initConsts ();
  void initConsts (double celltype);
  void initConsts (double celltype, double conc, double *ic50);
  void computeRates( double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC );
  void solveAnalytical( double dt );
	void solveRK4( double tcurr, double dt );
  static double set_time_step(double TIME,double time_point,double max_time_step,
      double* CONSTANTS,double* RATES,double* STATES,double* ALGEBRAIC);
};



#endif

