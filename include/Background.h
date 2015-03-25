/**
A class to draw the background of the program

This class includes the code that is used to initialise, draw and change the background of the program.

This class will be changed into a singleton as only one state of a Background is required for the program.

@author Gethin
*/

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Tiles.h"
#include "AABB.h"
#include <SFML\Graphics.hpp>

class Background : Tiles{
private:
	static const int ksiNumTiles = GRIDX * GRIDY;
	Tiles tiles[ksiNumTiles];
	bool bMapped;
	std::vector<AABB*> m_vectorOfAABB;
public:
	Background(); //This is the default constructor for the Background class.
	void drawBackground(sf::RenderTarget & window /*This is the target that the program will be drawn onto.*/) const; //This function is used to draw the background of the program onto the screen.
	void setColour(sf::Color sColor /*This is the colour that the tile is going to be set to.*/, int iTile/*This is the number of the tile that will have its colour modified.*/); //This function is used to set the colour of one of the tiles in the background.
	void assignMatrixValues(char(&charArray)[GRIDX][GRIDY]/*This is the matrix that will be used to set the colour of the tiles in the background.*/); //This function is used to assign the values of the matrix to the background to draw the correct tiles.
	std::vector<AABB*> getObstacles();
};

#endif