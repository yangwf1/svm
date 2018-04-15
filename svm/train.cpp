#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include "SVM.h"
#include "HingeLoss.h""
#include "Data.h"

using namespace std;
int main()
{
	int batch_size = 5;
	int epoches = 1;
	float lr = 0.01;
	int data_dim = 4;
	string train_data_path = "train.txt";
	string test_data_path = "test.txt";
	/*this function is used to generate next train batch using sample index*/
	vector<Data> get_next_batch(vector<int> sample_index, vector<vector<float>>input);
	/*all train samples are stored in train_data,each row represents a train sample,and is the same for test data in test_data*/
	vector<vector<float>> train_data;
	vector<vector<float>> test_data;
	/*calculate number of train sample and test sample,they are used to gegerate random shuffled sample index*/
	int number_train_sample = 0;
	int number_test_sample = 0;

	ifstream f_train(train_data_path);
	ifstream f_test(test_data_path);
	/*prepare train data,read all data in train.txt and save it in train_data*/
	vector<float> tmp;
	float data_tmp;
	while (f_train)
	{
		number_train_sample += 1;
		f_train >> data_tmp;
		//cout << data_tmp << endl;
		tmp.push_back(data_tmp);
		if (number_train_sample % 5 == 0)
		{
			train_data.push_back(tmp);
			tmp.clear();
		}
	}
	number_train_sample = number_train_sample / 5;
	/*prepare test data,read all data in test.txt and save it in test_data*/
	tmp.clear();
	while (f_test)
	{
		number_test_sample += 1;
		f_test >> data_tmp;
		//cout << data_tmp << endl;
		tmp.push_back(data_tmp);
		if (number_test_sample % 5 == 0)
		{
			test_data.push_back(tmp);
			tmp.clear();
		}
	}
	number_test_sample = number_test_sample / 5;

	/*begin to train svm model*/
	SVM model;
	model.set_lr_rate(lr);
	model.weight_init(data_dim);
	HingeLoss loss;

	int current_index = 0;
	vector<int> input_index;
	vector<Data> batch;
	vector<float> label_batch;
	int accurate_predict = 0;
	int iter = 0;
	for(int epoch=0;epoch<epoches;epoch++)
	{ 
		iter = 0;
		current_index = 0;
		/*random shuffle train sample index*/
		random_device rd;
		mt19937 g(rd());
		vector<int> train_data_index;
		for (int i = 0; i < number_train_sample; i++)
		{
			train_data_index.push_back(i);
		}
		shuffle(train_data_index.begin(), train_data_index.end(), g);
		while ((current_index + batch_size) < number_train_sample)
		{
			iter = iter + 1;
			accurate_predict = 0;
			for (int i = 0; i < batch_size; i++)
			{
				input_index.push_back(current_index + i);
			}
			current_index += batch_size;
			batch = get_next_batch(input_index, train_data);
			for (int i = 0; i < batch.size(); i++)
			{
				label_batch.push_back(batch[i].label);
			}
			model.forward(batch);
			loss.forward(model.output,label_batch);
			model.backward(loss.grad_input);
			model.apply_grad();
			/*calculate training accuracy in current batch*/
			for (int i = 0; i < model.output.size(); i++)
			{
				if (label_batch[i] * model.output[i] > 0)
					accurate_predict += 1;
			}
			cout << "epoch:" << epoch << "batch:"<<iter<<" loss:"<<loss.loss<<" accuracy:" << accurate_predict/(batch_size+0.0)<< "\n" << endl;
			input_index.clear();
			batch.clear();
			label_batch.clear();
		}
	}
	/*test the train_ed model on test set*/
	vector<int>test_index;
	vector<Data>test_batch;
	vector<float>test_label;
	for (int i = 0; i < number_test_sample; i++)
		test_index.push_back(i);
	test_batch = get_next_batch(test_index, test_data);
	for (int i = 0; i < test_batch.size(); i++)
		test_label.push_back(test_batch[i].label);
	model.forward(test_batch);
	float accuracy = 0;
	for (int i = 0; i < test_batch.size(); i++)
		if (test_label[i] * model.output[i] > 0)
			accuracy = accuracy+1;
	cout <<(accuracy / (number_test_sample+0.0)) << endl;

}
vector<Data> get_next_batch(vector<int> sample_index, vector<vector<float>>input)
{
	vector<Data> output;
	for (int i = 0; i < sample_index.size(); i++)
	{
		output.push_back(Data(input[sample_index[i]]));
	}
	return output;
}