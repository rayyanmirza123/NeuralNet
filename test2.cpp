#include "NeuralNetwork.h"

int main()
{
	int Hidden[] = {5,3,2};
	double Input[] = {0.1,0.1};
	double Output[] = {0.1};
	
	NeuralNetwork Network(2 , 3 , Hidden , 1);
	Network.ReadInput(Input);
	Network.ReadOutput(Output);
	
	Network.InitNetwork();
	Network.BackProp(0.01);
	
	Network.DEBUG();
	
    
	return 0;
	
}
