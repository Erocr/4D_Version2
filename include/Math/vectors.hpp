#ifndef VECTORS
#define VECTORS

#include <math.h>
#include <string>
#include <stdexcept>
#include <Math/Vec2d.hpp>
#include <Math/Vec3d.hpp>
#include <Math/Vec4d.hpp>
using namespace std;


Vec2d to2d(Vec3d v);
Vec2d to2d(Vec4d v);
Vec3d to3d(Vec2d v, float z = 0);
Vec3d to3d(Vec4d v);
Vec4d to4d(Vec2d v, float z = 0, float w = 0);
Vec4d to4d(Vec3d v, float w = 0);


#endif