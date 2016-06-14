#include "stdafx.h"

#include "SimManager.h"
#include "Physics.h"
#include "Vec3.h"

Vec3 gravitationalAcceleration(double mass, const Vec3& pos) {

	SimManager& manager = SimManager::GetManager();

	Vec3 acc = pos;
	acc.normalize();

	// pos is assumed to point from source mass to target mass
	// acc will point opposite this
	acc *= -1; 

	double distSq = pos.lengthSquare();
	if (distSq > 0) {
		double accMag = mass / (distSq + manager.getConfig().softeningParam);
		acc *= accMag;
	}

	return acc;
}