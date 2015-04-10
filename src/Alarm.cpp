#include "Alarm.h"

Alarm::Alarm(std::string sName, long iDuration, bool bAutoRestart)
{
	m_sName = sName;
	m_iDuration = iDuration;
	m_bAutoRestart = bAutoRestart;
	m_iExpireCount = 0;
}

void Alarm::setAutoRestart(bool bAutoRestart)
{
	m_bAutoRestart = bAutoRestart;
}

void Alarm::pause()
{
	m_bPaused = true;
	m_iPauseTime = AlarmUtils::getSystemTimeMillis();
}

void Alarm::resume()
{
	m_iEndTime += (AlarmUtils::getSystemTimeMillis() - m_iPauseTime);
	m_bPaused = false;
}

void Alarm::reset()
{
	m_iExpireCount = 0;
	restart();
}

void Alarm::restart()
{
	m_iEndTime = AlarmUtils::getSystemTimeMillis() + m_iDuration;
}

void Alarm::extendDuration(long iAmount)
{
	m_iDuration += iAmount;
}

void Alarm::shortenDuration(long iAmount)
{
	// Alarms must be at least 1 millisecond.
	if (m_iDuration - iAmount > 0)
	{		
		m_iDuration -= iAmount;
	}
}

bool Alarm::hasExpired(long iTimeNow)
{
	if (iTimeNow > m_iEndTime)
	{
		m_iExpireCount++;
		return true;
	}
	else
	{
		return false;
	}
}

bool Alarm::getAutoRestart() const
{
	return m_bAutoRestart;
}

long Alarm::getTimeRemaining() const
{
	if (m_bPaused)
	{
		return std::max(m_iEndTime - m_iPauseTime, 0l);
	}
	else
	{
		return std::max(m_iEndTime - AlarmUtils::getSystemTimeMillis(), 0l);
	}
}

long Alarm::getExpireCount() const
{
	return m_iExpireCount;
}

long Alarm::getDuration() const
{
	return m_iDuration;
}

std::string Alarm::getName() const
{
	return m_sName;
}

bool Alarm::operator==(Alarm a)
{
	return (m_sName == a.getName());
}

bool Alarm::operator==(std::string sName)
{
	return (m_sName == sName);
}