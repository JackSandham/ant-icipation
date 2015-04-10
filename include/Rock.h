#ifndef ROCK_H
#define ROCK_H

#include <SFML\Graphics.hpp>

#include "TextureManager.h"
#include "AABB.h"

class Rock : public AABB, public sf::Drawable
{
	public:
		Rock();
		Rock(Vector2D vPosition, float fWidth, float fHeight);

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