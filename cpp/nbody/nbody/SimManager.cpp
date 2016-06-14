#include "stdafx.h"

#include <iostream>
#include <cmath>

#include "SimManager.h"

SimManager& SimManager::GetManager() {

	static SimManager manager;
	return manager;
}

// Default Constructor
// Initialize default sim configurations
SimManager::SimManager()
	: time(0)
	, bodyManager()
{
	config.timeStep = 0.01;
	config.softeningParam = 0.0025;
	config.totalSimTime = 1;
	config.enableDebugOutput = true;
}

// Initialize simulation
bool SimManager::init() {

	std::cout << "Sim Initialization" << std::endl;
	printConfig();

	// Some test bodies
	bodyManager.addBody(1, Vec3(1, 0), Vec3(0, 0.1));
	bodyManager.addBody(1, Vec3(-1, 0), Vec3(0, -0.1));

	return true;
}

void SimManager::runSimulation() {

	while (time < config.totalSimTime) {
		double dt = std::fmin(config.timeStep, config.totalSimTime - time);

		if(config.enableDebugOutput)
			std::cout << "++++++++ Running step t = " << time << ", dt = " << dt << std::endl;
		bodyManager.runTimeStep(dt);

		bodyManager.dumpOutput();
		time += dt;
	}
}

// Print sim config
void SimManager::printConfig() const {

	std::cout << "Sim Config" << std::endl;
	std::cout << '\t' << "Time Step:       " << config.timeStep << std::endl;
	std::cout << '\t' << "Total Sim Time:  " << config.totalSimTime << std::endl;
	std::cout << '\t' << "Softening Param: " << config.softeningParam << std::endl;
}