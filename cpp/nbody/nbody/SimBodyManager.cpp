#include "stdafx.h"

#include <filesystem>

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
		body.updatePosAndVel(dt);
	}
}
