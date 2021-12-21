// This file was generated by the ExaHyPE toolkit.
// It will NOT be regenerated or overwritten.
// Please adapt it to your own needs.
// 
// ========================
//   www.exahype.eu
// ========================

#include "Forward.h"

#include "Forward_Variables.h"

#include "kernels/KernelUtils.h"
#include "peano/utils/Loop.h"
#include "../elasticutil.h"


tarch::logging::Log earthadj::Forward::_log( "earthadj::Forward" );


void earthadj::Forward::init(const std::vector<std::string>& cmdlineargs,const exahype::parser::ParserView& constants) {
  // Tip: You find documentation for this method in header file "earthadj::Forward.h".
  
  // @todo Please implement/augment if required

  initPointSourceLocations(cmdlineargs,constants);	
    
}

void earthadj::Forward::adjustPointSolution(const double* const x,const double t,const double dt,double* const Q) {
  // Tip: You find documentation for this method in header file "earthadj::Forward.h".
  // Tip: See header file "earthadj::AbstractForward.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.
  
  // @todo Please implement/augment if required
	if (tarch::la::equals(t,0.0)) {
		auto xx=x[0];
		auto yy=x[1];

		Q[sigma11] = 0.0;
		Q[sigma22] = 0.0;
		Q[sigma12] = 0.0;
//    Q[uu] = std::exp(-(xx-5)*(xx-5)-(yy-5)*(yy-5));
//    Q[vv] = std::exp(-(xx-5)*(xx-5)-(yy-5)*(yy-5));;
		Q[uu]=0.0;
		Q[vv]=0.0;
		if(xx<7.5) {
			Q[lamb] = 2.0;
			Q[mu] = 0.5;
		}
		else{
			Q[lamb] = 2.0;
			Q[mu] = 2.0;
		}
		Q[rho] = 1.0;
  }
}

void earthadj::Forward::boundaryValues(const double* const x,const double t,const double dt,const int faceIndex,const int direction,const double* const fluxIn,const double* const stateIn,const double* const gradStateIn,double* const fluxOut,double* const stateOut) {
  // Tip: You find documentation for this method in header file "earthadj::Forward.h".
  // Tip: See header file "earthadj::AbstractForward.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.

  // @todo Please implement/augment if required
	if(faceIndex==3){
		freeSurface(direction,stateIn,stateOut);
	} else{
		specifiedTraction(direction, stateIn, stateOut);
	}
}

exahype::solvers::Solver::RefinementControl earthadj::Forward::refinementCriterion(const double* const luh,const tarch::la::Vector<DIMENSIONS,double>& cellCentre,const tarch::la::Vector<DIMENSIONS,double>& cellSize,double t,const int level) {
  // Tip: You find documentation for this method in header file "earthadj::Forward.h".
  // Tip: See header file "earthadj::AbstractForward.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.
  // Tip: See header file "peano/utils/Loop.h" for dimension-agnostic for loops.
  
  //  Example: Loop over all pointwise state variables (plus parameters)
  //
  //  constexpr int sizeOfQ = NumberOfVariables+NumberOfParameters;
  //  dfor(i,Order+1) {
  //    const int iLinearised = dLinearised(i,Order+1);
  //    const double* const Q = luh + iLinearised * sizeOfQ; // pointwise state variables (plus parameters)
  //    // use Q[0], Q[1], ... Q[sizeOfQ-1]
  //  }
  
  // @todo Please implement/augment if required
  return exahype::solvers::Solver::RefinementControl::Keep;
}

//*****************************************************************************
//******************************** PDE ****************************************
// To use other PDE terms, specify them in the specification file, delete this 
// file and its header and rerun the toolkit
//*****************************************************************************


void earthadj::Forward::eigenvalues(const double* const Q,const int direction,double* const lambda) {
  // Tip: You find documentation for this method in header file "earthadj::Forward.h".
  // Tip: See header file "earthadj::AbstractForward.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.
  
  // @todo Please implement/augment if required
	auto cp=std::sqrt((Q[lamb]+2*Q[mu])/Q[rho]);
	auto cs=std::sqrt(Q[mu]/Q[rho]);


	lambda[0] = -cp;
	lambda[1] = cp;
	lambda[2] = -cs;
	lambda[3] = cs;
	lambda[4] = 0;
}





void earthadj::Forward::flux(const double* const Q,double** const F) {
  // Tip: You find documentation for this method in header file "earthadj::Forward.h".
  // Tip: See header file "earthadj::AbstractForward.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.
  
  // @todo Please implement/augment if required
  F[0][0] = -(Q[lamb]+2*Q[mu])*Q[uu];
  F[0][1] = -Q[lamb]*Q[uu];
  F[0][2] = -Q[mu]*Q[vv];
  F[0][3] = -Q[sigma11]/Q[rho];
  F[0][4] = -Q[sigma12]/Q[rho];
  
  F[1][0] = -Q[lamb]*Q[vv];
  F[1][1] = -(Q[lamb]+2*Q[mu])*Q[vv];
  F[1][2] = -Q[mu]*Q[uu];
  F[1][3] = -Q[sigma12]/Q[rho];
  F[1][4] = -Q[sigma22]/Q[rho];
  
}





void  earthadj::Forward::initPointSourceLocations(const std::vector<std::string>& cmdlineargs,const exahype::parser::ParserView& constants){
  // Tip: You find documentation for this method in header file "earthadj::Forward.h".
  // Tip: See header file "earthadj::AbstractForward.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.
  
  // @todo Please implement/augment if required

  pointSourceLocation[0][0]=5.0;
  pointSourceLocation[0][1]=5.0;
    
}

void  earthadj::Forward::pointSource(const double* const Q,const double* const x,const double t,const double dt, double* const forceVector, int n) {
  // Tip: You find documentation for this method in header file "earthadj::Forward.h".
  // Tip: See header file "earthadj::AbstractForward.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.
  
  // @todo Please implement/augment if required
	double T=0.1;
	double M_0=1e4;
	auto M_xy=(M_0*t/(T*T))*std::exp(-t/T);
	forceVector[sigma12]=M_xy;
	forceVector[sigma11]=0.0;
	forceVector[sigma22]=0.0;
	forceVector[uu]=0.0;
	forceVector[vv]=0.0;
//	std::cerr <<t<<":time \n";
}
