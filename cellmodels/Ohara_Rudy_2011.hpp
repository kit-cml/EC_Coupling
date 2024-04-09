#ifndef OHARA_RUDY_2011_HPP
#define OHARA_RUDY_2011_HPP

#include "cellmodel.hpp"
#include "../enums/enum_Ohara_Rudy_2011.hpp"

class Ohara_Rudy_2011 : public Cellmodel
{
public:
  Ohara_Rudy_2011();
  ~Ohara_Rudy_2011();
  void initConsts ();
  void computeRates();
  void computeRates( double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC );
  // void solveAnalytical();
  void solveAnalytical( double dt);
  void solveAnalytical( double dt, double Ca_TRPN );
  static double set_time_step(double TIME,double time_point,double max_time_step,
      double* CONSTANTS,double* RATES,double* STATES,double* ALGEBRAIC);

};


#endif

