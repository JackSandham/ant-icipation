/**
A class to control the matrix and its values.

This class includes the code that is used to construct and set the values of the matrix.

This class will be changed into a singleton as only one state of a Matrix Controller is required for the program.

@author Gethin
*/

#ifndef MATRIXCONTROLLER
#define MATRIXCONTROLLER

#define GRIDX 50
#define GRIDY 50

#include "Vector2D.h" //Boo
#include "ant.h"
#include <fstream>

class MatrixController
{
private:
	fstream grid;
	Vector2D tempPos;
	bool bTempBool;
public:
	MatrixController(); //This is the deafult constructor for a Matrix Controller
	void setAntPosInMatrix(Ant* ant /*This is the ant that is going to be placed into the matrix*/, char(&charArray)[GRIDX][GRIDY] /*This is the matrix which the information of the ant is going to be placed.*/); //This function is used to set the position of the ant passed in the parameters into the matrix.
	void constructMatrix(char (&arrayMatrix)[GRIDX][GRIDY]/*This is the matrix that will have the information from the text document placed into it.*/); //This function is used to create the matrix using a text file.
	void presetMatrix(char(&arrayMatrix)[GRIDX][GRIDY]/*This is the matrix that will be initialized*/); //This function is used to initially set the values of the matrix. In this case the matrix is being set to '.'.
};

#endif