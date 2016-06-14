
#ifndef __SIMBODY_H_
#define __SIMBODY_H_

#include "Vec3.h"

class SimBody
{
public:

	SimBody();
	SimBody(double mass, const Vec3& pos, const Vec3& vel);

	void prepForTimeStep();
	void applyForce(double dt, const SimBody&);
	void updatePosAndVel();

private:

	static int globalId;

	int id;

	double mass;

	Vec3 pos;
	Vec3 deltaPos;

	Vec3 vel;
	Vec3 deltaVel;
};

#endif
