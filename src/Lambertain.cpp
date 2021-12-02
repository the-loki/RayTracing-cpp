//
// Created by toomimaya on 12/1/21.
//

#include "Lambertain.h"
#include "Hittable.h"
#include "Utils.hpp"

LambertianMaterial::LambertianMaterial(const Color &albedo) : albedo_(albedo) {
}

bool LambertianMaterial::scatter(const Ray &inRay, const HitRecord &hitRecord, Color &attenuation, Ray &scatteredRay) {
    Vector3 scatterDirection = hitRecord.normal + Utils::randomUnitVector3();
    scatteredRay = Ray{hitRecord.point, scatterDirection.normalize()};
    attenuation = albedo_;
    return true;
}
