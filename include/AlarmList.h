/**
An AlarmList is a globally accessible container for storing and managing Alarms.

@see Alarm.h
@see AlarmListener.h
@author Nathan
*/

#ifndef ALARM_LIST_H
#define ALARM_LIST_H

#include <string>
#include <vector>
#include <thread>
#include <ctime>

#include "Alarm.h"
#include "AlarmEvent.h"
#include "AlarmListener.h"
#include "AlarmUtils.h"

class AlarmList
{
	public:
		static AlarmList* getAlarmList();
		void addAlarm(Alarm& a);
		bool removeAlarm(Alarm& a);
		void clearAlarms();
		bool alarmExists(std::string sName);
		Alarm* getAlarm(std::string sName);

		void addAlarmListener(AlarmListener* al);
		bool removeAlarmListener(AlarmListener* al);
		void clearAlarmListeners();

		void pauseAllAlarms();
		void resumeAllAlarms();
		void setCheckFrequency(int iFrequency);

	protected:

	private:		
		AlarmList();
		~AlarmList();

		void run();
		void checkAlarms(long iTimeNow);
		void launchEventAlarmExpired(long iTimeNow, Alarm& a);

		static AlarmList* m_instance;
		static bool m_bInstanceExists;
		long m_iCheckInterval;
		long m_iTimeNow;
		long m_iLastCheck;	

		std::vector<std::vector<Alarm>::iterator> m_removals;
		std::vector<AlarmListener*> m_alarmListeners;
		std::vector<Alarm> m_alarms;
		std::thread* m_thread;
};

#endif