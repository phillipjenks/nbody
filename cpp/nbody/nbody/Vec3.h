
#ifndef __VEC3_H_
#define __VEC3_H_

#include <iostream>

class Vec3
{
public:

	double x, y, z;

	Vec3();
	Vec3(double x, double y, double z);
	Vec3(double x, double y);

	~Vec3() = default;

	Vec3(const Vec3&) = default;
	Vec3& operator=(const Vec3&) = default;

	Vec3(Vec3&&) = default;
	Vec3& operator=(Vec3&&) = default;

	// Return vector length
	double length() const;
	double lengthSquare() const;

	// Normalize our vector
	void normalize();

	Vec3& operator+=(const Vec3& other);
	Vec3& operator*=(double scale);
	Vec3& operator/=(double scale);
};

// Utility operator overloading
Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
Vec3 operator*(double scale, const Vec3& vec);
Vec3 operator*(const Vec3& vec, double scale);
Vec3 operator/(const Vec3& vec, double scale);
Vec3 operator-(const Vec3& vec);
Vec3 operator-(const Vec3& lhs, const Vec3& rhs);

std::ostream& operator<<(std::ostream& out, const Vec3& vec);

#endif
