/**
A messenger object that contains information about a recent expirey event occurring on the AlarmList.

AlarmEvent properties are read-only to prevent data corruption when visting multiple AlarmListener's.

An AlarmEvent has a very short lifespan and should not be used as a way of storing data about an
event. Rather, the data should be extracted from the event object and stored in another manner. 
AlarmEvents are deleted once all AlarmListeners have received notification of the event.

@see AlarmListener.h
@author Nathan
*/

#ifndef ALARM_EVENT_H
#define ALARM_EVENT_H

#include "Alarm.h"
#include <string>

class AlarmEvent
{
	public:
		AlarmEvent(long iExpireTime, Alarm& a);

		/**
		Returns the time that the Alarm expired, in milliseconds. 

		@return The time that the Alarm expired, in milliseconds. */
		long getExpireTime() const;

		/**
		Returns the duration of the Alarm, in milliseconds. 

		@return The duration of the Alarm, in milliseconds. */
		long getDuration() const;

		/**
		Returns the name of the Alarm.
		
		@return The name of the Alarm. */
		std::string getName() const;

		/**
		Returns the number of times the Alarm has expired. 
		
		@return The number of times the Alarm has expired. */
		int getExpireCount() const;

	protected:

	private:
		AlarmEvent();

		std::string m_sName;
		long m_iDuration;
		long m_iExpireTime;
		int m_iExpireCount;
};

#endif