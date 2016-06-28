/*

	Singleton class for managing time profiling of the simulation

*/


#ifndef __TIME_PROFILER_H_
#define __TIME_PROFILER_H_

#include <map>
#include <string>
#include <time.h>

#define START_TIMED_INTERVAL(x) TimeProfiler::GetProfiler().startInterval((x));
#define STOP_TIMED_INTERVAL(x) TimeProfiler::GetProfiler().stopInterval((x));

namespace {
	struct ProfileData {
		unsigned int m_totalTrials = 0;
		double m_totalTime = 0;
	};
}

class TimeProfiler
{

	using ProfileMap = std::map<std::string, ProfileData>;
	using IntervalMap = std::map<std::string, clock_t>;

public:

	// Static method to get the time profiler singleton
	static TimeProfiler& GetProfiler();

	~TimeProfiler() = default;

	TimeProfiler(const TimeProfiler&) = delete;
	TimeProfiler& operator=(const TimeProfiler&) = delete;

	TimeProfiler(TimeProfiler&&) = delete;
	TimeProfiler& operator=(TimeProfiler&&) = delete;

	// Add a timed trial for a profile name
	void addProfile(const std::string& profileName, double time);

	// Start a timing interval for a profile name
	void startInterval(const std::string&);

	// Stop a timing interval for a profile name
	void stopInterval(const std::string&);

	void dumpProfile();

private:

	TimeProfiler() = default;

	// Stop all running intervals
	void clearIntervals();

	ProfileMap profiles;
	IntervalMap intervals;
};

#endif