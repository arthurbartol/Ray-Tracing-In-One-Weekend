#pragma once

#include <vector>
#include <memory>

#include "Hittable.h"

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable
{
public:
    HittableList() {}
    HittableList(shared_ptr<Hittable> object)
    {
        add(object);
    }

    //
    // Methods
    //
    void clear()
    {
        objects.clear();
    }

    void add(shared_ptr<Hittable> object)
    {
        objects.push_back(object);
    }

    bool hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRec) const override
    {
        HitRecord tempRec;
        bool hitAnything = false;
        double closestSoFar = tMax;

        for (const auto& object : objects)
        {
            if (object->hit(ray, tMin, closestSoFar, tempRec))
            {
                hitAnything = true;
                closestSoFar = tempRec.t;
                hitRec = tempRec;
            }
        }

        return hitAnything;
    }

public:
    std::vector<shared_ptr<Hittable>> objects;
};
