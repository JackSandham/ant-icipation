#include "ant.h"

Ant::Ant()
{

}

void Ant::Update()
{
	setMin();
	setMax();
	m_fBottom = rectangle.getPosition().y + rectangle.getSize().y;
	m_fLeft = rectangle.getPosition().x;
	m_fRight = rectangle.getPosition().x + rectangle.getSize().x;
	m_fTop = rectangle.getPosition().y;
}

bool Ant::Collision(Ant ant)
{
	if(m_fRight < ant.m_fLeft || m_fLeft > ant.m_fRight ||
		m_fTop > ant.m_fBottom || m_fBottom < ant.m_fTop)
	{
		return false;
	}
	return true;
}