#ifndef WALL_H
#define WALL_H

#include <SFML\Graphics.hpp>

#include "TextureManager.h"
#include "AABB.h"

class Wall : public AABB, public sf::Drawable
{
	public:
		Wall();
		Wall(Vector2D vPosition, float fWidth, float fHeight);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:

	private:
		float m_fX;
		float m_fY;
		float m_fWidth;
		float m_fHeight;
		sf::Sprite m_sprite;
};

#endif