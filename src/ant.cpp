#include "ant.h"


Ant::Ant()
{

}
void Ant::Update()
{
	setMin();
	setMax();
	m_fBottom = Rectangle.getPosition().y + Rectangle.getSize().y;
	m_fLeft = Rectangle.getPosition().x;
	m_fRight = Rectangle.getPosition().x + Rectangle.getSize().x;
	m_fTop = Rectangle.getPosition().y;

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