
#ifndef __TIMED_INTERVAL_H_
#define __TIMED_INTERVAL_H_

#include <string>

#define TIMED_INTERVAL(x) TimedInterval _profiler_interval((x));

class TimedInterval
{
public:
	TimedInterval(const std::string&);
	~TimedInterval();

private:

	std::string name;
};

#endif

