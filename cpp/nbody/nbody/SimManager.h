
#ifndef __SIMMANAGER_H_
#define __SIMMANAGER_H_

namespace {
	typedef struct {
		double timeStep;
		double softeningParam;
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

private:

	// Private constructor for singleton instance
	SimManager();

	// Struct with configuration parameters
	SimConfig config;

	// current time
	double time;

	// Utility to print the sim configuration
	void printConfig() const;
};

#endif