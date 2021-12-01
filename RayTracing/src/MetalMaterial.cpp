//
// Created by Toomimaya on 12/1/21.
//

#include "MetalMaterial.h"
#include "Hittable.h"
#include "Utils.hpp"

MetalMaterial::MetalMaterial(const Color &albedo, double fuzz) : albedo_(albedo), fuzz_(fuzz < 1 ? fuzz : 1) {
}

bool MetalMaterial::scatter(const Ray &inRay, const HitRecord &hitRecord, Color &attenuation, Ray &scatteredRay) {
    auto reflectDirection = Utils::reflect(inRay.direction().normalize(), hitRecord.normal);
    scatteredRay = Ray(hitRecord.point, (reflectDirection + fuzz_ * Utils::randomUnitVector3()).normalize());
    attenuation = albedo_;

    return (dot(scatteredRay.direction(), hitRecord.normal) > 0);
}
