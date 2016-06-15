// nbody.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>

#include "SimManager.h"

void getOpts(int argc, char** argv, std::string& configFile, std::string& bodyFile);

int main(int argc, char** argv)
{

	std::string configFile;
	std::string bodyFile;

	getOpts(argc, argv, configFile, bodyFile);

	if (bodyFile.empty()) {
		std::cout << "Usage: nbody.exe <body_file> [-c <config_file>]";
		return 0;
	}

	SimManager& simulation = SimManager::GetManager();

	std::cout << "---- Initializing Sim" << std::endl;
	if (!simulation.init(configFile, bodyFile)) {
		std::cout << "---- Sim Failed To Initialize" << std::endl;
		return 1;
	}

	std::cout << "---- Running Simulation" << std::endl;
	simulation.runSimulation();

	std::cout << "---- Simulation Finished" << std::endl;

    return 0;
}

void getOpts(int argc, char** argv, std::string& configFile, std::string& bodyFile) {
	for (int i = 1; i < argc; ++i) {
		std::string arg(argv[i]);

		if (arg == "-c") {
			if (i + 1 < argc) {
				configFile = argv[i + 1];
				++i;
			}
		}
		// Only take the first non-config file
		else if(bodyFile.empty()) {
			bodyFile = argv[i];
		}
	}
}

