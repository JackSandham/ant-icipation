#include "MatrixController.h"

MatrixController::MatrixController(){
	tempPos.setValues(0, 0);
	bTempBool = false;
}

void MatrixController::setAntPosInMatrix(Ant* ant, char(&charArray)[GRIDX][GRIDY]){
	if (bTempBool == true){
		charArray[(int)tempPos.getX()][(int)tempPos.getY()] = '.';
		bTempBool = false;
	}
	float xPos = ant->getPosition().getX();
	float yPos = ant->getPosition().getY();
	xPos = xPos / 1000;
	yPos = yPos / 1000;
	xPos = xPos * 50;
	yPos = yPos * 50;
	xPos = (int)xPos;
	yPos = (int)yPos;
	charArray[(int)yPos][(int)xPos] = 'a';
	tempPos = Vector2D(yPos, xPos);
	bTempBool = true;
}

void MatrixController::constructMatrix(char(&arrayMatrix)[GRIDX][GRIDY]){
	grid.open("../Maps/Map1.txt", ios_base::in);
	if(grid.is_open()){
		for (int i = 0; i < GRIDX; i++){
			for (int j = 0; j < GRIDY; j++){
					grid>>arrayMatrix[i][j];
				}
			}
		grid.close();
	}
	else{
		cout<<"error";
	}
}

void MatrixController::presetMatrix(char(&arrayMatrix)[GRIDX][GRIDY]){
	for (int i = 0; i < GRIDX; i++){
		for (int j = 0; j < GRIDY; j++){
			arrayMatrix[i][j] = '.';
		}
	}
}