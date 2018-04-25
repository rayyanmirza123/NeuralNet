#include "NeuralNetwork.h"

/*
Dummy Constructor
*/
NeuralNetwork::NeuralNetwork()
{
	
}

/*
Main Network Creator Constructor
*/

NeuralNetwork::NeuralNetwork(int Input , int Hidden , int HiddenLayer[MAX_HIDDEN_LAYERS] , int Output)
{
	NumInputs = Input;
	NumHiddenLayers = Hidden;
	TotalNeurons = 0;
    
	for(int i=0;i<=NumHiddenLayers-1;i++)
	{
		HiddenNeuronsInEachLayer[i] = HiddenLayer[i];
	  	TotalNeurons += HiddenNeuronsInEachLayer[i];
	}
	
	NumOutputs = Output;
	TotalNeurons += NumInputs + NumOutputs;
}

/*
Initializes network 

Initializes weights with random function R() 

calculate weighted sums

*/

void NeuralNetwork::InitNetwork()
{
	int TotalLayers = NumHiddenLayers + 2;
	int Next = 0;
	
	for(int i=0;i<=NumInputs;i++)
	{
		Network[0][i] = Inputs[i];
	}
	Network[0][NumInputs] = -1;
	
	for(int i=1,s=0;i<=NumHiddenLayers,s<=NumHiddenLayers-1;i++,s++)
	{
		Next = HiddenNeuronsInEachLayer[i];
		for(int j=0;j<=Next;j++)
		{
			Network[i][j] = Hidden[s][j];
		}
		 Network[i][Next] = -1;
	}
	
	for(int i=0;i<=NumOutputs;i++)
	{
		Network[NumHiddenLayers + 2][i] = Output[i];
	}
	
	NeuronsInEachLayer[0] = NumInputs;
	
	for(int i=1,s=0;i<=NumHiddenLayers,s<=NumHiddenLayers;i++,s++)
	{
		NeuronsInEachLayer[i] = HiddenNeuronsInEachLayer[s];
	}
	
	NeuronsInEachLayer[NumHiddenLayers+1] = NumOutputs;
	
}

/*
Generates a random double between 0 and 1

*/

double NeuralNetwork::R()
{
	return ((double)rand()/(double)RAND_MAX);
}

/*
Displays Neural Network State At the Time: 

No Need to call as it is already called in BackProp() Function For Debugging purposes

*/

void NeuralNetwork::DEBUG()
{
	int TotalLayers = NumHiddenLayers + 2;
	int Next = 0;
	cout<<"\n************Neural Network***************\n\n";
	cout<<"\nNo of Inputs : "<<NumInputs<<"\n";
	cout<<"\bNo of Outputs : "<<NumOutputs<<"\n";
	cout<<"\nNo of Hidden Layers : "<<NumHiddenLayers<<"\n";
	
	for(int i=0;i<=NumHiddenLayers-1;i++)
	{
		cout<<"\nNo of Neurons in each hidden layer : "<<i+1<<" : "<<HiddenNeuronsInEachLayer[i]<<"\n";
	}
	
	cout<<"\n Total Neurons in Network : "<<TotalNeurons<<"\n";
	
	for(int i=0;i<=TotalLayers;i++)
	{
		cout<<"Neuron In each Layer : "<<NeuronsInEachLayer[i]<<"\n";
	}
	
	cout<<"\nCalculated Output : \n";
	
	for(int i=0;i<=NumOutputs-1;i++)
	{
	cout<<"\nOutput for Input : "<<i+1<<" : "<<Output[i]<<"\n";	
	}
	
	cout<<"\n************Weights******************** \n\n";
	
	
	for(int i=0;i<=TotalLayers-2;i++)
	{
		cout<<"Layer : "<<i+1<<"\n";
		for(int j=0;j<=NeuronsInEachLayer[i];j++)
		{
			cout<<"Neuron : "<<j+1<<"\n";
			Next = NeuronsInEachLayer[i+1];
			
			for(int k=0;k<=Next;k++)
			{
				cout<<"Weight : "<<Weights[i][j][k]<<"\n";
			}
		}
	}
	
	cout<<"\n**********Network**************\n\n";
	
	for(int j=0;j<=NumInputs;j++)
		{
			cout<<"Inputs : "<<j+1<<" "<<Network[0][j]<<"\n";
		}
		
			
	cout<<"\n";
		
	for(int i=0;i<=NumHiddenLayers-1;i++)
	{
		
		Next = HiddenNeuronsInEachLayer[i];
		cout<<"Hidden Layer : "<<i+1<<" "<<"Neurons In Layer ( +1 bias Neuron ) "<<Next<<"\n\n";
		for(int j=0;j<=Next;j++)
		{
			cout<<" Neurons : "<<j+1<<" : "<<Network[i+1][j]<<"\n";
		}
		cout<<"\n";
	}
	
	for(int i=0;i<=NumOutputs-1;i++)
	{
		cout<<"Calculated Output : "<<i+1<<" "<<Network[NumHiddenLayers + 2][i]<<"\n";
	}
			
}

/*
Copy Input ( User Inputted ) Copies Input Into Class Neural Network array Input for processing
*/

void NeuralNetwork::ReadInput(double Input[MAX_INPUT])
{
	for(int i=0;i<=NumInputs-1;i++)
	{
		Inputs[i] = Input[i];
	}
}

/*
Copy Output(User Expected)
Copies Output Into Class Neural Network array RealOutput for checking
*/

void NeuralNetwork::ReadOutput(double Outputs[MAX_OUTPUT])
{
	for(int i=0;i<=NumOutputs;i++)
	{
		RealOutput[i] = Outputs[i];
	}
}

/*

SIGMOID FUNCTION : ACTIVATION FUNCTION : SIGMOID 1/(1 + e^(x))

It collapses the output in range [ -0.5 , 0.5 ] 

*/

double NeuralNetwork::SIGMOID(double x)
{
	return (1/(1+exp(-x)));
}

void NeuralNetwork::InitWeights()
{

int TotalLayers = NumHiddenLayers+2;
int Next=0;

for(int i=0;i<=TotalLayers-2;i++)
	{
		for(int j=0;j<=NeuronsInEachLayer[i];j++)
		{
			Next = NeuronsInEachLayer[i+1];
			
			for(int k=0;k<=Next;k++)
			{
				Weights[i][j][k] = R();
			}
		}
	}
}

/*
Calculate Weighted Sum 
y = x1*w1 + x2*w2 + x3*w3 + ...... + xn*wn;
*/

void NeuralNetwork::CalcWS()
{
	int TotalLayers = NumHiddenLayers + 2;
	int Next = 0;
	
	double WeightedSum = 0;
	
	for(int i=0;i<=TotalLayers-1;i++)
	{
		for(int j=0;j<=NeuronsInEachLayer[i];j++)
		{
			Next = NeuronsInEachLayer[i+1];
			
			for(int k=0;k<=Next;k++)
			{
			WeightedSum += Weights[i][k][j]*Network[i][k]; 	
			}
			  
               Network[i+1][j] = SIGMOID(WeightedSum); 	
			   cout<<"\n Weighted Sum : "<<Network[i+1][j]<<"\n";
		}
	}
}


/*

Uses Gradient Descent Method to calculate the error and then back propagates it to update weight values

*/

void NeuralNetwork::UpdateWeights()
{
	int TotalLayers = NumHiddenLayers + 2;
	int Next = 0;
	
	for(int i=0;i<=TotalLayers-1;i++)
	{
		for(int j=0;j<=NeuronsInEachLayer[i];j++)
		{
			Next = NeuronsInEachLayer[i+1];
			for(int k=0;k<=Next-1;k++)
			{
				Weights[i][j][k] -= -2*(ALPHA)*(RealOutput[k] - Output[k])*SIGMOID(Output[k])*( 1 - SIGMOID(Output[k]))*Network[i][k];
				cout<<"\n Updated Weight : "<<Weights[i][j][k]<<"\n";
			}
		}
	}
}

bool NeuralNetwork::CheckOutput(double x1 , double x2)
{
	bool err;
	
	err = fabs(x1 - x2) < numeric_limits<double>::epsilon();
    
    return (err);
}

/*

Function To Implement Back-Propagation Algorithm
To train the network :-


-------------------------------------------------------------------------
|INPUT LAYER      |    HIDDEN LAYER         |    OUTPUT LAYER           |
|---------------- |------------------------ |---------------------------| 
|                 |                         |                           |  
|     (N1,W1)     |     (N1,W1)..(N1,W1)    |                           | 
|     (N2,W2)     |     (N2,W2)..(N2,W2)    |     OUTPUT                | 
|     (N3,W3)     |      .............      |                           |
|     ......      |       ............      |                           |
|     ......      |      (N,W)..(N,W)       |                           |
|                 |                         |                           |
|_____(N,W)_______|_________________________|___________________________|

OUTPUT = SIGMOID(N1*W1 + N2*W2 + .. + Nn*Wn) 

Calculates error in the Weights from gradient descendant method  
if desired output && desired error has been reached it stops updating the Weights and conclude that the Network has been trained much
                
*/

void NeuralNetwork::BackProp(double ErrorPercentage)
{
	InitWeights();
	InitNetwork();
	CalcWS();
	
	int i=0;
	int itera = 0;
	
	bool EP=false;
	
  while(i<=NumOutputs-1)
	{
	
	   while(!(EP))
	   {
		
		EP = CheckOutput(Network[NumHiddenLayers + 2][i] , RealOutput[i]);		
			cout<<"****************************Iteration :: ****************** "<<itera<<"\n";
			
			CalcWS();
			UpdateWeights();
			
		cout<<"\n Current Output No :: "<<i<<"\n"; 
		cout<<"\n Current Output :: "<<Network[NumHiddenLayers+2][i]<<"\n";
		cout<<"\n Real Output ::  "<<RealOutput[i]<<"\n";
		cout<<"\n Error Percentage :: "<<EP<<" %"<<"\n";
       
		itera++;
		
		}
	
	  i++;   
	 }

}

void NeuralNetwork::LoadTestData(char FileName[MAX_NAME])
{
	FileIO LoadTestData;
	
	LoadTestData.OpenNeuralNetwork(FileName , _TEST_);
}

void NeuralNetwork::SaveWeights(double Weight[LAYERS][TOTAL_NEURONS][TOTAL_NEURONS])
{
int TotalLayers = NumHiddenLayers+2;
int Next=0;

for(int i=0;i<=TotalLayers-2;i++)
	{
		for(int j=0;j<=NeuronsInEachLayer[i];j++)
		{
			Next = NeuronsInEachLayer[i+1];
			
			for(int k=0;k<=Next;k++)
			{
				Weight[i][j][k] = Weight[i][j][k];
			}
		}
	}	
}

void NeuralNetwork::LoadWeights(double Weight[LAYERS][TOTAL_NEURONS][TOTAL_NEURONS])
{
int TotalLayers = NumHiddenLayers+2;
int Next=0;

for(int i=0;i<=TotalLayers-2;i++)
	{
		for(int j=0;j<=NeuronsInEachLayer[i];j++)
		{
			Next = NeuronsInEachLayer[i+1];
			
			for(int k=0;k<=Next;k++)
			{
				Weights[i][j][k] = Weight[i][j][k];
			}
		}
	}	
}

void NeuralNetwork::LoadNeuronsInEachLayer(int NeuronsInLayer[TOTAL_NEURONS])
{
int TotalLayers = NumHiddenLayers + 2;

for(int i=0;i<=TotalLayers;i++)
{
	NeuronsInLayer[i] = NeuronsInEachLayer[i];
}

}

