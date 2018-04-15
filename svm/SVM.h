#pragma once
#include<vector>
#include<iostream>
#include "Data.h"
using namespace std;

class SVM
{
public:
	SVM();
	~SVM();
	void forward(const vector<Data> input);
	void backward(vector<float> grad_output);
	void apply_grad();
	void set_lr_rate(float learn_rate);
	void weight_init(int dim);
	float lr;
	vector <float>weight;
	vector<Data> input_data;
	vector<float> output;
	vector<float> grad_weight;
};

