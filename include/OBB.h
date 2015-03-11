#ifndef OBB_H
#define OBB_H

#include "Shape.h"
#include <SFML\Graphics.hpp>

class OBB : public Shape
{
	public:
		OBB(sf::Vector2f position, float width, float height, float angle);
		
		float getHalfWidth();
		float getHalfHeight();
		float getAngle();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:

	private:
		float m_fWidth;
		float m_fHeight;
		float m_fAngle;
};

#endif