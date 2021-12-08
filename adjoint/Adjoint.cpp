// This file was generated by the ExaHyPE toolkit.
// It will NOT be regenerated or overwritten.
// Please adapt it to your own needs.
// 
// ========================
//   www.exahype.eu
// ========================

#include "Adjoint.h"

#include "Adjoint_Variables.h"

#include "kernels/KernelUtils.h"
#include "peano/utils/Loop.h"

tarch::logging::Log earthadj::Adjoint::_log( "earthadj::Adjoint" );

constexpr uint sigma11=0;
constexpr uint sigma22=1;
constexpr uint sigma12=2;
constexpr uint uu=3;
constexpr uint vv=4;
constexpr uint lamb =5;//lambda is already used for eigenvalues
constexpr uint mu=6;
constexpr uint rho=7;

void earthadj::Adjoint::init(const std::vector<std::string>& cmdlineargs,const exahype::parser::ParserView& constants) {
  // Tip: You find documentation for this method in header file "earthadj::Adjoint.h".
  
  // @todo Please implement/augment if required

    
}

void earthadj::Adjoint::adjustPointSolution(const double* const x,const double t,const double dt,double* const Q) {
  // Tip: You find documentation for this method in header file "earthadj::Adjoint.h".
  // Tip: See header file "earthadj::AbstractAdjoint.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.
  
  // @todo Please implement/augment if required
  if (tarch::la::equals(t,0.0)) {
    Q[0] = 0.0;
    Q[1] = 0.0;
    Q[2] = 0.0;
    Q[3] = 0.0;
    Q[4] = 0.0;
    Q[5] = 0.0;
    Q[6] = 0.0;
    Q[7] = 0.0;
  }
}

void earthadj::Adjoint::boundaryValues(const double* const x,const double t,const double dt,const int faceIndex,const int direction,const double* const fluxIn,const double* const stateIn,const double* const gradStateIn,double* const fluxOut,double* const stateOut) {
  // Tip: You find documentation for this method in header file "earthadj::Adjoint.h".
  // Tip: See header file "earthadj::AbstractAdjoint.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.

  // @todo Please implement/augment if required
  stateOut[0] = 0.0;
  stateOut[1] = 0.0;
  stateOut[2] = 0.0;
  stateOut[3] = 0.0;
  stateOut[4] = 0.0;

  fluxOut[0] = 0.0;
  fluxOut[1] = 0.0;
  fluxOut[2] = 0.0;
  fluxOut[3] = 0.0;
  fluxOut[4] = 0.0;
}

exahype::solvers::Solver::RefinementControl earthadj::Adjoint::refinementCriterion(const double* const luh,const tarch::la::Vector<DIMENSIONS,double>& cellCentre,const tarch::la::Vector<DIMENSIONS,double>& cellSize,double t,const int level) {
  // Tip: You find documentation for this method in header file "earthadj::Adjoint.h".
  // Tip: See header file "earthadj::AbstractAdjoint.h" for toolkit generated compile-time 
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


void earthadj::Adjoint::eigenvalues(const double* const Q,const int direction,double* const lambda) {
  // Tip: You find documentation for this method in header file "earthadj::Adjoint.h".
  // Tip: See header file "earthadj::AbstractAdjoint.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.
  auto cp=std::sqrt((Q[lamb]+2*Q[mu])/Q[rho]);
  auto cs=std::sqrt(Q[mu]/Q[rho]);
  // @todo Please implement/augment if required
  lambda[0] = -cp;
  lambda[1] = cp;
  lambda[2] = -cs;
  lambda[3] = cs;
  lambda[4] = 0;
}





void earthadj::Adjoint::flux(const double* const Q,double** const F) {
  // Tip: You find documentation for this method in header file "earthadj::Adjoint.h".
  // Tip: See header file "earthadj::AbstractAdjoint.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.
  
  // @todo Please implement/augment if required
  F[0][sigma11] = Q[uu]/Q[rho];
  F[0][sigma22] = 0.0;
  F[0][sigma12] = Q[vv]/Q[rho];
  F[0][uu] = (Q[lamb]+2*Q[mu])*Q[sigma11]+Q[lamb]*Q[sigma22];
  F[0][vv] = Q[mu]*Q[sigma12];
  
  F[1][sigma11] = 0.0;
  F[1][sigma22] = Q[vv]/Q[rho];
  F[1][sigma12] = Q[uu]/Q[rho];
  F[1][uu] = Q[mu]*Q[sigma12];
  F[1][vv] = (Q[lamb]+2*Q[mu])*Q[sigma22]+Q[lamb]*Q[sigma11];
  
}





