#pragma once
#include<vector>
#include<stdio.h>

using namespace std;
class Data
{
public:
	Data(vector<float> input);
	~Data();
	vector<float> data;
	float label;
};

