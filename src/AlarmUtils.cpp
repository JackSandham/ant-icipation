#include "AlarmUtils.h"

AlarmUtils::AlarmUtils()
{
}

long AlarmUtils::getSystemTimeMillis()
{
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
	return ms.count();
}