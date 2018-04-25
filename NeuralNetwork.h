
#ifndef _NEURALH_
#define _NEURALH_

#define MAX_INPUT 10
#define MAX_HIDDEN 20
#define MAX_HIDDEN_LAYERS 5
#define MAX_OUTPUT 10

#define TOTAL_NEURONS 40

#define LAYERS  MAX_HIDDEN_LAYERS + 2  


#define ALPHA 0.1

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include "FileIO.h"


using namespace std;

class NeuralNetwork
{

int NumInputs;
int NumHiddenLayers;
int HiddenNeuronsInEachLayer[MAX_HIDDEN];
int NeuronsInEachLayer[MAX_INPUT + MAX_OUTPUT + MAX_HIDDEN];
int NumOutputs;
int TotalNeurons;

double Inputs[MAX_INPUT];
double Hidden[MAX_HIDDEN_LAYERS][MAX_HIDDEN];
double Output[MAX_OUTPUT];
double RealOutput[MAX_OUTPUT];

double Network[TOTAL_NEURONS][TOTAL_NEURONS];

double Weights[LAYERS][TOTAL_NEURONS][TOTAL_NEURONS];

double R();
void InitWeights();
void CalcWS();
void UpdateWeights();

double SIGMOID(double x);
bool CheckOutput(double x1 , double x2);

public:
	
	NeuralNetwork();
	NeuralNetwork(int Input , int Hidden , int HiddenLayer[MAX_HIDDEN_LAYERS] , int Output );
	
	void BackProp(double ErrorPercentage);
	void ReadInput(double Inputs[MAX_INPUT]);
	void ReadOutput(double Output[MAX_OUTPUT]);
	void InitNetwork();
	void DEBUG();
	
	
	//File Handling Functions
	
	void LoadTestData(char FileName[MAX_NAME]);
	void LoadNeuronsInEachLayer(int NeuronsInEachLayer[TOTAL_NEURONS]);
	void SaveWeights(double Weight[LAYERS][TOTAL_NEURONS][TOTAL_NEURONS]);
	void LoadWeights(double Weight[LAYERS][TOTAL_NEURONS][TOTAL_NEURONS]);
	
	
};

#endif
