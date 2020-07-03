#pragma once
class Vector3 {
public:
	float x, y, z;

	Vector3& operator+(Vector3 arg)
	{
		x += arg.x;
		y += arg.y;
		z += arg.z;
		return *this;
	}
};
