#ifndef SHAPE_H
#define SHAPE_H

#include <SFML\Graphics.hpp>

class Shape : public sf::Drawable
{
	public:
		Shape();

		void setPosition(sf::Vector2f pos);
		void setColor(sf::Color passedColor);

		sf::Vector2f getPosition();
		sf::Color getColor();

	protected:
		sf::Vector2f m_vPosition;
		sf::Vector2f m_vOrigin;
		sf::Color m_Color;

	private:

};

#endif