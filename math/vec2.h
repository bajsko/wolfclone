/*
*  WOLFCLONE
*  MODULE: Math
*
*  vec2.h
*      2-D vector class
*
*  Created on 18-02-2017.
*  Copyright C Klas Henriksson 2017. All rights reserved
*/

#ifndef vec2_h
#define vec2_h

template<typename T>
class Vec2 {
public:

	Vec2() : x(T(0)), y(T(0)) {}
	Vec2(T xx) : x(xx), y(xx) {}
	Vec2(T xx, T yy) : x(xx), y(yy) {}
	Vec2(const Vec2<T>& r) : x(r.x), y(r.y) {}

	Vec2<T>& operator = (const Vec2<T>& rhs)
	{
		if (this == &rhs)
			return *this;

		this->x = rhs.x;
		this->y = rhs.y;

		return *this;
	}

	Vec2<T> operator + (const Vec2<T> &v) const { return Vec2<T>(x + v.x, y + v.y); }
	Vec2<T> operator - (const Vec2<T> &v) const { return Vec2<T>(x - v.x, y - v.y); }
	Vec2<T> operator * (const Vec2<T> &v) const { return Vec2<T>(x * v.x, y * v.y); }
	Vec2<T> operator * (const T &r) const { return Vec2<T>(x * r, y * r); }
	Vec2<T>& operator *= (const T &r) { x *= r, y *= r; return *this; }

	void operator += (const Vec2<T> &v) { x += v.x; y += v.y; }
    void operator -= (const Vec2<T> &v) { x -= v.x; y -= v.y; }

	T length() const { return (x * x + y * y); }
	T lengthSquared() const { return sqrt((x * x + y * y)); }

	Vec2<T>& normalize()
	{
		float len = lengthSquared();
		float invLen = 1 / len;

		x *= invLen;
		y *= invLen;

		return *this;
	}

	T dot(const Vec2<T>& v) const
	{
		return x * v.x + y * v.y;
	}

	T x, y;
};

typedef Vec2<float> vec2f;
typedef Vec2<double> vec2d;

class Vec2Util
{
public:
	template<typename T>
	static void debug_print(const Vec2<T>& v)
	{
		std::stringstream s;
		s << "{" << v.x << ":" << v.y << "}";
		std::cout << s.str() << std::endl;
	}
};

#endif
