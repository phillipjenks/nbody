#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <sstream>
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
	, dataOutput()
{
	config.timeStep = 0.01;
	config.softeningParam = 0.0025;
	config.totalSimTime = 1;
	config.enableDebugOutput = true;
}

// Initialize simulation
bool SimManager::init(const std::string& configFile, const std::string& bodyFile) {

	std::cout << "Sim Initialization" << std::endl;

	if (!dataOutput.init()) {
		std::cout << "Failed to initialize data output module" << std::endl;
		return false;
	}

	if (!configFile.empty()) {
		if (!loadConfig(configFile)) {
			std::cout << "Failed to load given config file " << configFile << ". Using default configuration" << std::endl;
		}
	}
	printConfig();

	if (bodyFile.empty()) {
		std::cout << "No Body File Given" << std::endl;
		return false;
	}
	if (!loadBodies(bodyFile)) {
		std::cout << "Failed to load initial condition file " << bodyFile << std::endl;
		return false;
	}

	return true;
}

void SimManager::runSimulation() {

	if (!bodyManager.hasBodies()) {
		std::cout << "No bodies to simulate. Skipping simulation" << std::endl;
		return;
	}

	while (time < config.totalSimTime) {
		double dt = std::fmin(config.timeStep, config.totalSimTime - time);

		if(config.enableDebugOutput)
			std::cout << "++++++++ Running step t = " << time << ", dt = " << dt << std::endl;
		bodyManager.runTimeStep(dt);

		dataOutput.dumpOutput(time, bodyManager.getBodies());
		time += dt;
	}
}

// Print sim config
void SimManager::printConfig() const {

	std::cout << "Sim Config" << std::endl;
	std::cout << '\t' << "Time Step:       " << config.timeStep << std::endl;
	std::cout << '\t' << "Total Sim Time:  " << config.totalSimTime << std::endl;
	std::cout << '\t' << "Softening Param: " << config.softeningParam << std::endl;
	std::cout << '\t' << "Debug Output:    " << (config.enableDebugOutput ? 'T' : 'F') << std::endl;
}

namespace {
	template<class T>
	void loadValue(std::stringstream& ss, T& currVal) {

		T tmpVal = currVal;
		ss >> tmpVal;
		
		currVal = tmpVal;
	}
}

bool SimManager::loadConfig(const std::string& configFile) {

	std::ifstream inFile(configFile.c_str());

	if (inFile.fail()) {
		std::cout << "Failed To Read Config File" << std::endl;
		return false;
	}

	std::string line;

	SimConfig tmpConfig = config;

	while (inFile.good()) {

		std::getline(inFile, line);

		std::stringstream ssParam(line);
		std::string paramName;

		ssParam >> paramName;

		if (paramName == "TimeStep") {

			loadValue(ssParam, tmpConfig.timeStep);
		} else if (paramName == "TotalTime") {
			
			loadValue(ssParam, tmpConfig.totalSimTime);
		} else if (paramName == "SofteningParam") {
		
			loadValue(ssParam, tmpConfig.softeningParam);
		} else if (paramName == "DebugOutput") {
		
			loadValue(ssParam, tmpConfig.enableDebugOutput);
		}
	}

	inFile.close();

	config = tmpConfig;

	return true;
}

bool SimManager::loadBodies(const std::string& bodyFile) {

	std::ifstream inFile(bodyFile.c_str());

	if (inFile.fail()) {
		std::cout << "Failed To Read Body File" << std::endl;
		return false;
	}

	std::string line;

	while (inFile.good()) {

		double mass = 0;
		Vec3 pos;
		Vec3 vel;

		std::getline(inFile, line);
		std::stringstream ssBody(line);

		loadValue(ssBody, mass);
		if (mass == 0) {
			std::cout << "Got body with zero mass. Skipping." << std::endl;
			continue;
		}

		loadValue(ssBody, pos.x);
		loadValue(ssBody, pos.y);
		loadValue(ssBody, pos.z);

		loadValue(ssBody, vel.x);
		loadValue(ssBody, vel.y);
		loadValue(ssBody, vel.z);

		bodyManager.addBody(mass, pos, vel);
	}

	return true;
}