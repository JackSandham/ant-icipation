#include "Food.h"
#include <stdlib.h>     //for using the function sleep
#include <Windows.h>

Food::Food()
{
}



Food::Food(Vector2D passedPosition, int width, int height, sf::Color passedColor) : AABB(passedPosition,  width,  height,passedColor)
{
	foodRadius = new Circle(getPosition(), 50,sf::Color::Green);// foods detection radius
	m_bRadiusVisible = true;
	m_bCollidable =true;
	Update();
}

void Food::Update()
{
	m_fBottom = rectangle.getPosition().y + rectangle.getSize().y; //calculates the bottom edge
	m_fLeft = rectangle.getPosition().x; //calculates the left edge
	m_fRight = rectangle.getPosition().x + rectangle.getSize().x;//calculates the right edge
	m_fTop = rectangle.getPosition().y;//calculates the top edge
}

void Food::setRadiusVisibility(bool bPassedVisibility)
{
	m_bRadiusVisible = bPassedVisibility;
}



bool Food::radiusIsVisible()
{
	return m_bRadiusVisible;
}



void Food::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_bRadiusVisible)
	{
		target.draw(*foodRadius);
	}
	target.draw(rectangle);
}

Circle* Food::getFoodRadius()
{
	return foodRadius;
}

bool Food::getCollidable()
{
	return m_bCollidable;
}


	
void Food::setCollidable(bool bPassedCollidable)
{
	m_bCollidable = bPassedCollidable;
}
