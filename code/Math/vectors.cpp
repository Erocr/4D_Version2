#include <Math/vectors.hpp>


Vec2d to2d(Vec3d v) {
	return { v.x, v.y };
}

Vec2d to2d(Vec4d v) {
	return { v.x, v.y };
}

Vec3d to3d(Vec2d v, float z) {
	return { v.x, v.y, z };
}

Vec3d to3d(Vec4d v) {
	return { v.x, v.y, v.z };
}

Vec4d to4d(Vec2d v, float z, float w) {
	return { v.x, v.y, z, w };
}

Vec4d to4d(Vec3d v, float w) {
	return { v.x, v.y, v.z, w };
}
