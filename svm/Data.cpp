#include "Data.h"



Data::Data(vector<float> input){
	if (input[0] == 0)
		label = -1;
	else
		label = 1;
	for (int i = 0; i < input.size() - 1; i++)
		data.push_back(input[i+1]);
	data.push_back(1);
};


Data::~Data()
{

};
