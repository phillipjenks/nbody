
#ifndef __SIMBODYMANAGER_H_
#define __SIMBODYMANAGER_H_

#include <vector>

// Forward Declarations
class Vec3;
class SimBody;

// aliasing
using VecBody = std::vector<SimBody>;

class SimBodyManager
{
public:
	
	// Add a body to the body manager
	void addBody(double mass, const Vec3& pos, const Vec3& vel);

	// Run a time step for our bodies
	void runTimeStep(double dt);

private:

	// Our body list
	VecBody bodies;
};

#endif