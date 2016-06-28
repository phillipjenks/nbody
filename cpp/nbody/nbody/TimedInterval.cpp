#include "stdafx.h"
#include "TimedInterval.h"

#include "TimeProfiler.h"

TimedInterval::TimedInterval(const std::string& name)
	: name(name)
{
	TimeProfiler::GetProfiler().startInterval(name);
}


TimedInterval::~TimedInterval() {

	TimeProfiler::GetProfiler().stopInterval(name);
}
