#pragma once

#include "Vec3.h"

class Ray
{
public:
    Ray() {}
    Ray(const Vec3& origin, const Vec3& direction)
        : origin(origin), direction(direction) {}

    //
    // Methods
    //  
    Vec3 at(double t) const
    {
        return origin + t * direction;
    }

public:
    Vec3 origin;
    Vec3 direction;
};
