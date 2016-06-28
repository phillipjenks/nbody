#include "stdafx.h"

#include <filesystem>
#include <thread>

#include "SimManager.h"
#include "SimBodyManager.h"
#include "SimBody.h"
#include "Vec3.h"

void runStep(std::size_t begin, std::size_t end, VecBody* bodies, double dt);

const unsigned int NUM_THREADS = 8;

void SimBodyManager::addBody(double mass, const Vec3& pos, const Vec3& vel) {

	bodies.push_back(SimBody(mass, pos, vel));
}

void SimBodyManager::runTimeStep(double dt) {

	if (bodies.size() < NUM_THREADS) {

		runStep(0, bodies.size() - 1, &bodies, dt);
	} else {

		std::vector<std::thread> threads;
		unsigned int elemsPerThread = bodies.size() / NUM_THREADS;
		unsigned int leftover = bodies.size() % NUM_THREADS;
		std::size_t start = 0;

		for (unsigned int th = 0; th < NUM_THREADS; ++th) {
			
			std::size_t end = start + elemsPerThread - 1;
			if (leftover > 0) {
				++end;
				--leftover;
			}

			// std::cout << "Thread " << th << " got elems " << start << " - " << end << " for " << bodies.size() << " bodies " << elemsPerThread << std::endl;
			threads.push_back(std::thread(runStep, start, end, &bodies, dt));

			start = end + 1;
		}

		for (auto& th : threads) {
			th.join();
		}
	}

	for (auto& body : bodies) {
		body.updatePosAndVel(dt);
	}
}

void runStep(std::size_t begin, std::size_t end, VecBody* bodies, double dt) {

	for (std::size_t ind = begin; ind <= end; ++ind) {
		SimBody& body = (*bodies)[ind];

		body.prepForTimeStep();

		for (auto& otherBody : (*bodies)) {
			if (!body.areSameBody(otherBody)) {
				body.applyForceFrom(dt, otherBody);
			}
		}
	}
}
