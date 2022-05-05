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
#include "../elasticutil.h"


tarch::logging::Log earthadj::Adjoint::_log("earthadj::Adjoint");


void
earthadj::Adjoint::init(const std::vector<std::string> &cmdlineargs, const exahype::parser::ParserView &constants) {
	// Tip: You find documentation for this method in header file "earthadj::Adjoint.h".

	// @todo Please implement/augment if required
//	initPointSourceLocations(cmdlineargs,constants);


}

void earthadj::Adjoint::adjustPointSolution(const double *const x, const double t, const double dt, double *const Q) {
	// Tip: You find documentation for this method in header file "earthadj::Adjoint.h".
	// Tip: See header file "earthadj::AbstractAdjoint.h" for toolkit generated compile-time
	//      constants such as Order, NumberOfVariables, and NumberOfParameters.

	// @todo Please implement/augment if required
	if (tarch::la::equals(t, 0.0)) {
		auto xx = x[0];
		auto yy = x[1];

		double probex=8.0;
		double probey=0.0;

//		if ((xx < 8.5 && xx > 7.5) && (yy < 11.0 && yy > 9.0)) {
		auto dir = std::exp(-(xx-probex)*(xx-probex)*4-(yy-probey)*(yy-probey)*4)/(4*M_PI);
//		Q[sigma11] = dir;//dir*-125.153;
//		Q[sigma22] = dir;//80.77*dir;
//		Q[sigma12] = dir;//-28.6597*dir;
//
//		Q[uu]=0.0;//TODO !!!!!!!!
//		Q[vv]=0.0;

		Q[sigma11] = 0.0;//dir*-125.153;
		Q[sigma22] = 0.0;//80.77*dir;
		Q[sigma12] = 0.0;//-28.6597*dir;

//		Q[uu]=-dir*3/5.83095;//dir;//TODO cutoff direc delata?
//		Q[vv]=dir*5/5.83095;//dir;
		Q[uu]=0.0;//dir;//TODO cutoff direc delata?
		Q[vv]=0.0;//dir;
//		} else {
//			Q[sigma11] = 0.0;
//			Q[sigma22] = 0.0;
//			Q[sigma12] = 0.0;
//			Q[uu]=0.0;
//			Q[vv]=0.0;
//		}

//    Q[uu] = std::exp(-(xx-5)*(xx-5)-(yy-5)*(yy-5));
//    Q[vv] = std::exp(-(xx-5)*(xx-5)-(yy-5)*(yy-5));;
//		Q[uu] = 0.0;//-86.857*dir;
//		Q[vv] = 0.0;//25.2797*dir;
//		if (xx < 7.5) {
//			Q[lamb] = 2.0;
//			Q[mu] = 0.5;
//		} else {
//			Q[lamb] = 2.0;
//			Q[mu] = 2.0;
//		}
//		Q[rho] = 1.0;
//		WP1(Q,xx,yy);
//		second_example(Q,xx,yy);
		vsp_helsinki(Q,xx,yy);
	}
}

void earthadj::Adjoint::boundaryValues(const double *const x, const double t, const double dt, const int faceIndex,
									   const int direction, const double *const fluxIn, const double *const stateIn,
									   const double *const gradStateIn, double *const fluxOut, double *const stateOut) {
	// Tip: You find documentation for this method in header file "earthadj::Adjoint.h".
	// Tip: See header file "earthadj::AbstractAdjoint.h" for toolkit generated compile-time
	//      constants such as Order, NumberOfVariables, and NumberOfParameters.

	// @todo Please implement/augment if required
//	zeroBoundary(direction, stateIn, stateOut);
	if (faceIndex == 2) {
		freeSurface(direction, stateIn, stateOut);
	} else {
		zeroBoundary(direction, stateIn, stateOut);
	}
}

exahype::solvers::Solver::RefinementControl
earthadj::Adjoint::refinementCriterion(const double *const luh, const tarch::la::Vector<DIMENSIONS, double> &cellCentre,
									   const tarch::la::Vector<DIMENSIONS, double> &cellSize, double t,
									   const int level) {
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
//	if (t == 0)
//		if (cellCentre[0] < 3 && cellCentre[1] > 4 && cellCentre[1] < 8)
//			return exahype::solvers::Solver::RefinementControl::Refine;
	return exahype::solvers::Solver::RefinementControl::Keep;

}

//*****************************************************************************
//******************************** PDE ****************************************
// To use other PDE terms, specify them in the specification file, delete this 
// file and its header and rerun the toolkit
//*****************************************************************************


void earthadj::Adjoint::eigenvalues(const double *const Q, const int direction, double *const lambda) {
	// Tip: You find documentation for this method in header file "earthadj::Adjoint.h".
	// Tip: See header file "earthadj::AbstractAdjoint.h" for toolkit generated compile-time
	//      constants such as Order, NumberOfVariables, and NumberOfParameters.
	auto cp = std::sqrt((Q[lamb] + 2 * Q[mu]) / Q[rho]);
	auto cs = std::sqrt(Q[mu] / Q[rho]);
	// @todo Please implement/augment if required
	lambda[0] = -cp;
	lambda[1] = cp;
	lambda[2] = -cs;
	lambda[3] = cs;
	lambda[4] = 0;
}


void earthadj::Adjoint::flux(const double *const Q, double **const F) {
	// Tip: You find documentation for this method in header file "earthadj::Adjoint.h".
	// Tip: See header file "earthadj::AbstractAdjoint.h" for toolkit generated compile-time
	//      constants such as Order, NumberOfVariables, and NumberOfParameters.

	// @todo Please implement/augment if required
	F[0][sigma11] = Q[uu] / Q[rho];
	F[0][sigma22] = 0.0;
	F[0][sigma12] = Q[vv] / Q[rho];
	F[0][uu] = (Q[lamb] + 2 * Q[mu]) * Q[sigma11] + Q[lamb] * Q[sigma22];
	F[0][vv] = Q[mu] * Q[sigma12];

	F[1][sigma11] = 0.0;
	F[1][sigma22] = Q[vv] / Q[rho];
	F[1][sigma12] = Q[uu] / Q[rho];
	F[1][uu] = Q[mu] * Q[sigma12];
	F[1][vv] = (Q[lamb] + 2 * Q[mu]) * Q[sigma22] + Q[lamb] * Q[sigma11];

}

/*
void earthadj::Adjoint::initPointSourceLocations(const std::vector<std::string> &cmdlineargs,
												 const exahype::parser::ParserView &constants) {
	pointSourceLocation[0][0]=3.0;
	pointSourceLocation[0][1]=4.0;
}


void earthadj::Adjoint::pointSource(const double *const Q, const double *const x, const double t, const double dt,
									double *const forceVector, int n) {
	double T=0.1;
	double M_0=1e4;
//	auto M_xy=(M_0*t/(T*T))*std::exp(-t*10/T);
	auto M_xy=M_0;
	forceVector[sigma12]=M_xy;
	forceVector[sigma11]=M_xy;
	forceVector[sigma22]=M_xy;
	forceVector[uu]=0.0;
	forceVector[vv]=0.0;
}*/



