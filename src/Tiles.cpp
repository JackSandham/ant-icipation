#include "Tiles.h"

Tiles::Tiles(){
	Position.setValues(1,1);
	Size.setValues(18,18);
	sColour = sf::Color::White;
}

Tiles::Tiles(float fxPos, float fyPos, float fxSize, float fySize, sf::Color sColor){
	Position.setValues(fxPos, fyPos);
	Size.setValues(fxSize, fySize);
	sColour = sColor;
}

float Tiles::getXPos(){
	return Position.getX();
}

float Tiles::getYPos(){
	return Position.getY();
}

float Tiles::getXSize(){
	return Size.getX();
}

float Tiles::getYSize(){
	return Size.getY();
}

sf::Color Tiles::getColour(){
	return sColour;
}

void Tiles::setColour(sf::Color sColor){
	sColour = sColor;
}

void Tiles::draw(sf::RenderTarget & window,sf::RenderStates states) const{
	sf::RectangleShape rect;
	rect.setPosition(Position.getX(), Position.getY());
	rect.setSize(sf::Vector2f(Size.getX(), Size.getY()));
	rect.setFillColor(sColour);

	window.draw(rect);
}
