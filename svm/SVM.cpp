#include "SVM.h"
#include "random"
#include "ctime"
#include "cstdlib"
using namespace std;
SVM::SVM()
{
}

SVM::~SVM()
{
}
void SVM::apply_grad()
{
	for (int i = 0; i < weight.size(); i++)
	{
		weight[i] -= lr * grad_weight[i];
		grad_weight[i] = 0;
	}
		
}


void SVM::forward(vector<Data> input)
{
	output.clear();
	input_data.clear();
	for (int i = 0; i < input.size(); i++)
	{
		input_data.push_back(input[i]);
		output.push_back(0);
		for (int j = 0; j < input[i].data.size(); j++)
			output[i] += weight[j] * input[i].data[j];
	}
}
void SVM::backward(vector<float> grad_output)
{
	for (int i = 0; i < grad_weight.size(); i++)
	{
		grad_weight[i]=0;
		for (int j = 0; j < grad_output.size(); j++)
		{
			grad_weight[i] += grad_output[j] * input_data[j].data[i];
		}
	}
}
void SVM::set_lr_rate(float learn_rate)
{
	lr = learn_rate;
}
void SVM::weight_init(int dim)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < dim + 1; i++)
	{
		weight.push_back(rand() / (RAND_MAX + 1.0)-0.5);
		grad_weight.push_back(0);
	}
		
}