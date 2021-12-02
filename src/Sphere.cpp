//
// Created by MSI-PC on 2021/12/1.
//

#include "Sphere.h"

#include <utility>
#include "Utils.hpp"


Sphere::Sphere(const Point3 &center, double radius, std::shared_ptr<Material> material)
        : center_(center), radius_(radius), material_(std::move(material)) {
}

bool Sphere::hit(const Ray &ray, double distanceMin, double distanceMax, HitRecord &hitRecord) const {
    auto centerToOrigin = ray.origin() - center_;
    auto a = ray.direction().lengthSquared();
    auto halfB = dot(ray.direction(), centerToOrigin);
    auto c = centerToOrigin.lengthSquared() - radius_ * radius_;
    auto discriminant = halfB * halfB - a * c;

    const auto setHitRecord = [&hitRecord, &ray](auto &distance, auto &center, auto &material, auto &radius) {
        hitRecord.distance = distance;
        hitRecord.point = ray.at(distance);
        auto normal = (hitRecord.point - center) / radius;//要实现介质空心球，必须使用半径参与计算，直接对向量归一化会使负半径失去作用
        hitRecord.setFaceNormal(ray, normal);
        hitRecord.material = material;
    };

    if (discriminant > 0) {
        auto sqrtD = sqrt(discriminant);
        auto distance = (-halfB - sqrtD) / a;

        if (distance > distanceMin && distance < distanceMax) {
            setHitRecord(distance, center_, material_, radius_);
            return true;
        }

        distance = (-halfB + sqrtD) / a;
        if (distance > distanceMin && distance < distanceMax) {
            setHitRecord(distance, center_, material_, radius_);
            return true;
        }
    }

    return false;
}

Point3 Sphere::randomPointInSphere() const {
    return Utils::randomUnitVector3() * Utils::randomDouble(0, radius_) + center_;
}
