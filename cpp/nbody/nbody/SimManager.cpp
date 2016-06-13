#include "stdafx.h"

#include <iostream>

#include "SimManager.h"

// Default Constructor
// Initialize default sim configurations
SimManager::SimManager() {

	config.timeStep = 0.01;
	config.softeningParam = 0.0025;
}

// Initialize simulation
bool SimManager::init() {

	std::cout << "Sim Initialization" << std::endl;
	printConfig();

	return true;
}

// Print sim config
void SimManager::printConfig() const {

	std::cout << "Sim Config" << std::endl;
	std::cout << '\t' << "Time Step:       " << config.timeStep << std::endl;
	std::cout << '\t' << "Softening Param: " << config.softeningParam << std::endl;
}