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
#include "exahype/parser/Parser.h"

tarch::logging::Log earthadj::Forward::_log("earthadj::Forward");


void
earthadj::Forward::init(const std::vector<std::string> &cmdlineargs, const exahype::parser::ParserView &constants) {
	// Tip: You find documentation for this method in header file "earthadj::Forward.h".

	// @todo read when to refine
	auto& parser=constants.getParser();

	std::string path=parser.getStringFromPath("/solvers/0/adg","", true);
	std::cout <<path<<"\n";
	refine = path.length()>0;
	initPointSourceLocations(cmdlineargs, constants);
	if (refine)
		mrparser.parse(path.data(), _domainOffset, _domainSize, 0);
//	mrparser.parse("/home/sven/uni/mt/mt/experiments/outputE/no-refinement.npy", _domainOffset, _domainSize);
}

void earthadj::Forward::adjustPointSolution(const double *const x, const double t, const double dt, double *const Q) {
	// Tip: You find documentation for this method in header file "earthadj::Forward.h".
	// Tip: See header file "earthadj::AbstractForward.h" for toolkit generated compile-time
	//      constants such as Order, NumberOfVariables, and NumberOfParameters.

	// @todo Please implement/augment if required
	if (tarch::la::equals(t, 0.0)) {
		auto xx = x[0];
		auto yy = x[1];

		Q[sigma11] = 0.0;
		Q[sigma22] = 0.0;
		Q[sigma12] = 0.0;
		Q[uu] = 0.0;
		Q[vv] = 0.0;

//		WP1(Q,xx,yy);
//		second_example(Q,xx,yy);
		vsp_helsinki(Q,xx,yy);


		// first example
//		if (xx < 7.5) {
//			Q[lamb] = 2.0;
//			Q[mu] = 0.5;
//		} else {
//			Q[lamb] = 2.0;
//			Q[mu] = 2.0;
//		}
//		Q[rho] = 1.0;


		//LOH non scaled:
//	  if(yy<-1000) {
//		  Q[rho]=2700;
//		  Q[mu]=30.67e9;
//		  Q[lamb]=144e9;
//
//
//	  } else{
//		  Q[rho]=2600;
//		  Q[mu]=10.4e9;
//		  Q[lamb]=36.4e9;
//	  }

	}
}

void earthadj::Forward::boundaryValues(const double *const x, const double t, const double dt, const int faceIndex,
									   const int direction, const double *const fluxIn, const double *const stateIn,
									   const double *const gradStateIn, double *const fluxOut, double *const stateOut) {
	// Tip: You find documentation for this method in header file "earthadj::Forward.h".
	// Tip: See header file "earthadj::AbstractForward.h" for toolkit generated compile-time
	//      constants such as Order, NumberOfVariables, and NumberOfParameters.

	// Specified traction
	if (faceIndex == 3) {
		freeSurface(direction, stateIn, stateOut);
	} else {
		zeroBoundary(direction, stateIn, stateOut);
	}
//	zeroBoundary(direction,stateIn,stateOut);
}

exahype::solvers::Solver::RefinementControl
earthadj::Forward::refinementCriterion(const double *const luh, const tarch::la::Vector<DIMENSIONS, double> &cellCentre,
									   const tarch::la::Vector<DIMENSIONS, double> &cellSize, double t,
									   const int level) {
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
//  if(cellCentre[0]<12000&&cellCentre[0]> -2000&&cellCentre[1]>-3000)
//  	return exahype::solvers::Solver::RefinementControl::Refine;
	if (refine && t == 0) {
		auto lvl = mrparser.get_level(cellCentre, -42);
		if (level - getCoarsestMeshLevel() < lvl)
			return exahype::solvers::Solver::RefinementControl::Refine;
		else
			return exahype::solvers::Solver::RefinementControl::Keep;
	}
////	if (cellCentre[0]<10.0/7&& cellCentre[1]<10.0/7)
//	{
////		std::cout <<"miau\n";
//		return exahype::solvers::Solver::RefinementControl::Refine;
//	}
	return exahype::solvers::Solver::RefinementControl::Keep;
}

//*****************************************************************************
//******************************** PDE ****************************************
// To use other PDE terms, specify them in the specification file, delete this 
// file and its header and rerun the toolkit
//*****************************************************************************


void earthadj::Forward::eigenvalues(const double *const Q, const int direction, double *const lambda) {
	// Tip: You find documentation for this method in header file "earthadj::Forward.h".
	// Tip: See header file "earthadj::AbstractForward.h" for toolkit generated compile-time
	//      constants such as Order, NumberOfVariables, and NumberOfParameters.

	// @todo Please implement/augment if required
	auto cp = std::sqrt((Q[lamb] + 2 * Q[mu]) / Q[rho]);
	auto cs = std::sqrt(Q[mu] / Q[rho]);
//	std::cout << mrparser.dataowner[direction]<<"\n";

	lambda[0] = -cp;
	lambda[1] = cp;
	lambda[2] = -cs;
	lambda[3] = cs;
	lambda[4] = 0;
}


void earthadj::Forward::nonConservativeProduct(const double *const Q, const double *const *const gradQ,
											   double **const BgradQ) {
	// Tip: You find documentation for this method in header file "earthadj::Forward.h".
	// Tip: See header file "earthadj::AbstractForward.h" for toolkit generated compile-time
	//      constants such as Order, NumberOfVariables, and NumberOfParameters.

//  std::cout <<"ncp"<<std::endl;
	// @todo Please implement/augment if required
	BgradQ[0][sigma11] = -(Q[lamb] + 2 * Q[mu]) * gradQ[0][uu];;
	BgradQ[0][sigma22] = -Q[lamb] * gradQ[0][uu];
	BgradQ[0][sigma12] = -Q[mu] * gradQ[0][vv];
	BgradQ[0][uu] = -gradQ[0][sigma11] / Q[rho];
	BgradQ[0][vv] = -gradQ[0][sigma12] / Q[rho];
//  BgradQ[0][lamb] = 0.0;
//  BgradQ[0][mu] = 0.0;
//  BgradQ[0][rho] = 0.0;

	BgradQ[1][sigma11] = -Q[lamb] * gradQ[1][vv];
	BgradQ[1][sigma22] = -(Q[lamb] + 2 * Q[mu]) * gradQ[1][vv];
	BgradQ[1][sigma12] = -Q[mu] * gradQ[1][uu];
	BgradQ[1][uu] = -gradQ[1][sigma12] / Q[rho];
	BgradQ[1][vv] = -gradQ[1][sigma22] / Q[rho];
//  BgradQ[1][lamb] = 0.0;
//  BgradQ[1][mu] = 0.0;
//  BgradQ[1][rho] = 0.0;
}

void earthadj::Forward::initPointSourceLocations(const std::vector<std::string> &cmdlineargs,
												 const exahype::parser::ParserView &constants) {
//	pointSourceLocation[0][0]=0.0;
//	pointSourceLocation[0][1]=-2000.0;
	pointSourceLocation[0][0] = 5.0;
	pointSourceLocation[0][1] = 5.0;
}


void earthadj::Forward::pointSource(const double *const Q, const double *const x, const double t, const double dt,
									double *const forceVector, int n) {
	double T = 0.1;
	double M_0 = 1.0e3;
	auto M_xy = (M_0 * t / (T * T)) * std::exp(-t / T);
	forceVector[sigma12] = M_xy;
	forceVector[sigma11] = 0.0;
	forceVector[sigma22] = 0.0;
	forceVector[uu] = 0.0;
	forceVector[vv] = 0.0;
}

