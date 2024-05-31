#include "Math/geometrical_space.hpp"
#include <iostream>

#include "doctest.h"

Space::Space() {
	point = Vec4d(0, 0, 0, 0);
	normal = Vec4d(0, 0, 0, -1);
    angles[0] = 0; angles[1] = 0; angles[2] = 0; angles[3] = 0; angles[4] = 0; angles[5] = 0;
    base[0] = Vec4d(); base[1] = Vec4d(); base[2] = Vec4d();
    updateNormal();
}

Vec4d Space::intersection(Line4d line) {
    float denom = normal.scalar(line.dir);
    float num = (point.x - line.p1.x) * normal.x + (point.y - line.p1.y) * normal.y +
        (point.z - line.p1.z) * normal.z + (point.w - line.p1.w) * normal.w;
    if (denom != 0) {
        float k = num / denom;
        if (k >= 0 && k <= 1) {
            return Vec4d(line.p1.add(line.dir.mul(k)));
        }
    }
}

bool Space::in_normal_side(Vec4d p) {
    return (p - point).scalar(normal) > 0;
}

void Space::rotate(float angle, int axis) {
    if (axis >= 6 || axis < 0) throw range_error("Cet axe n'existe pas");
    angles[axis] += angle;
}


void Space::updateNormal() {
    normal = vec(0, 0, 0, -1).rotation(angles);
    base[0] = vec(1, 0, 0, 0).rotation(angles);
    base[1] = vec(0, 1, 0, 0).rotation(angles);
    base[2] = vec(0, 0, 1, 0).rotation(angles);
}


Vec3d Space::changingBase(Vec4d vec) const {
    vec = vec - point;
    Vec4d res = base[0] * vec.x + base[1] * vec.y + base[2] * vec.z + normal * vec.w;
    if (abs(res.w) > 0.0001) throw runtime_error("vec n'est pas dans l'espace");
    return { res.x, res.y, res.z };
}


TEST_CASE("space") {
    Space space = Space();
    SUBCASE("intersection") {
        CHECK((space.intersection(Line4d(vec(1, 1, 1, 1), vec(1, 1, 1, -1))) == vec(1, 1, 1, 0)));
        CHECK((space.intersection(Line4d(vec(10, 1, 19, 1), vec(10, 1, 19, -1))) == vec(10, 1, 19, 0)));
    }
    SUBCASE("in_normal_side") {
        CHECK(space.in_normal_side(Vec4d(0, 0, 0, -1)));
        CHECK_FALSE(space.in_normal_side(Vec4d(0, 0, 0, 1)));
        CHECK(space.in_normal_side(Vec4d(1, 2, 3, -8)));
        CHECK_FALSE(space.in_normal_side(Vec4d(0, 0, 0, 0)));
    }
    SUBCASE("changingBase") {
        space.rotate(PI / 2, 2);
        space.updateNormal();
        CHECK(space.changingBase(Vec4d(0, 0, 0, -1)).alm_equal(Vec3d(1, 0, 0)));
        CHECK_THROWS_AS(space.changingBase(Vec4d(1, 0, 0, 0)), runtime_error);
    }
};


