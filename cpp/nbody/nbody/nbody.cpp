// nbody.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "SimManager.h"

int main(int argc, char** argv)
{

	SimManager& simulation = SimManager::GetManager();

	std::cout << "---- Initializing Sim" << std::endl;
	if (!simulation.init()) {
		std::cout << "---- Sim Failed To Initialize" << std::endl;
		return 1;
	}

	std::cout << "---- Running Simulation" << std::endl;
	simulation.runSimulation();

	std::cout << "---- Simulation Finished" << std::endl;

	std::cin.ignore();

    return 0;
}

