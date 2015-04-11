#include "AntHill.h"

AntHill::AntHill()
{
	m_fX = 0;
	m_fY = 0;
	m_fWidth = 50;
	m_fHeight = 50;
}

AntHill::AntHill(Vector2D vPosition, float fWidth, float fHeight) : AABB(vPosition,  fWidth,  fHeight)
{
	m_fX = vPosition.getX();
	m_fY = vPosition.getY();
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	
	TextureManager* tm = TextureManager::getInstance();
	m_sprite.setTexture(*tm->getTexture("ant_hill"));
	m_sprite.setScale(fWidth / tm->getTexture("ant_hill")->getSize().x, fHeight / tm->getTexture("ant_hill")->getSize().y);
	m_sprite.setPosition(vPosition.getX() + 300, vPosition.getY() + 100);
	m_sprite.setOrigin((fWidth / 2) / m_sprite.getScale().x, (fHeight / 2) / m_sprite.getScale().y);
}

void AntHill::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}