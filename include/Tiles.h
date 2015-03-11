#ifndef TILES_H
#define TILES_H

#include <SFML\Graphics.hpp>
#include "Vector2D.h"
#include <string>

using namespace std;

class Tiles : public sf::Drawable{
protected:
	Vector2D position;
	Vector2D size;
	sf::Color sColour;
public:
	Tiles();
	Tiles(Vector2D pos, Vector2D size1, sf::Color sColor);
	float getXPos();
	float getYPos();
	Vector2D getPos();
	float getXSize();
	float getYSize();
	Vector2D getSize();
	sf::Color getColour();
	void setXPos(float xPos);
	void setYPos(float yPos);
	void setPos(Vector2D pos);
	void setXSize(float xSize);
	void setYSize(float ySize);
	void setSize(Vector2D size1);
	void setColour(sf::Color sColor);
	void draw(sf::RenderTarget &window,sf::RenderStates states) const;
};

#endif