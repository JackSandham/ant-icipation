#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace std;


class Ant
{
public:
	sf::RectangleShape rect;
	float bottom, left, right, top;
	

	Ant(sf::Vector2f position, sf::Vector2f size, sf::Color color)
	{
		rect.setPosition(position);
		rect.setSize(size);
		rect.setFillColor(color);
	}

	void Update()
	{
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
		top = rect.getPosition().y;
	}

	bool Collision(Ant ant)
	{
		if(right < ant.left || left > ant.right ||
			top > ant.bottom || bottom < ant.top)
		{
			return false;
		}
		return true;
	}

//Ryan Wilson 23/02/15 ant-icipation







};




