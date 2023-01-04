#pragma once

#include <iostream>
#include <fstream>

#include "Vec3.h"
#include "MathCommon.h"

class Image
{
public:
	Image(const char* filepath)
	{
		file.open(filepath);
	}

	~Image()
	{
		file.close();
	}

	//
	// Methods
	//
	void createPPM(int width, int height)
	{
		file << "P3\n" << width << " " << height << "\n255\n";
	}

	void write(Vec3 pixelColor, int samplesPerPixel)
	{
		double r = pixelColor.x;
		double g = pixelColor.y;
		double b = pixelColor.z;

		// Divide the color by the number of samples
		double scale = 1.0 / samplesPerPixel;
		r *= sqrt(scale * r);
		g *= sqrt(scale * g);
		b *= sqrt(scale * b);

		// Write the translated [0,255] value of each color component
		file << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
			 << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
			 << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
	}

public:
	std::ofstream file;
};
