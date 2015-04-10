#include "AlarmList.h"

AlarmList* AlarmList::m_instance;
bool AlarmList::m_bInstanceExists;

AlarmList::AlarmList()
{
	setCheckFrequency(100);
	m_bInstanceExists = true;

	m_thread = new std::thread(&AlarmList::run, this);
}

AlarmList::~AlarmList()
{
	delete m_thread;
	m_bInstanceExists = false;
}

AlarmList* AlarmList::getAlarmList()
{
	if (m_bInstanceExists)
	{
		return m_instance;
	}
	else
	{
		m_instance = new AlarmList();
		return m_instance;
	}
}

void AlarmList::addAlarm(Alarm& a)
{
	a.restart();
	m_alarms.push_back(a);
}

bool AlarmList::removeAlarm(Alarm& a)
{
	for (std::vector<Alarm>::iterator it = m_alarms.begin(); it != m_alarms.end(); ++it)
	{
		if (*it == a)
		{
			m_alarms.erase(it);
			return true;
		}
	}
	return false;
}

void AlarmList::clearAlarms()
{
	m_alarms.clear();
}

bool AlarmList::alarmExists(std::string sName)
{
	for (std::vector<Alarm>::iterator it = m_alarms.begin(); it != m_alarms.end(); ++it)
	{
		if (*it == sName)
		{
			return true;
		}
	}
	return false;
}

Alarm* AlarmList::getAlarm(std::string sName)
{
	for (std::vector<Alarm>::iterator it = m_alarms.begin(); it != m_alarms.end(); ++it)
	{
		if (*it == sName)
		{
			return &(*it);
		}
	}
	return nullptr;
}

void AlarmList::addAlarmListener(AlarmListener* al)
{
	m_alarmListeners.push_back(al);
}

bool AlarmList::removeAlarmListener(AlarmListener* al)
{
	for (std::vector<AlarmListener*>::iterator it = m_alarmListeners.begin(); it != m_alarmListeners.end(); ++it)
	{
		if (*it == al)
		{
			m_alarmListeners.erase(it);
			return true;
		}
	}
	return false;
}

void AlarmList::clearAlarmListeners()
{
	m_alarmListeners.clear();
}

void AlarmList::pauseAllAlarms()
{
	for (std::vector<Alarm>::iterator it = m_alarms.begin(); it != m_alarms.end(); ++it)
	{
		it->pause();
	}
}

void AlarmList::resumeAllAlarms()
{
	for (std::vector<Alarm>::iterator it = m_alarms.begin(); it != m_alarms.end(); ++it)
	{
		it->resume();
	}
}

void AlarmList::setCheckFrequency(int iFrequency)
{
	if (iFrequency < 1)
	{
		return;
	}
	m_iCheckInterval = 1000 / iFrequency;
}	

void AlarmList::run()
{
	m_iTimeNow = AlarmUtils::getSystemTimeMillis();
	m_iLastCheck = m_iTimeNow;
	
	while (m_bInstanceExists)
	{
		if (m_iTimeNow > (m_iLastCheck + m_iCheckInterval))
		{
			checkAlarms(m_iTimeNow);
			m_iLastCheck = m_iTimeNow;
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			m_iTimeNow = AlarmUtils::getSystemTimeMillis();
		}
	}
}

void AlarmList::checkAlarms(long iTimeNow)
{
	for (std::vector<Alarm>::iterator it = m_alarms.begin(); it != m_alarms.end(); ++it)
	{
		if (it->hasExpired(iTimeNow))
		{
			launchEventAlarmExpired(iTimeNow, *it);
			if (it->getAutoRestart() == true)
			{
				it->restart();
			}
			else
			{
				m_removals.push_back(it);
			}
		} 
	}

	// Avoiding invalidating the iterator above by performing removals here instead.
	for (std::vector<std::vector<Alarm>::iterator>::iterator it = m_removals.begin(); it != m_removals.end(); ++it)
	{
		m_alarms.erase(*it);
	}
	m_removals.clear();
}

void AlarmList::launchEventAlarmExpired(long iTimeNow, Alarm& a)
{
	AlarmEvent* e = new AlarmEvent(iTimeNow, a);
	for (std::vector<AlarmListener*>::iterator it = m_alarmListeners.begin(); it != m_alarmListeners.end(); ++it)
	{
		(*it)->alarmExpired(e);
	}
	delete e;
}