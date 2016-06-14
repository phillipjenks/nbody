
#ifndef __SIMMANAGER_H_
#define __SIMMANAGER_H_

#include "SimBodyManager.h"

namespace {
	typedef struct {
		double timeStep;
		double totalSimTime;
		double softeningParam;

		bool enableDebugOutput;
	} SimConfig;
}

class SimManager
{
public:

	static SimManager& GetManager();

	~SimManager() = default;

	SimManager(const SimManager&) = delete;
	SimManager& operator=(const SimManager&) = delete;

	SimManager(SimManager&&) = delete;
	SimManager& operator=(SimManager&&) = delete;

	// Initialize simulation
	// -- Update config if necessary
	// -- Read in initial conditions
	bool init();

	// Run the simulation
	void runSimulation();

	const SimConfig& getConfig() const { return config; }

private:

	// Private constructor for singleton instance
	SimManager();

	// Struct with configuration parameters
	SimConfig config;

	// current time
	double time;

	// Utility class for managing sim bodies
	SimBodyManager bodyManager;

	// Utility to print the sim configuration
	void printConfig() const;
};

#endif