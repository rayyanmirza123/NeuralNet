# NeuralNet

It started in my junior high and now i want it to atleast behave like a neural net engine or do some stuff

any contributions ?? feel free to add them

#To train the network :-
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
