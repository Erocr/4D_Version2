# pragma once

#include <algorithm>

typedef uint8_t Uint8;


struct ColorFloat {
	float r;
	float g;
	float b;
	float a;

	ColorFloat(float _r, float _g, float _b, float _a) : r{ _r }, g{ _g }, b{ _b }, a{ _a } {
		if (r > 1) r = 1; else if (r < 0) r = 0;
		if (g > 1) g = 1; else if (g < 0) g = 0;
		if (b > 1) b = 1; else if (b < 0) b = 0;
		if (a > 1) a = 1; else if (a < 0) a = 0;
	}

	ColorFloat operator+(ColorFloat c) {
		return { r + c.r, g + c.g, b + c.b, a + c.a };
	}
	ColorFloat operator-(ColorFloat c) {
		return { r - c.r, g - c.g, b - c.b, a - c.a };
	}
	ColorFloat operator*(float o) {
		return { r * o, g * o, b * o, a * o };
	}
	ColorFloat operator/(float o) {
		return { r / o, g / o, b / o, a / o };
	}
	ColorFloat operator*(ColorFloat c) {
		return { r * c.r, g * c.g, b * c.b, a * c.a };
	}
	ColorFloat operator/(ColorFloat c) {
		return { r / c.r, g / c.g, b / c.b, a / c.a };
	}
};


struct Color {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;

	Color(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a) : r{ _r }, g{ _g }, b{ _b }, a{ _a } {}
	Color(Uint8 _r, Uint8 _g, Uint8 _b) : r{ _r }, g{ _g }, b{ _b }, a{ 255 } {}
	Color() : r{ 0 }, g{ 0 }, b{ 0 }, a{ 255 } {}

	Color operator+(Color c) {
		return { Uint8(r + c.r), Uint8(g + c.g), Uint8(b + c.b), Uint8(a +c.a) };
	}
	Color operator-(Color c) {
		return { Uint8(r - c.r), Uint8(g - c.g), Uint8(b - c.b), Uint8(a - c.a) };
	}
	Color operator*(ColorFloat c) {
		return { Uint8(r * c.r), Uint8(g * c.g), Uint8(b * c.b), Uint8(a * c.a) };
	}
};