#include "stdafx.h"
#include "TimeProfiler.h"
#include "SimManager.h"

#include <sstream>
#include <fstream>
#include <time.h>

// Static method for accessing the singleton
TimeProfiler& TimeProfiler::GetProfiler() {

	static TimeProfiler profiler;
	return profiler;
}

// Add a time trial for a profile
void TimeProfiler::addProfile(const std::string& name, double time) {

	profiles[name].m_totalTrials++;
	profiles[name].m_totalTime += time;
}

// Start a timed interval
void TimeProfiler::startInterval(const std::string& name) {

	intervals[name] = clock();
}

// Stop a timed interval
void TimeProfiler::stopInterval(const std::string& name) {

	IntervalMap::iterator itInterval = intervals.find(name);
	if (itInterval != intervals.end()) {

		addProfile(name, (double)(clock() - itInterval->second));
		intervals.erase(itInterval);
	}
}

// Clear all timed intervals
void TimeProfiler::clearIntervals() {

	for (auto& interval : intervals) {
		addProfile(interval.first, (double)(clock() - interval.second));
	}
	intervals.clear();
}

// Dump profile data to a file
void TimeProfiler::dumpProfile() {
	
	clearIntervals();

	if (profiles.empty()) {
		// Nothing to do
		return;
	}

	std::stringstream profileStream;

	const SimManager& simulation = SimManager::GetManager();

	std::string configFile = simulation.getConfigFileName();
	std::string bodyFile = simulation.getBodyFileName();

	profileStream << "Profile For" << (configFile.empty() ? "" : (" Config: " + configFile + ",")) << " Bodies: " << bodyFile << '\n';
	profileStream << simulation.getConfigAsString() << '\n' << '\n';

	for (auto& profileData : profiles) {
		if (profileData.second.m_totalTrials <= 0) {
			// This shouldn't happen but we should check this anyway in case our assumption
			// of trials >= 1 is broken in the future
			continue;
		}

		profileStream << profileData.first << ":";
		profileStream << " Total Time: " << profileData.second.m_totalTime / (double)CLOCKS_PER_SEC << " s";
		profileStream << ", Total Trials: " << profileData.second.m_totalTrials;
		profileStream << ", Average Time: " << profileData.second.m_totalTime / (double)CLOCKS_PER_SEC / profileData.second.m_totalTrials << " s" << '\n';
	}

	std::ofstream outFile;
	outFile.open("profile_data", std::ofstream::out);

	if (outFile.is_open()) {
		outFile << profileStream.str();
	}

	outFile.close();
}