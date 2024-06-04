#ifndef SPACE
#define SPACE

#include "Math/vectors.hpp"
#include "Math/line.hpp"

class Space {
public:
	Vec4d point; Vec4d normal;
	Space();
	Vec4d intersection(Line4d line);
	bool in_normal_side(Vec4d p);

	// axis est successivement pour les axes xy, xz, xw, yz, yw, zw
	void rotate(float angle, int axis);
	void updateNormal();

	Vec3d changingBase(Vec4d vec) const;
	Vec4d changingBase4d(Vec4d vec) const;
private:
	float angles[6];
	// base calculee dans updateNormal()
	Vec4d base[3];
};

#endif