#pragma once

#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable
{
public:
    Sphere() {}
    Sphere(Vec3 center, double radius) : center(center), radius(radius) {}

    //
    // Methods
    //
    bool hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRec) const override
    {
        Vec3 oc = ray.origin - center;
        double a = ray.direction.length2();
        double halfb = dot(oc, ray.direction);
        double c = oc.length2() - radius * radius;

        double discriminant = halfb * halfb - a * c;
        if (discriminant < 0.0)
            return false;
        double sqrtDisc = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range
        double root = (-halfb - sqrtDisc) / a;
        if (root < tMin || root > tMax)
        {
            root = (-halfb + sqrtDisc) / a;
            if (root < tMin || root > tMax)
                return false;
        }

        hitRec.t = root;
        hitRec.point = ray.at(hitRec.t);
        Vec3 outwardNormal = (hitRec.point - center) / radius;
        hitRec.setFaceNormal(ray, outwardNormal);

        return true;
    }

public:
    Vec3 center;
    double radius;
};
