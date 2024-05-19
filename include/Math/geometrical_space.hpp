#ifndef SPACE
#define SPACE

#include "Math/geometrical_vectors.hpp"
#include "Math/geometrical_line.hpp"

class Space {
public:
	Vec4d point; Vec4d normal;
	Space();
	Space(Vec4d p, Vec4d n);
	Vec4d intersection(Line4d line);
};

#endif