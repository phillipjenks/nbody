#include "stdafx.h"

#include "SimBody.h"
#include "Vec3.h"

int SimBody::globalId = 0;

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
	deltaPos = Vec3();
	deltaVel = Vec3();
}

void SimBody::applyForce(double dt, const SimBody& other) {

	if (id != other.id) {
		// do the math
	}
}

void SimBody::updatePosAndVel() {
	pos += deltaPos;
	vel += deltaVel;

	prepForTimeStep();
}
