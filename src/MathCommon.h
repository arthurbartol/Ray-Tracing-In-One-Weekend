#pragma once

#include <cmath>
#include <limits>
#include <memory>

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

// Common headers
#include "Ray.h"
#include "Vec3.h"
