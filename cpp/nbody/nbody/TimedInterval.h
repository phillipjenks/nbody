
/*

	Utility class for creating a timed interval

*/

#ifndef __TIMED_INTERVAL_H_
#define __TIMED_INTERVAL_H_

#include <string>

#define TIMED_INTERVAL(x) TimedInterval _profiler_interval((x));

class TimedInterval
{
public:

	// Constructor will use the time profiler singleton to start a timed interval
	TimedInterval(const std::string&);

	// Destructor will use the time profiler singleton to stop a timed interval
	~TimedInterval();

private:

	std::string name;
};

#endif

