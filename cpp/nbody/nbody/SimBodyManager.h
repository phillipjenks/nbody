
#ifndef __SIMBODYMANAGER_H_
#define __SIMBODYMANAGER_H_

#include <vector>

#include "SimBody.h"

// Forward Declarations
class Vec3;

class SimBodyManager
{
public:
	
	// Add a body to the body manager
	void addBody(double mass, const Vec3& pos, const Vec3& vel);

	// Run a time step for our bodies
	void runTimeStep(double dt);

	// Method to assess whether or not we own any bodies
	bool hasBodies() const { return !bodies.empty(); }

	const VecBody& getBodies() const { return bodies; }

private:

	// Our body list
	VecBody bodies;
};

#endif