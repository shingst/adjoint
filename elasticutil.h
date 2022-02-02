//
// Created by sven on 08.12.21.
//

#ifndef EXAHYPE_ENGINE_ELASTICUTIL_H
#define EXAHYPE_ENGINE_ELASTICUTIL_H

constexpr uint sigma11 = 0;
constexpr uint sigma22 = 1;
constexpr uint sigma12 = 2;
constexpr uint uu = 3;
constexpr uint vv = 4;
constexpr uint lamb = 5;//lambda is already used for eigenvalues
constexpr uint mu = 6;
constexpr uint rho = 7;

inline void specifiedTraction(const int direction,const double *const stateIn,double *const stateOut) {
	if (direction == 0) {
		stateOut[sigma11] = -stateIn[sigma11];
		stateOut[sigma22] = stateIn[sigma22];
	} else {
		stateOut[sigma11] = stateIn[sigma11];
		stateOut[sigma22] = -stateIn[sigma22];
	}
	stateOut[sigma12] = -stateIn[sigma12];
	stateOut[uu] = stateIn[uu];
	stateOut[vv] = stateIn[vv];

	// Do not remove!
	stateOut[lamb] = stateIn[lamb];
	stateOut[mu] = stateIn[mu];
	stateOut[rho] = stateIn[rho];
}

inline void specifiedMotion(const int direction,const double *const stateIn,double *const stateOut) {
	stateOut[sigma11] = stateIn[sigma11];
	stateOut[sigma22] = stateIn[sigma22];

	stateOut[sigma12] = stateIn[sigma12];
	stateOut[uu] = -stateIn[uu];
	stateOut[vv] = -stateIn[vv];
	// Do not remove!
	stateOut[lamb] = stateIn[lamb];
	stateOut[mu] = stateIn[mu];
	stateOut[rho] = stateIn[rho];
}

inline void zeroBoundary(const int direction,const double *const stateIn,double *const stateOut) {
	stateOut[sigma11] = 0.0;
	stateOut[sigma22] = 0.0;

	stateOut[sigma12] = 0.0;
	stateOut[uu] = 0.0;
	stateOut[vv] = 0.0;
	// Do not remove!
	stateOut[lamb] = stateIn[lamb];
	stateOut[mu] = stateIn[mu];
	stateOut[rho] = stateIn[rho];
}

inline void freeSurface(const int direction,const double *const stateIn,double *const stateOut) {
	stateOut[sigma11] = -stateIn[sigma11];
	stateOut[sigma22] = -stateIn[sigma22];

	stateOut[sigma12] = -stateIn[sigma12];
	stateOut[uu] = stateIn[uu];
	stateOut[vv] = stateIn[vv];
	// Do not remove!
	stateOut[lamb] = stateIn[lamb];
	stateOut[mu] = stateIn[mu];
	stateOut[rho] = stateIn[rho];
}

inline void second_example(double *const Q, double x,double y){
	if( 2*x+y>22){ //2*x+y>22
		Q[rho]=7;
		Q[mu]=30;
		Q[lamb]=100;
	} else if (x+3*y>27){
		Q[rho]=1.5;
		Q[mu]=40;
		Q[lamb]=100;
	} else if(x+1.5*y<9){
		Q[rho]=4.7;
		Q[mu]=20;
		Q[lamb]=100;
	} else {
		Q[rho]=2.7;
		Q[mu]=30.67;
		Q[lamb]=144;
	}

}


#endif  // EXAHYPE_ENGINE_ELASTICUTIL_H
