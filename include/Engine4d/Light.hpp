#pragma once

#include <Math/vectors.hpp>
#include <View/Color.hpp>

class Light {
public:
	Light(Vec4d pos_, Color c, int brightness_);
	Color wallColor(Vec3d point, Vec3d normal, Color wallCol) const;

private:
	Vec4d pos;
	Color color;
	int brightness;
};