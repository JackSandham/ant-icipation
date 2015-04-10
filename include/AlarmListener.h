/**
An interface that provides the necessary functions for receiving Alarm events.

@author Nathan
*/

#ifndef ALARM_LISTENER_H
#define ALARM_LISTENER_H

#include "AlarmEvent.h"

class AlarmListener
{
	public:
		virtual void alarmExpired(AlarmEvent* e) = 0;

	protected:
	private:
};

#endif