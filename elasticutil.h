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

#endif  // EXAHYPE_ENGINE_ELASTICUTIL_H
