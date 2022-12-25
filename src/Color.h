#pragma once

#include <iostream>

#include "Vec3.h"

void writeColor(std::ostream& out, Vec3 pixelColor)
{
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixelColor.x) << ' '
        << static_cast<int>(255.999 * pixelColor.y) << ' '
        << static_cast<int>(255.999 * pixelColor.z) << '\n';
}
