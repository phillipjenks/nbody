#include "stdafx.h"
#include "TimedInterval.h"

#include "TimeProfiler.h"

// Constructor that starts a timed interval
TimedInterval::TimedInterval(const std::string& name)
	: name(name)
{
	TimeProfiler::GetProfiler().startInterval(name);
}

// Destructor that stops a timed interval
TimedInterval::~TimedInterval() {

	TimeProfiler::GetProfiler().stopInterval(name);
}
