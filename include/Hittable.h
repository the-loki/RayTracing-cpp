//
// Created by Toomimaya on 11/30/21.
//

#pragma once

#include "Ray.h"
#include "Vector3.hpp"
#include "Material.h"
#include <vector>
#include <memory>

struct HitRecord {
    double distance{0};
    bool frontFace{false};
    Point3 point{};
    Vector3 normal{};
    std::shared_ptr<Material> material;

    inline void setFaceNormal(const Ray &ray, const Vector3 &outWardNormal) {
        frontFace = dot(ray.direction(), outWardNormal) < 0;//当未使用折射的时候，仍然有部分同向，此处有一点不理解
        normal = frontFace ? outWardNormal : -outWardNormal;
    }
};

class Hittable {
public:
    Hittable() = default;

    virtual bool hit(const Ray &ray, double distanceMin, double distanceMax, HitRecord &hitRecord) const = 0;
};

class HittableList : public Hittable {
public:
    HittableList() = default;

    explicit HittableList(const std::shared_ptr<Hittable> &objects);

    bool hit(const Ray &ray, double distanceMin, double distanceMax, HitRecord &hitRecord) const override;

    void add(const std::shared_ptr<Hittable> &object);

    void clear();

public:
    std::vector<std::shared_ptr<Hittable>> objects;
};

