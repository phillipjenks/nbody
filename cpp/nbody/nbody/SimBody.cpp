#include "stdafx.h"

#include "SimManager.h"
#include "SimBody.h"
#include "Vec3.h"
#include "Physics.h"

unsigned int SimBody::globalId = 0;

SimBody::SimBody()
	: SimBody(0, Vec3(), Vec3())
{
}

SimBody::SimBody(double mass, const Vec3& pos, const Vec3& vel)
	: id(++globalId)
	, mass(mass)
	, pos(pos)
	, deltaPos()
	, vel(vel)
	, deltaVel()
{}

void SimBody::prepForTimeStep() {

	if(SimManager::GetManager().getConfig().enableDebugOutput)
		std::cout << id << " Prepping for time step " << std::endl;

	deltaPos *= 0;
	deltaVel *= 0;
}

void SimBody::applyForceFrom(double dt, const SimBody& other) {

	if (!areSameBody(other)) {
		// RK4 Implementation http://spiff.rit.edu/richmond/nbody/OrbitRungeKutta4.pdf
		SimManager& manager = SimManager::GetManager();

		Vec3 relPos = pos - other.pos;

		Vec3 k1v = gravitationalAcceleration(other.mass, relPos);
		Vec3 k1r = vel;

		Vec3 k2v = gravitationalAcceleration(other.mass, relPos + 0.5 * dt * k1r);
		Vec3 k2r = vel + 0.5 * dt * k1v;

		Vec3 k3v = gravitationalAcceleration(other.mass, relPos + 0.5 * dt * k2r);
		Vec3 k3r = vel + 0.5 * dt * k2v;

		Vec3 k4v = gravitationalAcceleration(other.mass, relPos + 0.5 * dt * k3r);
		Vec3 k4r = vel + dt * k3v;

		if (manager.getConfig().enableDebugOutput) {
			std::cout << id << " deltas before rk with " << other.id << " on " << id << " " << deltaPos << " " << deltaVel << std::endl;
		}

		// Add up our RK estimations
		// Subtract off our additions from velocity so that they are not double counted
		// This will be added back in SimBody::updatePosAndVel
		deltaPos += dt * (k1r + 2 * k2r + 2 * k3r + k4r) / 6 - dt * vel;
		deltaVel += dt * (k1v + 2 * k2v + 2 * k3v + k4v) / 6;

		if (manager.getConfig().enableDebugOutput) {
			std::cout << other.id << " on " << id << " " << deltaPos << " " << deltaVel << std::endl;
		}
	}
}

void SimBody::updatePosAndVel(double dt) {

	SimManager& manager = SimManager::GetManager();

	if (manager.getConfig().enableDebugOutput)
		std::cout << id << " Old Pos And Vel " << pos << " " << deltaPos << " " << vel << " " << deltaVel << std::endl;

	pos += deltaPos + vel * dt;
	vel += deltaVel;

	if (manager.getConfig().enableDebugOutput)
		std::cout << id << " New Pos And Vel " << pos << " " << vel << std::endl;
}
