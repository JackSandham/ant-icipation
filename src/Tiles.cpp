#include "Tiles.h"

Tiles::Tiles(){
	position = Vector2D(0,0);
	size = Vector2D(0,0);
	sColour = sf::Color::Blue;
}

Tiles::Tiles(Vector2D pos, Vector2D size1, sf::Color sColor){
	position = pos;
	size = size1;
	sColour = sColor;
}

float Tiles::getXPos(){
	return position.getX();
}

float Tiles::getYPos(){
	return position.getY();
}

Vector2D Tiles::getPos(){
	return position;
}

float Tiles::getXSize(){
	return size.getX();
}

float Tiles::getYSize(){
	return size.getY();
}

Vector2D Tiles::getSize(){
	return size;
}

sf::Color Tiles::getColour(){
	return sColour;
}

void Tiles::setXPos(float xPos){
	position.setX(xPos);
}

void Tiles::setYPos(float yPos){
	position.setY(yPos);
}

void Tiles::setPos(Vector2D pos){
	position = pos;
}

void Tiles::setXSize(float xSize){
	size.setX(xSize);
}

void Tiles::setYSize(float ySize){
	size.setY(ySize);
}

void Tiles::setSize(Vector2D size1){
	size = size1;
}

void Tiles::setColour(sf::Color sColor){
	sColour = sColor;
}


void Tiles::draw(sf::RenderTarget &window,sf::RenderStates states)const {
	sf::RectangleShape rect;
	rect.setPosition(position.getX(), position.getY());
	rect.setSize(sf::Vector2f(size.getX(), size.getY()));
	rect.setFillColor(sColour);

	window.draw(rect);
}