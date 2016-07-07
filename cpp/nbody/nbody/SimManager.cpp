#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

#include "SimManager.h"
#include "TimedInterval.h"
#include "TimeProfiler.h"

SimManager& SimManager::GetManager() {

	static SimManager manager;
	return manager;
}

// Default Constructor
// Initialize default sim configurations
SimManager::SimManager()
	: time(0)
	, outputTime(0)
	, bodyManager()
	, dataOutput()
{
	config.timeStep = 0.01;
	config.outputFrequency = 0.01;
	config.softeningParam = 0.0025;
	config.gravityStrength = 0.001;
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
		START_TIMED_INTERVAL("Read Config File");
		this->configFile = configFile;
		if (!loadConfig(configFile)) {
			std::cout << "Failed to load given config file " << configFile << ". Using default configuration" << std::endl;
		}
		STOP_TIMED_INTERVAL("Read Config File");
	}
	printConfig();

	if (bodyFile.empty()) {
		std::cout << "No Body File Given" << std::endl;
		return false;
	}

	START_TIMED_INTERVAL("Read Body File");
	this->bodyFile = bodyFile;
	if (!loadBodies(bodyFile)) {
		std::cout << "Failed to load initial condition file " << bodyFile << std::endl;
		return false;
	}
	STOP_TIMED_INTERVAL("Read Body File");

	std::cout << "Number Of Bodies: " << getTotalNumberOfBodies() << std::endl;

	return true;
}

void SimManager::runSimulation() {

	if (!bodyManager.hasBodies()) {
		std::cout << "No bodies to simulate. Skipping simulation" << std::endl;
		return;
	}

	char spacing[] = "                             ";

	if (!config.enableDebugOutput) {
		std::cout << std::endl;
	}

	// dump initial condition
	dataOutput.dumpOutput(time, bodyManager.getBodies());

	// This is used to handle accuracy errors when comparing doubles
	double outputThreshold = 0.001;

	while (time < config.totalSimTime) {

		TIMED_INTERVAL("Simulation Loop");

		if (!config.enableDebugOutput) {
			std::cout << '\t' << "Simulation Progress: " << time << "/" << config.totalSimTime << " (" << int(100 * time / config.totalSimTime) << "%)" << spacing << '\r';
		}

		double dt = std::fmin(config.timeStep, config.totalSimTime - time);

		if (config.enableDebugOutput) {
			std::cout << "++++++++ Running step t = " << time << ", dt = " << dt << std::endl;
		}

		bodyManager.runTimeStep(dt);
		time += dt;

		if (time >= (outputTime - outputThreshold)) {
			dataOutput.dumpOutput(time, bodyManager.getBodies());
			outputTime += config.outputFrequency;
		}
	}

	if (!config.enableDebugOutput) {
		std::cout << '\t' << "Simulation Progress: " << time << "/" << config.totalSimTime << " (100%)" << spacing << '\n' << std::endl;
	}
}

// Return the config as a string
std::string SimManager::getConfigAsString() const {

	std::stringstream configStream;

	configStream << "Sim Config" << '\n';
	configStream << '\t' << "Time Step:        " << config.timeStep << '\n';
	configStream << '\t' << "Output Frequency: " << config.outputFrequency << '\n';
	configStream << '\t' << "Total Sim Time:   " << config.totalSimTime << '\n';
	configStream << '\t' << "Softening Param:  " << config.softeningParam << '\n';
	configStream << '\t' << "Gravity Strength: " << config.gravityStrength << '\n';
	configStream << '\t' << "Debug Output:     " << (config.enableDebugOutput ? 'T' : 'F');

	return configStream.str();
}

// Print sim config
void SimManager::printConfig() const {

	std::cout << getConfigAsString() << std::endl;
}

namespace {
	template<class T>
	void loadValue(std::stringstream& ss, T& currVal) {

		T tmpVal = currVal;
		ss >> tmpVal;
		
		currVal = tmpVal;
	}

	// Implement specific functionality for loadValue::<bool>
	void loadValue(std::stringstream& ss, bool& currVal) {

		std::string asString;
		loadValue(ss, asString);

		if (!asString.empty()) {

			std::transform(asString.begin(), asString.end(), asString.begin(), ::tolower);
			if (asString == "true" || asString == "t" || asString == "1") {
				currVal = true;
			} else if(asString == "false" || asString == "f" || asString == "0") {
				currVal = false;
			}
		}
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
		} else if (paramName == "OutputFrequency") {

			loadValue(ssParam, tmpConfig.outputFrequency);
		} else if (paramName == "TotalTime") {
			
			loadValue(ssParam, tmpConfig.totalSimTime);
		} else if (paramName == "SofteningParam") {

			loadValue(ssParam, tmpConfig.softeningParam);
		} else if (paramName == "GravityStrength") {

			loadValue(ssParam, tmpConfig.gravityStrength);
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