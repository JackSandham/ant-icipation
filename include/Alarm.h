/**
A simple timing object for use in conjunction with the AlarmList.

Setting the auto restart flag of the Alarm to true will cause the Alarm to restart itself every
time it expires without ever removing the Alarm from the AlarmList. This flag can be used to
guarantee the existence of an Alarm once it has been added to the AlarmList. By default, Alarms
will not automatically restart.

Alarms track the number of times that they have expired. This value can be reset by calling the
reset function.

Alarms are considered equal if their names are the same.

@see AlarmListener.h
@see AlarmEvent.h
@author Nathan
*/

#ifndef ALARM_H
#define ALARM_H

#include <string>
#include <algorithm>

#include "AlarmUtils.h"

class Alarm
{
	public:
		Alarm(std::string sName, long iDuration, bool bAutoRestart);

		/**
		Sets the auto-restart flag for the Alarm. Alarms that automatically restart will call
		their own restart function upon expiring. Setting this flag to true ensures that the Alarm
		will not be removed from the AlarmList due to expiration. 
		
		@param bAutoRestart True to enable automatic restarting of the Alarm. */
		void setAutoRestart(bool bAutoRestart);
		/**
		*/
		void pause();
		/**
		*/
		void resume();
		/**
		*/
		void reset();

		/**
		*/
		void restart();
		/**
		*/
		void extendDuration(long iAmount);
		/**
		*/
		void shortenDuration(long iAmount);
		/**
		*/
		bool hasExpired(long iTimeNow);
		/**
		*/
		bool getAutoRestart() const;
		/**
		*/
		long getTimeRemaining() const;
		/**
		*/
		long getExpireCount() const;
		/**
		*/
		long getDuration() const;
		/**
		*/
		std::string getName() const;
		/**
		*/
		bool operator==(Alarm a);
		/**
		*/
		bool operator==(std::string sName);

	protected:

	private:
		long systemTimeMillis();

		std::string m_sName;
		int m_iExpireCount;
		bool m_bAutoRestart;
		bool m_bPaused;
		long m_iPauseTime;
		long m_iDuration;
		long m_iEndTime;
};

#endif