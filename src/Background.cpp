#include "Background.h"

Background::Background()
{
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

void Background::drawBackground(sf::RenderTarget & window) const
{
	for(int i = 0; i < ksiNumTiles; i++){
		window.draw(tiles[i]);
	}
}

void Background::setColour(sf::Color sColor, int iTile)
{
	tiles[iTile].setColour(sColor);
}

void Background::assignMatrixValues(char(&charArray)[GRIDX][GRIDY], std::vector<Rock>& rocks, std::vector<Wall>& walls)
{
	if (bMapped == false)
	{
		int k = 0;
		int l = 0;
		for (int i = 0; i < GRIDX; i++)
		{
			for (int j = 0; j < GRIDY; j++)
			{
				switch (charArray[i][j])
				{
				case '.':
					{
						setColour(sf::Color::White, k); //Free Space
						break;	
					}
				case '1':
					{
						Wall wall(Vector2D(20 * j + 10, 20 * i + 10), 20, 20);
						walls.push_back(wall);
						break;
					}
				case '2':
					{
						// This is now redundant due to food automatically spawning over time (And also does not work). It would ideally 
					    // be replaced with another type of obstacle, such as a bush.
						Food* food = new Food(Vector2D(20*j+10,20*i+10), 20, 20);
						food->setFoodNumber(l+1);
						l++;
						m_vectorOfFood.push_back(food);
						break;
					}	
				case '3':
					{
						Rock rock(Vector2D(20 * j + 10, 20 * i + 10), 20, 20);
						rocks.push_back(rock);
						break;
					}
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

std::vector<Food*> Background::getFood()
{
	return m_vectorOfFood;
}