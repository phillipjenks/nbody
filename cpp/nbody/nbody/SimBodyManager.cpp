#include "stdafx.h"

#include "SimManager.h"
#include "SimBodyManager.h"
#include "SimBody.h"
#include "Vec3.h"


void SimBodyManager::addBody(double mass, const Vec3& pos, const Vec3& vel) {

	bodies.push_back(SimBody(mass, pos, vel));
}

void SimBodyManager::runTimeStep(double dt) {

	// Naive implementation
	for (auto& body : bodies) {

		body.prepForTimeStep();

		for (auto& otherBody : bodies) {

			if (!body.areSameBody(otherBody)) {
				body.applyForceFrom(dt, otherBody);
			}
		}
	}

	for (auto& body : bodies) {
		body.updatePosAndVel();
	}
}

void SimBodyManager::dumpOutput() const {

	// Just dump to stdout for now
	for (auto body : bodies) {
		std::cout << "              Body: "
					<< body.getId()
					<< ", Mass: "
					<< body.getMass()
					<< ", Pos: "
					<< body.getPos()
					<< ", Vel: "
					<< body.getVel()
					<< std::endl;
	}
}