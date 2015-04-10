/**
A class to create visual tiles.

This class includes the code that is used to create and modify tiles.

Each tile has its own unique position, size and colour. The colour can be changed individually.

@author Gethin
*/

#ifndef TILES_H
#define TILES_H

#define GRIDX 45 //--Gethin Changes
#define GRIDY 35 //--Gethin Changes
//I have made these variables so that it keeps the size of the grid consistent.
//Unfortunatly I cant access the same variables as the ones set in the Adjacency Matrix

#include <SFML\Graphics.hpp>
#include "Vector2D.h"

class Tiles : public sf::Drawable {
protected:
	Vector2D Position;
	Vector2D Size;
	sf::Color sColour;
public:
	Tiles(); //This is the default constructor for a Tile
	Tiles(float fxPos /*This is used to set the x position of the tile.*/, float fyPos/*This is used to set the y position of the tile.*/, float fxSize/*This is used to set the x size of the tile.*/, float fySize/*This is used to set the y size of the tile.*/, sf::Color sColor/*This is used to set the colour of the tile.*/); //This is a constructor for a Tile which takes in a position, size and colour in the parameters.
	float getXPos(); //This function is used to get the X position of the tile.
	float getYPos(); //This function is used to get the Y position of the tile.
	float getXSize(); //This function is used to get the X size of the tile.
	float getYSize(); //This function is used to get the Y size of the tile.
	sf::Color getColour(); //This function is used to get the colour of the tile.
	void draw(sf::RenderTarget & /*This is the target that the tiles will be drawn onto.*/,sf::RenderStates /*The current render states*/) const; //This function is used to draw the tile onto the screen.
	void setColour(sf::Color sColor/*This is the colour that the tile will be set to.*/); //This function is used to set the colour of the tile.
};

#endif