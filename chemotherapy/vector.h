#pragma once
#include "sdk.h"
#include "sse.h"

#include <math.h>
#include <xmmintrin.h>

#include <cstring>
#include <cmath>
#include <limits>

#define FLT_PI 3.1415925f
#define FLT_EPSILON 1.192092896e-07f

//#define max(a,b) (((a)>(b))?(a):(b))
//#define min(a,b) (((a)<(b))?(a):(b))

inline float Rad2Deg(const float &i)
{
	return i * (180.f / FLT_PI);
}

inline float Deg2Rad(const float &i)
{
	return i * (FLT_PI / 180.f);
}

inline float Sqrt(const float &i) // #include <xmmintrin.h>
{
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(i)));
}



class Vector
{
public:
	Vector();
	Vector(float, float, float);

	float&	operator [] (int);
	Vector&	operator =  (const Vector&);

	Vector&	operator += (const Vector&);
	Vector&	operator -= (const Vector&);
	Vector&	operator *= (const Vector&);
	Vector&	operator *= (const float);
	Vector&	operator /= (const Vector&);
	Vector&	operator /= (const float);

	Vector	operator +  (const Vector&) const;
	Vector	operator -  (const Vector&) const;
	Vector	operator /  (const Vector&) const;
	Vector	operator /  (const float&)  const;
	Vector	operator *  (const Vector&) const;
	Vector	operator *  (const float&)  const;

	bool	operator == (const Vector&) const;
	bool	operator != (const Vector&) const;


	void	Zero();
	bool	IsZero(const float = FLT_EPSILON) const;
	bool	ToScreen(Vector &) const;


	Vector	Angle(Vector *);

	Vector	Cross(const Vector&) const;
	Vector	Rotate(const Vector&) const;

	Vector	Up();
	Vector	Forward();
	Vector	Right();

	float	Length() const;
	float	Length2D() const;
	float	Dot(const Vector&) const;
	float	DistTo(const Vector&) const;

	float	Normalize();

	void	NormalizeAngle();
	void	ClampAngle();




	float	x, y, z;
};

class VectorAligned : public Vector // put this in vector.h
{
public:
	float w;
};

class matrix4x4
{
public:
	inline float *operator [] (int i)
	{
		return m[i];
	}

	inline const float *operator [] (int i) const
	{
		return m[i];
	}

	float m[4][4];
};

class matrix3x4
{
public:
	inline float *operator [] (int i)
	{
		return m[i];
	}

	inline const float *operator [] (int i) const
	{
		return m[i];
	}

	float m[3][4];
};

inline void Vector::NormalizeAngle()
{
	if (x != x)
	{
		x = 0;
	}
	if (y != y)
	{
		y = 0;
	}
	while (x > 89)
	{
		x = 89;
	}
	while (x < -89)
	{
		x = -89;
	}
	while (y > 180)
	{
		y = y - 360;
	}
	while (y < -180)
	{
		y = y + 360;
	}

	z = 0;
}

inline void Vector::ClampAngle()
{
	while (x > 89)
	{
		x = 89;
	}
	while (x < -89)
	{
		x = -89;
	}
	while (y > 180)
	{
		y = 180;
	}
	while (y < -180)
	{
		y = -180;
	}

	z = 0;
}


inline void Cross(const Vector &a, const Vector &b, Vector &x)
{
	x.x = ((a.y * b.z) - (a.z * b.y));
	x.y = ((a.z * b.x) - (a.x * b.z));
	x.z = ((a.x * b.y) - (a.y * b.x));
}

inline void AngleMatrix(const Vector &angles, matrix3x4 &matrix)
{
	float sp, sy, sr, cp, cy, cr;

	SinCos(Deg2Rad(angles.x), sp, cp);
	SinCos(Deg2Rad(angles.y), sy, cy);
	SinCos(Deg2Rad(angles.z), sr, cr);

	matrix[0][0] = cp * cy;
	matrix[1][0] = cp * sy;
	matrix[2][0] = -sp;

	float crcy = cr * cy;
	float crsy = cr * sy;
	float srcy = sr * cy;
	float srsy = sr * sy;

	matrix[0][1] = sp * srcy - crsy;
	matrix[1][1] = sp * srsy + crcy;
	matrix[2][1] = sr * cp;

	matrix[0][2] = sp * crcy + srsy;
	matrix[1][2] = sp * crsy - srcy;
	matrix[2][2] = cr * cp;

	matrix[0][3] = 0.f;
	matrix[1][3] = 0.f;
	matrix[2][3] = 0.f;
}

inline void AngleVectors(const Vector &angles, Vector *forward)
{
	float sp, sy, cp, cy;

	SinCos(Deg2Rad(angles.x), sp, cp);
	SinCos(Deg2Rad(angles.y), sy, cy);

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
	forward->Normalize();
}

inline void AngleVectors(const Vector &angles, Vector *forward, Vector *right, Vector *up)
{
	float sp, sy, sr, cp, cy, cr;

	SinCos(Deg2Rad(angles.x), sp, cp);
	SinCos(Deg2Rad(angles.y), sy, cy);
	SinCos(Deg2Rad(angles.z), sr, cr);

	if (forward)
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
		forward->Normalize();
	}

	if (right)
	{
		right->x = -(sr * sp * cy) + (cr * sy);
		right->y = -(sr * sp * sy) + -(cr * cy);
		right->z = -(sr * cp);
		right->Normalize();
	}

	if (up)
	{
		up->x = cr * sp * cy + -sr * -sy;
		up->y = cr * sp * sy + -sr * cy;
		up->z = cr * cp;
		up->Normalize();
	}
}

inline void VectorRotate(const Vector &i, const matrix3x4 &matrix, Vector &o)
{
	o.x = i.Dot(Vector(matrix[0][0], matrix[0][1], matrix[0][2]));
	o.y = i.Dot(Vector(matrix[1][0], matrix[1][1], matrix[1][2]));
	o.z = i.Dot(Vector(matrix[2][0], matrix[2][1], matrix[2][2]));
}

inline void VectorRotate(const Vector &i, const Vector &angles, Vector &o)
{
	static matrix3x4 matrix;

	AngleMatrix(angles, matrix);
	VectorRotate(i, matrix, o);
}

inline void VectorAngles(const Vector &vec, Vector &angles)
{
	if (vec.x == 0 && vec.y == 0)
	{
		if (vec.z > 0.f)
			angles.x = 270.f;
		else
			angles.x = 90.f;

		angles.y = 0.f;
	}
	else
	{
		angles.x = Rad2Deg(atan2(-vec.z, vec.Length2D()));
		angles.y = Rad2Deg(atan2(vec.y, vec.x));

		if (angles.x < 0.f)
			angles.x += 360.f;

		if (angles.y < 0.f)
			angles.y += 360.f;
	}

	angles.z = 0.f;
	//NormalizeAngles(angles);
}

inline void VectorAngles(const Vector &vec, const Vector &up, Vector &angles)
{
	Vector left;
	Cross(up, vec, left);

	left.Normalize();

	float len = vec.Length2D();
	angles.x = Rad2Deg(atan2(-vec.z, len));

	if (len > .001f)
	{
		angles.y = Rad2Deg(atan2(vec.y, vec.x));
		angles.z = Rad2Deg(atan2(left.z, ((left.y * vec.x) - (left.x * vec.y))));
	}
	else
	{
		angles.y = Rad2Deg(atan2(-left.x, left.y));
		angles.z = 0.f;
	}

	//NormalizeAngles(angles);
}

inline void VectorTransform(const Vector &i, const matrix3x4 &matrix, Vector &o)
{
	o.x = i.Dot(Vector(matrix[0][0], matrix[0][1], matrix[0][2])) + matrix[0][3];
	o.y = i.Dot(Vector(matrix[1][0], matrix[1][1], matrix[1][2])) + matrix[1][3];
	o.z = i.Dot(Vector(matrix[2][0], matrix[2][1], matrix[2][2])) + matrix[2][3];
}

inline void MatrixGetColumn(const matrix3x4 &matrix, int i, Vector &o)
{
	o.x = matrix[0][i];
	o.y = matrix[1][i];
	o.z = matrix[2][i];
}

inline void MatrixPosition(const matrix3x4 &matrix, Vector &vec)
{
	MatrixGetColumn(matrix, 3, vec);
}

inline void MatrixAngles(const matrix3x4 &matrix, Vector &angles)
{
	Vector forward, left, up;

	forward[0] = matrix[0][0];
	forward[1] = matrix[1][0];
	forward[2] = matrix[2][0];
	left[0] = matrix[0][1];
	left[1] = matrix[1][1];
	left[2] = matrix[2][1];
	up[2] = matrix[2][2];

	float len2d = forward.Length2D();

	if (len2d > 0.001f)
	{
		angles.x = Rad2Deg(atan2f(-forward.z, len2d));
		angles.y = Rad2Deg(atan2f(forward.y, forward.x));
		angles.z = Rad2Deg(atan2f(left.z, up.z));
	}
	else
	{
		angles.x = Rad2Deg(atan2f(-forward.z, len2d));
		angles.y = Rad2Deg(atan2f(-left.x, left.y));
		angles.z = 0.f;
	}
}

inline void MatrixAngles(const matrix3x4 &matrix, Vector &angles, Vector &vec)
{
	MatrixAngles(matrix, angles);
	MatrixPosition(matrix, vec);
}

inline Vector::Vector()
{
	x = y = z = 0.f;
}

inline Vector::Vector(float ix, float iy, float iz)
{
	x = ix;
	y = iy;
	z = iz;
}

inline Vector Vector::Rotate(const Vector &i) const
{
	Vector o;
	VectorRotate(*this, i, o);

	return o;
}

inline Vector Vector::Angle(Vector* up = 0) //thanks to styles for fixing this bullshit math
{
	if (!x && !y)
		return Vector(0, 0, 0);

	float roll = 0;

	if (up)
	{
		Vector left = (*up).Cross(*this);

		roll = Rad2Deg(atan2f(left.z, (left.y * x) - (left.x * y)));
	}

	return Vector(Rad2Deg(atan2f(-z, sqrtf(x*x + y*y))), Rad2Deg(atan2f(y, x)), roll);
}

inline Vector Vector::Forward()
{
	float cp, cy, sp, sy;

	SinCos(Rad2Deg(x), sp, cp);
	SinCos(Rad2Deg(y), sy, cy);

	return Vector(cp*cy, cp*sy, -sp);
}

inline Vector Vector::Right()
{
	float sp, sy, sr, cp, cy, cr;

	SinCos(Rad2Deg(x), sp, cp);
	SinCos(Rad2Deg(y), sy, cy);
	SinCos(Rad2Deg(z), sr, cr);

	return Vector(-1 * sr*sp*cy + -1 * cr*-sy, -1 * sr*sp*sy + -1 * cr*cy, -1 * sr*cp);
}

inline Vector Vector::Up()
{
	float sp, sy, sr, cp, cy, cr;

	SinCos(Rad2Deg(x), sp, cp);
	SinCos(Rad2Deg(y), sy, cy);
	SinCos(Rad2Deg(z), sr, cr);

	return Vector(cr*sp*cy + -sr*-sy, cr*sp*sy + -sr*cy, cr*cp);
}

inline Vector& Vector::operator = (const Vector &i)
{
	x = i.x;
	y = i.y;
	z = i.z;

	return *this;
}

inline Vector& Vector::operator += (const Vector &i)
{
	x += i.x;
	y += i.y;
	z += i.z;

	return *this;
}

inline Vector& Vector::operator -= (const Vector &i)
{
	x -= i.x;
	y -= i.y;
	z -= i.z;

	return *this;
}

inline Vector& Vector::operator *= (const Vector &i)
{
	x *= i.x;
	y *= i.y;
	z *= i.z;

	return *this;
}

inline Vector& Vector::operator *= (const float i)
{
	x *= i;
	y *= i;
	z *= i;

	return *this;
}

inline Vector& Vector::operator /= (const Vector &i)
{
	x /= i.x;
	y /= i.y;
	z /= i.z;

	return *this;
}

inline Vector& Vector::operator /= (const float i)
{
	x /= i;
	y /= i;
	z /= i;

	return *this;
}

inline Vector Vector::operator + (const Vector &i) const
{
	return Vector(x + i.x, y + i.y, z + i.z);
}

inline Vector Vector::operator - (const Vector &i) const
{
	return Vector(x - i.x, y - i.y, z - i.z);
}

inline Vector Vector::operator / (const Vector &i) const
{
	return Vector(x / (i.x + FLT_EPSILON), y / (i.y + FLT_EPSILON), z / (i.z + FLT_EPSILON));
}

inline Vector Vector::operator / (const float &i) const
{
	return Vector(x / (i + FLT_EPSILON), y / (i + FLT_EPSILON), z / (i + FLT_EPSILON));
}

inline Vector Vector::operator * (const Vector &i) const
{
	return Vector(x * i.x, y * i.y, z * i.z);
}

inline Vector Vector::operator * (const float &i) const
{
	return Vector(x * i, y * i, z * i);
}

inline bool Vector::operator == (const Vector &i) const
{
	if (fabs(i.x - x) < FLT_EPSILON &&
		fabs(i.y - y) < FLT_EPSILON &&
		fabs(i.z - z) < FLT_EPSILON)
	{
		return 1;
	}

	return 0;
}

inline bool Vector::operator != (const Vector &i) const
{
	if (fabs(i.x - x) > FLT_EPSILON &&
		fabs(i.y - y) > FLT_EPSILON &&
		fabs(i.z - z) > FLT_EPSILON)
	{
		return 1;
	}

	return 0;
}

inline float& Vector::operator [] (int index)
{
	return ((float *)this)[index];
}

inline void Vector::Zero()
{
	x = y = z = 0.f;
}

inline bool Vector::IsZero(const float i) const
{
	return (x > -i && x < i && y > -i && y < i && z > -i && z < i);
}

inline float Vector::Length() const
{
	return Sqrt((x * x) + (y * y) + (z * z));
}

inline float Vector::Length2D() const
{
	return Sqrt((x * x) + (y * y) + (z * z));
}

inline float Vector::DistTo(const Vector &i) const
{
	return (*this - i).Length();
}

inline float Vector::Normalize()
{
	float len = Length();
	float mul = 1.f / (len + FLT_EPSILON);

	x = x * mul;
	y = y * mul;
	z = z * mul;

	return len;
}

inline float Vector::Dot(const Vector &i) const
{
	return x * i.x + y * i.y + z * i.z;
}

inline Vector Vector::Cross(const Vector &i) const
{
	return Vector(y * i.z - z * i.y, z * i.x - x * i.z, x * i.y - y * i.x);
}