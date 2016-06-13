#include "stdafx.h"

#include <cmath>

#include "Vec3.h"

// Init our vector to the origin
Vec3::Vec3()
	: Vec3(0, 0)
{}

Vec3::Vec3(double x, double y)
	: Vec3(x, y, 0)
{}

Vec3::Vec3(double x, double y, double z)
	: x(x)
	, y(y)
	, z(z)
{}

// Return vector length
double Vec3::length() const {
	return std::sqrt(x * x + y * y + z * z);
}

Vec3 operator+(const Vec3& lhs, const Vec3& rhs) {
	return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vec3 operator*(double scale, const Vec3& vec) {
	return Vec3(scale * vec.x, scale * vec.y, scale * vec.z);
}

Vec3 operator-(const Vec3& vec) {
	return Vec3(-vec.x, -vec.y, -vec.z);
}
Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
	return lhs + (-rhs);
}