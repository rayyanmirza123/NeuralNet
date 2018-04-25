#include "FileIO.h"

FileIO::FileIO()
{
}

void FileIO::OpenNeuralNetwork(char FileName[MAX_NAME] , int Mode)
{
	fstream fin;
    NeuralNetwork Network;
    
    int Layers = NumHiddenLayers + 2;
    
    switch(Mode)
    {
    	case _TEST_:
    		
			fin.open(FileName , ios::in);
    		fin>>Inputs;
    		
    		for(int i=0;i<=Inputs;i++)
    		{
    			fin>>NumInputs>>NumOutputs;
    			for(int j=0;j<=NumInputs-1;j++)
    			{
    				fin>>Inp[j];
				}
				Network.ReadInput(Inp);
				
				for(int k=0;k<=NumOutputs-1;k++)
				{
					fin>>Out[k];
				}				
				Network.ReadOutput(Out);
				Network.InitNetwork();
				
			}
			fin.close();
    		break;
    	
		case _NEW_:
    		
    		fin.open(FileName , ios::out);
    		
    		fin<<NumInputs<<"\n";
    		fin<<NumHiddenLayers<<"\n";
    		fin<<NumOutputs<<"\n";
    		
    		Network.SaveWeights(Weight);
    		
    		
    		for(int i=0;i<=Layers-1;i++)
    		{
    			for(int j=0;j<=NeuronsInEachLayer[i];i++)
    			{
    				for(int k=0;k<=NeuronsInEachLayer[j+1];k++)
    				{
    					fin<<Weight[i][j][k]<<"\n";
					}
				}
			}
    		
    		fin.close();
    		break;
    	
		case _EXIST_:
    		
    		fin.open(FileName , ios::in);
    		
    		fin>>NumInputs;
    		fin>>NumHiddenLayers;
    		fin>>NumOutputs;
    		
    			for(int i=0;i<=Layers-1;i++)
    		{
    			for(int j=0;j<=NeuronsInEachLayer[i];i++)
    			{
    				for(int k=0;k<=NeuronsInEachLayer[j+1];k++)
    				{
    					fin>>Weight[i][j][k];
					}
				}
			}
    		
			Network.LoadWeights(Weight);
    		break;
    	
		default:
    		
			break;
	}
	
}

void FileIO::CreateInputFile(char FileName[MAX_NAME] , int Type)
{
	fstream fin;
	
	switch(Type)
	{
		case ADD_TEST:
			
			fin.open(FileName , ios::out);
			
			fin<<49<<"\n";
			for(int i=0;i<=199;i++)
			{
				fin<<2<<1<<"\n";
				fin<<i<<"\n";
				fin<<i+1<<"\n";
			}
			
			for(int i=0;i<=49;i++)
			{
				fin<<i+i+1<<"\n";
			}
			fin.close();
			break;
		case MUL_TEST:
			break;
		case DIV_TEST:
			break;
		default:
			break;
	}
}
