#include <iostream>

#include "MathCommon.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"

Vec3 rayColor(const Ray& ray, const Hittable& world)
{
    HitRecord hitRec;
    if (world.hit(ray, 0.0, MY_INFINITY, hitRec))
        return 0.5 * (hitRec.normal + Vec3(1.0, 1.0, 1.0));
    Vec3 normalizedDir = normalized(ray.direction);
    double t = 0.5 * (normalizedDir.y + 1.0);
    return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    const double ASPECT_RATIO = 16.0 / 9.0;
    const int WIDTH = 800;
    const int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);

    // World
    HittableList world;
    world.add(make_shared<Sphere>(Vec3(0.0, 0.0, -1.0), 0.5));
    world.add(make_shared<Sphere>(Vec3(0.0, -100.5, -1.0), 100.0));

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
            Vec3 pixelColor = rayColor(ray, world);

            writeColor(std::cout, pixelColor);
        }
    }

    std::cerr << "\nDone.\n";
}
