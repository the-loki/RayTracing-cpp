//
// Created by MSI-PC on 2021/12/2.
//

#include "DielectricMaterial.h"
#include "Hittable.h"
#include "Utils.hpp"

DielectricMaterial::DielectricMaterial(double refIdx) : refIdx_(refIdx) {
}

bool DielectricMaterial::scatter(const Ray &inRay, const HitRecord &hitRecord, Color &attenuation, Ray &scatteredRay) {
    attenuation = Color{1.0, 1.0, 1.0};
    double e = hitRecord.frontFace ? (1.0 / refIdx_) : refIdx_;
    auto directionNormalized = inRay.direction().normalize();
    auto cosTheta = std::fmin(dot(-directionNormalized, hitRecord.normal), 1.0);
    auto sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

    if (e * sinTheta > 1.0) {
        auto reflected = Utils::reflect(directionNormalized, hitRecord.normal);
        scatteredRay = Ray{hitRecord.point, reflected};
        return true;
    }

    double reflectProb = Utils::schlick(cosTheta, e);
    if (Utils::randomDouble() < reflectProb) {
        auto reflected = Utils::reflect(directionNormalized, hitRecord.normal);
        scatteredRay = Ray{hitRecord.point, reflected};
        return true;
    }

    auto directionRefracted = Utils::refract(directionNormalized, hitRecord.normal, e);
    scatteredRay = Ray{hitRecord.point, directionRefracted};
    return true;
}
