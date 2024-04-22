#ifndef CELL_HPP
#define CELL_HPP

class Cellmodel
{

protected:
	Cellmodel(){}
public:
	 unsigned short algebraic_size;
  unsigned short constants_size;
  unsigned short states_size;
  unsigned short gates_size;
  unsigned short current_size;
  unsigned short concs_size;
  double ALGEBRAIC[255];
  double CONSTANTS[255];
  double RATES[255];
  double STATES[255];
  char gates_header[255];
  unsigned short gates_indices[255];
  char current_header[255];
  unsigned short current_indices[255];
  char concs_header[255];
  unsigned short concs_indices[255];
  virtual ~Cellmodel() {}

  virtual void initConsts() = 0;
  virtual void initConsts(double type){}
  virtual void initConsts(double type, double conc, double *hill){}
  virtual void initConsts(double type, double conc, double *hill, bool is_dutta){}
  virtual void initConsts(double type, double bcl, double conc, double *hill, bool is_dutta){}
  virtual void initConsts(double type, double conc, double *hill, double* boot){}
  virtual void initConsts( bool is_skinned, bool BETA, double* y){}
  
  virtual void computeRates() = 0;
  virtual void computeRates(double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC){}
  virtual void computeRates(double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC, double land_trpn){}
  virtual void computeRates(double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC, double *y){}

  // virtual void solveAnalytical() = 0;
  virtual void solveAnalytical(double dt) {}
  virtual void solveAnalytical(double dt, double Ca_TRPN) {}

  virtual void solveEuler( double dt, double t, double Cai_input ){}
  virtual void solveRK4(double TIME,double dt) {}
};

#endif
