#include <iostream>

#include "Vec3.h"
#include "Ray.h"
#include "Camera.h"
#include "Hittable.h"
#include "Sphere.h"
#include "HittableList.h"

#include "MathCommon.h"
#include "Image.h"

Vec3 rayColor(const Ray& ray, const Hittable& world, int depth)
{
    HitRecord hitRec;

    // If we've exceeded the ray bounce limit, no more light is gathered
    if (depth <= 0)
        return Vec3(0.0);

    if (world.hit(ray, 0.0, MY_INFINITY, hitRec))
    {
        Vec3 target = hitRec.point + hitRec.normal + randomInUnitSphere();
        return 0.5 * rayColor(Ray(hitRec.point, target - hitRec.point), world, depth - 1);
    }
        
    Vec3 normalizedDir = normalized(ray.direction);
    double t = 0.5 * (normalizedDir.y + 1.0);
    return (1.0 - t) * Vec3(1.0) + t * Vec3(0.5, 0.7, 1.0);
}

int main()
{
    // Settings
    const double ASPECT_RATIO = 16.0 / 9.0;
    const int WIDTH = 640;
    const int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);

    const int SAMPLES_PER_PIXEL = 20;
    const int MAX_DEPTH = 50;

    // Image
    Image img("build/image.ppm");
    img.createPPM(WIDTH, HEIGHT);

    // World
    HittableList world;
    world.add(make_shared<Sphere>(Vec3(0.0, 0.0, -1.0), 0.5));
    world.add(make_shared<Sphere>(Vec3(0.0, -100.5, -1.0), 100.0));

    // Camera
    Camera cam;

    // Render
    for (int y = HEIGHT - 1; y >= 0; y--)
    {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
        for (int x = 0; x < WIDTH; x++)
        {
            Vec3 pixelColor(0.0);
            for (int s = 0; s < SAMPLES_PER_PIXEL; s++)
            {
                double u = (x + randomDouble()) / (WIDTH - 1);
                double v = (y + randomDouble()) / (HEIGHT - 1);

                Ray ray = cam.getRay(u, v);
                pixelColor += rayColor(ray, world, MAX_DEPTH);
            }

            img.write(pixelColor, SAMPLES_PER_PIXEL);
        }
    }

    std::cerr << "\nDone.\n";
}
