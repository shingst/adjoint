//
// Created by sven on 15.01.22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "parserMR.h"
#include "cnpy.h"


// TODO remember 0 0 of array is lower left corner
int64_t * parse(const char *filename){
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
	cnpy::NpyArray arr= cnpy::npy_load(filename);
	auto loaded_data = arr.data<int64_t>();//TODO switch to int
	std::vector<char>data_destructor{};
//	arr.data_holder->swap(data_destructor);/// gives me owner ship of the data
//	auto loaded_data = std::reinterpret_pointer_cast<double>(arr.data_holder[0]);
	ulong x=arr.shape[0];
	ulong y=arr.shape[1];
	std::cout <<"x"<< x <<"y"<<loaded_data[25]+0<<"\n";
	std::vector<double> a;
	auto tmp=arr.data_holder.get();
	std::cout << &(tmp[0])<<" "<<loaded_data<<"\n";

	return loaded_data;
}






int main (int argc, char *argv[]) {
//	parse("adjoint/MeshRefinement/test.txt");
	auto x=parse("/home/sven/uni/mt/mt/experiments/outputE/test1-0.npy");
	std::cout<< x[24]<<"\n";
}