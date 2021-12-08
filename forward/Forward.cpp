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

tarch::logging::Log earthadj::Forward::_log( "earthadj::Forward" );

constexpr uint sigma11=0;
constexpr uint sigma22=1;
constexpr uint sigma12=2;
constexpr uint uu=3;
constexpr uint vv=4;
constexpr uint lamb =5;//lambda is already used for eigenvalues
constexpr uint mu=6;
constexpr uint rho=7;





void earthadj::Forward::init(const std::vector<std::string>& cmdlineargs,const exahype::parser::ParserView& constants) {
  // Tip: You find documentation for this method in header file "earthadj::Forward.h".
  
  // @todo Please implement/augment if required

    
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
    Q[uu] = std::exp(-(xx-5)*(xx-5)-(yy-5)*(yy-5));
    Q[vv] = std::exp(-(xx-5)*(xx-5)-(yy-5)*(yy-5));;
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

  // Specified traction
  if(direction==0) {
    stateOut[sigma11] = -stateIn[sigma11];
    stateOut[sigma22] = stateIn[sigma22];
  }
  else {
    stateOut[sigma11]=stateIn[sigma11];
    stateOut[sigma22] = -stateIn[sigma22];
  }
  stateOut[sigma12] = -stateIn[sigma12];
  stateOut[uu] = stateIn[uu];
  stateOut[vv] = stateIn[vv];

  //Do not remove!
  stateOut[lamb] = stateIn[lamb];
  stateOut[mu] = stateIn[mu];
  stateOut[rho] = stateIn[rho];

  // Specified Motion
  stateOut[sigma11]=stateIn[sigma11];
  stateOut[sigma22] = stateIn[sigma22];

  stateOut[sigma12] = stateIn[sigma12];
  stateOut[uu] = -stateIn[uu];
  stateOut[vv] = -stateIn[vv];



// Zeroing BOundary
//  for(int i=0;i<5;i++)
//    stateOut[i]=0.0;



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









void  earthadj::Forward::nonConservativeProduct(const double* const Q,const double* const * const gradQ,double** const BgradQ) {
  // Tip: You find documentation for this method in header file "earthadj::Forward.h".
  // Tip: See header file "earthadj::AbstractForward.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.

//  std::cout <<"ncp"<<std::endl;
  // @todo Please implement/augment if required
  BgradQ[0][sigma11] = -(Q[lamb]+2*Q[mu])*gradQ[0][uu];;
  BgradQ[0][sigma22] = -Q[lamb]*gradQ[0][uu];
  BgradQ[0][sigma12] = -Q[mu]*gradQ[0][vv];
  BgradQ[0][uu] = -gradQ[0][sigma11]/Q[rho];
  BgradQ[0][vv] = -gradQ[0][sigma12]/Q[rho];
//  BgradQ[0][lamb] = 0.0;
//  BgradQ[0][mu] = 0.0;
//  BgradQ[0][rho] = 0.0;

  BgradQ[1][sigma11] = -Q[lamb]*gradQ[1][vv];
  BgradQ[1][sigma22] = -(Q[lamb]+2*Q[mu])*gradQ[1][vv];
  BgradQ[1][sigma12] = -Q[mu]*gradQ[1][uu];
  BgradQ[1][uu] = -gradQ[1][sigma12]/Q[rho];
  BgradQ[1][vv] = -gradQ[1][sigma22]/Q[rho];
//  BgradQ[1][lamb] = 0.0;
//  BgradQ[1][mu] = 0.0;
//  BgradQ[1][rho] = 0.0;
}


