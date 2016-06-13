
#ifndef __VEC3_H_
#define __VEC3_H_

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
};

// Utility operator overloading
Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
Vec3 operator*(double scale, const Vec3& vec);
Vec3 operator-(const Vec3& vec);
Vec3 operator-(const Vec3& lhs, const Vec3& rhs);

#endif
