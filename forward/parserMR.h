//
// Created by sven on 15.01.22.
//

#ifndef EXAHYPE_ENGINE_PARSEMR_H
#define EXAHYPE_ENGINE_PARSEMR_H


#include "peano/utils/Dimensions.h"
#include "tarch/la/Vector.h"

class ParserMR {
public:
	int64_t *data; //data is handled by dataowner
	std::vector<char> dataowner;//Do not remove, destruction deallocates data
	tarch::la::Vector<DIMENSIONS,double> offset;
	tarch::la::Vector<DIMENSIONS,double> domainsize;
	ulong xsize=0;
	ulong ysize=0;


	void parse(const char *filename, const tarch::la::Vector<2, double> &offsetPar, const tarch::la::Vector<2, double> &domainsizePar);
	int get_level(const tarch::la::Vector<DIMENSIONS,double>& cellCentre,const tarch::la::Vector<DIMENSIONS,double>& cellSize);

};





#endif //EXAHYPE_ENGINE_PARSEMR_H
