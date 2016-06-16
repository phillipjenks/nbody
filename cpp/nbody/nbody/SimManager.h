
#ifndef __SIMMANAGER_H_
#define __SIMMANAGER_H_

#include <string>

#include "SimBodyManager.h"
#include "DataOutput.h"

namespace {
	typedef struct {
		double timeStep;
		double outputFrequency;
		double totalSimTime;
		double softeningParam;
		double gravityStrength;

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
	bool init(const std::string& configFile, const std::string& bodyFile);

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
	double outputTime;

	// Utility class for managing sim bodies
	SimBodyManager bodyManager;

	// Utility class for file output
	DataOutput dataOutput;

	// Utility to print the sim configuration
	void printConfig() const;
	bool loadConfig(const std::string& configFile);
	bool loadBodies(const std::string& bodyFile);
};

#endif