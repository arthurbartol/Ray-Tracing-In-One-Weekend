#pragma once

#include "Vec3.h"

class Ray
{
public:
    Ray()
    {
        this->origin = Vec3(0.0);
        this->direction = Vec3(0.0);
    }

    Ray(const Vec3& origin, const Vec3& direction)
    {
        this->origin = origin;
        this->direction = direction;
    }

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
