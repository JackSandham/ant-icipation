#ifndef GAMETILES_H
#define GAMETILES_H

#include <SFML\Graphics.hpp>
#include "Vector2D.h"

class GameTiles : public sf::Drawable {
protected:
	Vector2D Position;
	Vector2D Size;
	sf::Color sColour;
public:
	GameTiles();
	GameTiles(float fxPos, float fyPos, float fxSize, float fySize, sf::Color sColor);
	float getXPos();
	float getYPos();
	float getXSize();
	float getYSize();
	sf::Color getColour();
	void draw(sf::RenderTarget &,sf::RenderStates) const;
	void setColour(sf::Color sColor);
};

#endif