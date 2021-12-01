//
// Created by MSI-PC on 2021/12/1.
//

#pragma once

#include "Hittable.h"

class Sphere : public Hittable {
public:
    Sphere() = default;

    Sphere(const Point3 &center, double radius);

    bool hit(const Ray &ray, double distanceMin, double distanceMax, HitRecord &hitRecord) const override;

    Point3 randomPointInSphere() const;

protected:
    Point3 center_;
    double radius_;
};

