#pragma once

#include "Ray.h"

struct HitRecord
{
    Vec3 point;
    Vec3 normal;
    double t;
    bool frontFace;

    inline void setFaceNormal(const Ray& ray, const Vec3& outwardNormal)
    {
        frontFace = dot(ray.direction, outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
public:
    virtual bool hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRec) const = 0;
};
