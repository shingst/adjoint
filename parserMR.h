//
// Created by sven on 15.01.22.
//

#ifndef EXAHYPE_ENGINE_PARSEMR_H
#define EXAHYPE_ENGINE_PARSEMR_H



class ParserMR {
public:
	int64_t *data; //data is handled by dataowner
	std::vector<char> dataowner;//Do not remove, destruction deallocates data


	void parse(const char *filename);

};





#endif //EXAHYPE_ENGINE_PARSEMR_H
