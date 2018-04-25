#ifndef _FILEIOH_
#define _FILEIOH_

#define MAX_NAME 20

#define _TEST_ 1
#define _EXIST_ 2
#define _NEW_ 3

#define ADD_TEST 100
#define MUL_TEST 200
#define DIV_TEST 300


#include <fstream>
#include "NeuralNetwork.h"



using namespace std;

class FileIO
{

int NumInputs;
int Inputs;
int NumHiddenLayers;
int HiddenNeuronsInEachLayer[MAX_HIDDEN];
int NumOutputs;
int Outputs;

int NeuronsInEachLayer[TOTAL_NEURONS];

double Inp[MAX_INPUT];
double Out[MAX_OUTPUT];

double Weight[LAYERS][TOTAL_NEURONS][TOTAL_NEURONS];

char FileName[MAX_NAME];
int Mode;

void ReadHiddenLayers(int Layers);


public:
	
	FileIO();
	FileIO(int NumInput , int NumHiddenLayer , int NumOutpus);
	void OpenNeuralNetwork(char FileName[MAX_NAME] , int Mode);
	
	void CreateInputFile(char FileName[MAX_NAME] , int Type);	
};

#endif
