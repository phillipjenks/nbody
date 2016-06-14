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
	return std::sqrt(lengthSquare());
}
double Vec3::lengthSquare() const {
	return x * x + y * y + z * z;
}

// Normalize the vector
void Vec3::normalize() {
	
	double length = this->length();
	if (length > 0) {
		x /= length;
		y /= length;
		z /= length;
	}
}

Vec3& Vec3::operator+=(const Vec3& other) {
	
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vec3& Vec3::operator*=(double scale) {

	x *= scale;
	y *= scale;
	z *= scale;

	return *this;
}

Vec3& Vec3::operator/=(double scale) {

	if (scale != 0) {
		x /= scale;
		y /= scale;
		z /= scale;
	}

	return *this;
}

Vec3 operator+(const Vec3& lhs, const Vec3& rhs) {
	return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vec3 operator*(double scale, const Vec3& vec) {
	return Vec3(scale * vec.x, scale * vec.y, scale * vec.z);
}
Vec3 operator*(const Vec3& vec, double scale) {
	return scale * vec;
}

// Return 0 vector if attempt to divide by zero
Vec3 operator/(const Vec3& vec, double scale) {
	
	Vec3 ret;
	if (scale != 0) {
		ret = vec;
		ret /= scale;
	}
	return ret;
}

Vec3 operator-(const Vec3& vec) {
	return Vec3(-vec.x, -vec.y, -vec.z);
}
Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
	return lhs + (-rhs);
}

std::ostream& operator<<(std::ostream& out, const Vec3& vec) {
	return out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
}