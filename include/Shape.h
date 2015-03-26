#ifndef SHAPE_H
#define SHAPE_H

#include <SFML\Graphics.hpp>
#include "Vector2D.h"

class Shape : public sf::Drawable
{
	public:
		Shape();

		void setPosition(Vector2D pos);
		void setColor(sf::Color passedColor);

		Vector2D getPosition();
		sf::Color getColor();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	protected:
		Vector2D m_vPosition;
		Vector2D m_vOrigin;
		sf::Color m_Color;

	private:

};

#endif