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

// will only with templates in cpp 20
inline void setQ(double *const Q,double s_wave_speed,double p_wave_speed,double rho_val){
	Q[mu]=s_wave_speed*s_wave_speed*rho_val;
	Q[lamb]=(p_wave_speed*p_wave_speed-2*s_wave_speed*s_wave_speed)*rho_val;
	Q[rho]=rho_val;
}

inline void second_example(double *const Q, double x,double y){
	if( 2*x+y>22){ //2*x+y>22
		setQ(Q,2.9,4.5,2.6);
	} else if (x+3*y>27){
		setQ(Q,4.0,6.3,3.0);
	} else if(x+1.5*y<9){
		setQ(Q,3.2,4.8,2.3);
	} else {
		setQ(Q,3.464,6.0,2.7);
	}
}

inline void vsp_helsinki(double *const Q, double x,double y){
	double s,p=0.0;
	if(y<2){
		p=5.85+0.3*y;
	} else if(y<2.5){
		p=6.45+0.2*(y-2.0);
	} else if(y<3.0){
		p=6.55;
	} else if(y<3.5){
		p=6.55-0.4*(y-3.0);
	}else if(y<4.0){
		p=6.35-0.3*(y-3.5);
	} else if(y<6.0){
		p=6.2-0.1*(y-4.0);
	} else{
		p=6.0;
	}
	s=p/1.71;
	setQ(Q,s,p,2.7);
}

inline void WP1(double *const Q, double x,double y){
	setQ(Q,3.464,6.0,2.7);
}


#endif  // EXAHYPE_ENGINE_ELASTICUTIL_H
