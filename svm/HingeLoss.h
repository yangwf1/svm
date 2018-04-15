#pragma once
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
class HingeLoss
{
public:
	HingeLoss();
	~HingeLoss();
	void forward(vector<float> input, vector<float>target);
	void backward();
	float loss;
	vector<float> grad_input;

};

