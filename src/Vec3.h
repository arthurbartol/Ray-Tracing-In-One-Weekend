#pragma once

#include <iostream>
#include <cmath>

#include "MathCommon.h"

class Vec3
{
public:
    Vec3()
    {
        this->x = 0.0;
        this->y = 0.0;
        this->z = 0.0;
    }

    Vec3(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vec3(double t)
    {
        this->x = t;
        this->y = t;
        this->z = t;
    }

    //
    // Operator overloadings
    //
    Vec3 operator-() const
    {
        return Vec3(-x, -y, -z);
    }

    Vec3& operator+=(const Vec3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3& operator*=(const double t)
    {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    Vec3& operator/=(const double t)
    {
        return *this *= 1 / t;
    }

    //
    // Methods
    //
    double length() const
    {
        return std::sqrt(length2());
    }

    double length2() const
    {
        return x * x + y * y + z * z;
    }

    inline static Vec3 random()
    {
        return Vec3(randomDouble(), randomDouble(), randomDouble());
    }

    inline static Vec3 random(double min, double max)
    {
        return Vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
    }

public:
    double x, y, z;
};

//
// Vec3 utility functions
//
inline std::ostream& operator<<(std::ostream &out, const Vec3& v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
    return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
    return Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
    return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline Vec3 operator*(double t, const Vec3& v)
{
    return Vec3(t*v.x, t*v.y, t*v.z);
}

inline Vec3 operator*(const Vec3& v, double t)
{
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t)
{
    return (1 / t) * v;
}

inline double dot(const Vec3 &u, const Vec3 &v)
{
    return u.x * v.x +
           u.y * v.y +
           u.z * v.z;
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v)
{
    return Vec3(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}

inline Vec3 normalized(Vec3 v)
{
    return v / v.length();
}

Vec3 randomInUnitSphere()
{
    while (true)
    {
        Vec3 p = Vec3::random(-1.0, 1.0);
        if (p.length2() >= 1)
            continue;
        return p;
    }
}
