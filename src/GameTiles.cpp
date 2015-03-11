#include "GameTiles.h"

GameTiles::GameTiles(){
	Position.setValues(1,1);
	Size.setValues(18,18);
	sColour = sf::Color::White;
}

GameTiles::GameTiles(float fxPos, float fyPos, float fxSize, float fySize, sf::Color sColor){
	Position.setValues(fxPos, fyPos);
	Size.setValues(fxSize, fySize);
	sColour = sColor;
}

float GameTiles::getXPos(){
	return Position.getX();
}

float GameTiles::getYPos(){
	return Position.getY();
}

float GameTiles::getXSize(){
	return Size.getX();
}

float GameTiles::getYSize(){
	return Size.getY();
}

sf::Color GameTiles::getColour(){
	return sColour;
}

void GameTiles::setColour(sf::Color sColor){
	sColour = sColor;
}

void GameTiles::draw(sf::RenderTarget & window,sf::RenderStates states) const{
	sf::RectangleShape rect;
	rect.setPosition(Position.getX(), Position.getY());
	rect.setSize(sf::Vector2f(Size.getX(), Size.getY()));
	rect.setFillColor(sColour);

	window.draw(rect);
}
