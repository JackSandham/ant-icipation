#include "AlarmEvent.h"

AlarmEvent::AlarmEvent(long iExpireTime, Alarm& a)
{
	m_iExpireTime = iExpireTime;
	m_sName = a.getName();
	m_iDuration = a.getDuration();
	m_iExpireCount = a.getExpireCount();
}

long AlarmEvent::getExpireTime() const
{
	return m_iExpireTime;
}

long AlarmEvent::getDuration() const
{
	return m_iDuration;
}

std::string AlarmEvent::getName() const
{
	return m_sName;
}

int AlarmEvent::getExpireCount() const
{
	return m_iExpireCount;
}