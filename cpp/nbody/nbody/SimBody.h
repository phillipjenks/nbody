
#ifndef __SIMBODY_H_
#define __SIMBODY_H_

#include "Vec3.h"

class SimBody
{
public:

	SimBody();
	SimBody(double mass, const Vec3& pos, const Vec3& vel);

	void prepForTimeStep();
	void applyForceFrom(double dt, const SimBody&);
	void updatePosAndVel();

	inline bool areSameBody(const SimBody& other) { return id == other.id; }

	unsigned int getId() const { return id; }
	double getMass() const { return mass; }
	const Vec3& getPos() const { return pos; }
	const Vec3& getVel() const { return vel; }

private:

	static unsigned int globalId;

	unsigned int id;

	double mass;

	Vec3 pos;
	Vec3 deltaPos;

	Vec3 vel;
	Vec3 deltaVel;
};

// aliasing
using VecBody = std::vector<SimBody>;

#endif
