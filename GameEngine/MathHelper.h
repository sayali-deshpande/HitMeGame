#ifndef _MATHHELPER_H
#define _MATHHELPER_H
#include <math.h>

#define PI 3.14159265
#define DEG_TO_RAD PI /180.0f

class Vector2
{
public:
	float x;
	float y;

	Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {};

	float Magnitude()
	{
		return (float)sqrt(x*x + y*y);
	}
	Vector2 Normalized()
	{
		float mag = Magnitude();
		return Vector2(x / mag, y / mag);
	}

	Vector2& Add(const Vector2& vec)
	{
		this->x = this->x +  vec.x;
		this->y = this->y + vec.y;
		return *this;
	}

	Vector2& Subtract(const Vector2& vec)
	{
		this->x = this->x - vec.x;
		this->y = this->y - vec.y;
		return *this;
	}

	friend inline Vector2& operator +(Vector2& vec1, const Vector2& vec2)
	{
		//return (vec1.x + vec2.x, vec1.y + vec2.y);
		return vec1.Add(vec2);
	}
	friend inline Vector2& operator -(Vector2& vec1, const Vector2& vec2)
	{
		//return (vec1.x - vec2.x, vec1.y - vec2.y);
		return vec1.Subtract(vec2);
	}
	friend inline Vector2& RotateVector(Vector2& vec, float angle)
	{
		float radAngle = (float)(angle *radAngle);
		return Vector2((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle + vec.y * cos(radAngle))));
	}
};



#endif
