// nbody.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "SimManager.h"

int main(int argc, char** argv)
{

	SimManager simulation;

	std::cout << "---- Initializing Sim" << std::endl;
	simulation.init();

	std::cout << "---- Simulation Finished" << std::endl;

	std::cin.ignore();

    return 0;
}

