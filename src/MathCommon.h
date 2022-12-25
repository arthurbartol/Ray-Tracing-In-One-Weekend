#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double MY_INFINITY = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// Utility functions
inline double deg2rad(double degrees)
{
    return degrees * PI / 180.0;
}

inline double randomDouble()
{
    // Returns a random real in [0,1]
    return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max)
{
    // Returns a random real in [min,max]
    return min + (max - min) * randomDouble();
}

inline double clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Common headers
#include "Ray.h"
#include "Vec3.h"
