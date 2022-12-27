#include <iostream>

#include "MathCommon.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"

Vec3 rayColor(const Ray& ray, const Hittable& world)
{
    HitRecord hitRec;
    if (world.hit(ray, 0.0, MY_INFINITY, hitRec))
        return 0.5 * (hitRec.normal + Vec3(1.0, 1.0, 1.0));
    Vec3 normalizedDir = normalized(ray.direction);
    double t = 0.5 * (normalizedDir.y + 1.0);
    return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

void writePPM(std::ostream& out, Vec3 pixelColor, int samplesPerPixel)
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

int main()
{
    // Image
    const double ASPECT_RATIO = 16.0 / 9.0;
    const int WIDTH = 800;
    const int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);
    const int SAMPLES_PER_PIXEL = 100;

    // World
    HittableList world;
    world.add(make_shared<Sphere>(Vec3(0.0, 0.0, -1.0), 0.5));
    world.add(make_shared<Sphere>(Vec3(0.0, -100.5, -1.0), 100.0));

    // Camera
    Camera cam;

    // Render
    std::cout << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";

    for (int y = HEIGHT - 1; y >= 0; y--)
    {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
        for (int x = 0; x < WIDTH; x++)
        {
            Vec3 pixelColor(0.0, 0.0, 0.0);
            for (int s = 0; s < SAMPLES_PER_PIXEL; s++)
            {
                double u = (x + randomDouble()) / (WIDTH - 1);
                double v = (y + randomDouble()) / (HEIGHT - 1);

                Ray ray = cam.getRay(u, v);
                pixelColor += rayColor(ray, world);
            }

            writePPM(std::cout, pixelColor, SAMPLES_PER_PIXEL);
        }
    }

    std::cerr << "\nDone.\n";
}
