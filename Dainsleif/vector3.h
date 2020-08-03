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

	Vector3& operator-(Vector3 arg)
	{
		x -= arg.x;
		y -= arg.y;
		z -= arg.z;
		return *this;
	}

	Vector3& operator*(float arg)
	{
		x *= arg;
		y *= arg;
		z *= arg;
		return *this;
	}

	void Normalize() {
        while (y > 180)
            y -= 360;
        while (y < -180)
            y += 360;

        if (x > 89.f)
            x = 89.f;
        else if (x < -89.f)
            x = -89.f;
	}
};
