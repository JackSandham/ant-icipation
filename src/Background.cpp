#include "Background.h"

Background::Background(){
	for(int i = 0; i < ksiNumTiles; i++){
		tiles[i]= Tiles(Position.getX(), Position.getY(), Size.getX(), Size.getY(), sColour);
		if(Position.getX() < 980){
			Position.setX(Position.getX() + 20);
			}
		else{
			Position.setX(1);
			Position.setY(Position.getY() + 20);
		}
	}
	bMapped = false;
}

void Background::drawBackground(sf::RenderTarget & window) const{
	for(int i = 0; i < ksiNumTiles; i++){
		window.draw(tiles[i]);
	}
}

void Background::setColour(sf::Color sColor, int iTile){
	tiles[iTile].setColour(sColor);
}

void Background::assignMatrixValues(char(&charArray)[GRIDX][GRIDY]){
	if (bMapped == false){
		int k = 0;
		for (int i = 0; i < GRIDX; i++){
			for (int j = 0; j < GRIDY; j++){
				switch (charArray[i][j]){
				case '.':
					setColour(sf::Color::White, k); //Free Space
					break;
				case '1':
					AABB* Obstacle = new AABB(Vector2D(20*j+10,20*i+10),20,20,sf::Color::Blue);
					m_vectorOfAABB.push_back(Obstacle);
				}
				k++;
			}
			bMapped = true;
		}
	}
}

std::vector<AABB*> Background::getObstacles()
{
	return m_vectorOfAABB;
}