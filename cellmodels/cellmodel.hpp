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
	double* ALGEBRAIC;
	double* CONSTANTS;
	double* RATES;
	double* STATES;
	virtual ~Cellmodel() {};
	virtual void initConsts() = 0;
	virtual void computeRates(double TIME, double* CONSTANTS, double* RATES, double* STATES, double* ALGEBRAIC) = 0;
	virtual void solveAnalytical(double dt) {};
	virtual void solveRK4(double tcurr, double dt) {};

};

#endif
