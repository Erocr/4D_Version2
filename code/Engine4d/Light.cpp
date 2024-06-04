#include <Engine4d/Light.hpp>
#include <Math/vectors.hpp>

Light::Light(Vec4d pos_, Color c, int brightness_) : pos{ pos_ }, color{ c }, brightness{ brightness_ }
{
	if (brightness < 0 || brightness > 255) throw runtime_error("La brightness doit etre entre 0 et 255");
}


Color Light::wallColor(Vec3d point, Vec3d normal, Color wallCol) const {
	Vec4d vl = (pos - to4d(point).normalise());
	float d = dist(to4d(point), pos);
	if (d < 1) d = 1;
	Vec4d vp = to4d(normal.normalise());
	float x = (vp.scalar(vl) + 1) / 510.;
	return wallCol * ColorFloat{ color.r * x, color.g * x, color.b * x, color.a };

}
