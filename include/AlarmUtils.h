/**
Contains utility functions and definitions for the Alarms module.

@author Nathan
*/

#ifndef ALARM_UTILS_H
#define ALARM_UTILS_H

#include <ctime>
#include <chrono>

class AlarmUtils
{
	public:
		static long getSystemTimeMillis();

		static const long SECONDS_IN_MINUTE = 60l;
		static const long SECONDS_IN_HOUR = 3600l;
		static const long SECONDS_IN_DAY = 86400l;
		static const long SECONDS_IN_WEEK = 604800l;
		static const long SECONDS_IN_YEAR = 31556952l;

		static const long MILLIS_IN_SECOND = 1000l;
		static const long MILLIS_IN_MINUTE = 60000l;
		static const long MILLIS_IN_HOUR = 3600000l;
		static const long MILLIS_IN_DAY = 86400000l;
		static const long MILLIS_IN_WEEK = 604800000l;
		static const long MILLIS_IN_YEAR = 31556952000l;

	protected:

	private:
		AlarmUtils();

};

#endif