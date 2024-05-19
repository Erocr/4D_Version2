#include "Math/geometrical_space.hpp"

#include "doctest.h"

Space::Space() {
	point = Vec4d(0, 0, 0, 0);
	normal = Vec4d(1, 0, 0, 0);
}
Space::Space(Vec4d p, Vec4d n) {
	point = p;
	normal = n;
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

TEST_CASE("space") {
    Space space = Space();
    SUBCASE("intersection") {
        CHECK((space.intersection(Line4d(vec(1, 1, 1, 1), vec(-1, 1, 1, 1))) == vec(0, 1, 1, 1)));
        CHECK((space.intersection(Line4d(vec(10, 1, 19, 1), vec(-10, 1, 19, 1))) == vec(0, 1, 19, 1)));
    }
};

