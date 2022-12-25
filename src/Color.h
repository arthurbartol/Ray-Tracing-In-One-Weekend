#pragma once

#include <iostream>

#include "Vec3.h"

void writeColor(std::ostream& out, Vec3 pixelColor, int samplesPerPixel)
{
    double r = pixelColor.x;
    double g = pixelColor.y;
    double b = pixelColor.z;

    // Divide the color by the number of samples
    double scale = 1.0 / samplesPerPixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}
