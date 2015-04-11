#ifndef ANT_HILL_H
#define ANT_HILL_H

#include <SFML\Graphics.hpp>

#include "TextureManager.h"
#include "AABB.h"

class AntHill : public AABB, public sf::Drawable
{
	public:
		AntHill();
		AntHill(Vector2D vPosition, float fWidth, float fHeight);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:

	private:
		float m_fX;
		float m_fY;
		float m_fWidth;
		float m_fHeight;
		float m_fMax;
		float m_fMin;
		sf::Sprite m_sprite;
};

#endif