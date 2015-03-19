#include "Background.h"

Background::Background(){
	for(int i = 0; i < ksiNumTiles; i++){
		tiles[i]= GameTiles(Position.getX(), Position.getY(), Size.getX(), Size.getY(), sColour);
		if(Position.getX() < 980){
			Position.setX(Position.getX() + 20);
			}
		else{
			Position.setX(1);
			Position.setY(Position.getY() + 20);
		}
	}
}

void Background::drawBackground(sf::RenderTarget & window) const{
	for(int i = 0; i < ksiNumTiles; i++){
		window.draw(tiles[i]);
	}
}

void Background::setColour(sf::Color sColor, int iTile){
	tiles[iTile].setColour(sColor);
}
