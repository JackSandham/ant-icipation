#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "GameTiles.h"
#include <SFML\Graphics.hpp>

class Background : GameTiles{
private:
	static const int ksiNumTiles = 2500;
	GameTiles tiles[ksiNumTiles];
public:
	Background();
	void drawBackground(sf::RenderTarget & window) const;
	void setColour(sf::Color sColor, int iTile);
	void setValuesNull();
};

#endif