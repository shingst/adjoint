//
// Created by sven on 15.01.22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "parserMR.h"
#include "cnpy.h"


// TODO remember 0 0 of array is lower left corner
void ParserMR::parse(const char *filename, const tarch::la::Vector<2, double> &offsetPar, const tarch::la::Vector<2, double> &domainsizePar) {
//	std::ifstream ifstr{filename};
//	long x=0;
//	long y=0;
//	char c;
//	ifstr >> c>> c>> x >>c>> y>>c;// reads # (x, y)
//	std::cout <<"x"<< x <<"y"<<y<<c<<"\n";
//	std::string buff;
//	getline(ifstr, buff );
//	double xx=-5.3;
//	ifstr>>xx;
//	std::cout <<xx;
//	std::vector<double> vals;//TODO switch to int
//	vals.resize(x*y);
	offset=offsetPar;
	domainsize=domainsizePar;
	cnpy::NpyArray arr= cnpy::npy_load(filename);
	data = arr.data<int64_t>();//TODO switch to int
	dataowner.push_back('a');
	arr.data_holder->swap(dataowner);/// gives me owner ship of the data
	xsize=arr.shape[0];
	ysize=arr.shape[1];
//	std::cout <<"x"<< xsize<<"y"<<data[25]+0<<"\n";
}

int ParserMR::get_level(const tarch::la::Vector<2, double> &cellCentre, const tarch::la::Vector<2, double> &cellSize) {
	auto xmap=(cellCentre[0]-offset[0])*xsize/domainsize[0];//TODO respect the 0.5 center !!!
	auto xind= (int)std::floor(xmap-0.5);
	auto ymap=(cellCentre[1]-offset[1])*ysize/domainsize[1];
	auto yind= (int)std::floor(ymap-0.5);

//	for (int i = 0; i < 2; ++i) {
//		for (int j = 0; j < 2; ++j) {
//			ret=std::max(ret,(int)data[xind+i+(yind+j)*xsize]);
//		}
//	}
	int ret=0;
	if(xind>0){
		if(yind>0)
			ret=std::max(ret,(int)data[xind+(yind)*xsize]);
		if(yind<ysize-1)
			ret=std::max(ret,(int)data[xind+(yind+1)*xsize]);
	}
	if(xind<xsize-1) {
		if (yind > 0)
			ret = std::max(ret, (int) data[xind + 1 + (yind) * xsize]);
		if(yind<ysize-1)
			ret=std::max(ret,(int)data[xind+1+(yind+1)*xsize]);
	}


	return ret;
}









//int main (int argc, char *argv[]) {
////	parse("adjoint/MeshRefinement/test.txt");
//	ParserMR a{};
//	a.parse("/home/sven/uni/mt/mt/experiments/outputE/test1-0.npy");
//	std::cout<< a.data[24]<<"\n";
//}



