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
	int xsize=0;
	int ysize=0;
	int xpoints=0;
	int ypoints=0;
	int amr_steps=1;


	void parse(const char *filename, const tarch::la::Vector<2, double> &offsetPar,
			   const tarch::la::Vector<2, double> &domainsizePar, const double maximumMeshSize);
	int get_level(const tarch::la::Vector<DIMENSIONS,double>& cellCentre,const tarch::la::Vector<DIMENSIONS,double>& cellSize);
	/**
	 * Get level with data being aligned to the cells
	 * @param cellCentre
	 * @return
	 */
	int get_level(const tarch::la::Vector<2, double> &cellCentre, int gridnr);

};





#endif //EXAHYPE_ENGINE_PARSEMR_H
