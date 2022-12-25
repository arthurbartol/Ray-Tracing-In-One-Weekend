#include <iostream>

#include "Color.h"
#include "Ray.h"
#include "Vec3.h"

bool hitSphere(const Vec3& center, double radius, const Ray& ray)
{
    Vec3 oc = ray.origin - center;
    double a = dot(ray.direction, ray.direction);
    double b = 2.0 * dot(oc, ray.direction);
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

Vec3 rayColor(const Ray& ray)
{
    if (hitSphere(Vec3(0.0, 0.0, -1.0), 0.5, ray))
        return Vec3(1.0, 0.0, 0.0);
    Vec3 normalizedDir = normalized(ray.direction);
    double t = 0.5 * (normalizedDir.y + 1.0);
    return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    const double ASPECT_RATIO = 16.0 / 9.0;
    const int WIDTH = 400;
    const int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);

    // Simple camera
    double viewportHeight = 2.0;
    double viewportWidth = ASPECT_RATIO * viewportHeight;
    double focalLength = 1.0;

    Vec3 origin = Vec3(0.0, 0.0, 0.0);
    Vec3 horizontal = Vec3(viewportWidth, 0.0, 0.0);
    Vec3 vertical = Vec3(0.0, viewportHeight, 0.0);
    Vec3 lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0.0, 0.0, focalLength);

    // Render
    std::cout << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";

    for (int y = HEIGHT - 1; y >= 0; y--)
    {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
        for (int x = 0; x < WIDTH; x++)
        {
            double u = (double) x / (WIDTH - 1);
            double v = (double) y / (HEIGHT - 1);

            Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
            Vec3 pixelColor = rayColor(ray);

            writeColor(std::cout, pixelColor);
        }
    }

    std::cerr << "\nDone.\n";
}
