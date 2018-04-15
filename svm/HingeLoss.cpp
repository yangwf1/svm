#include "HingeLoss.h"



HingeLoss::HingeLoss()
{
}


HingeLoss::~HingeLoss()
{
}
void HingeLoss::forward(vector<float> input, vector<float>target)
{
	loss = 0;
	grad_input.clear();
	for (int i = 0; i < input.size(); i++)
	{
		if (1 - input[i] * target[i] > 0)
		{
			loss = loss + 1 - input[i] * target[i];
			grad_input.push_back(-target[i]);
		}
		else
		{
			grad_input.push_back(0);
		}
	}
}

void HingeLoss::backward()
{
	
}