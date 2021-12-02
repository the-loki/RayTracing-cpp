//
// Created by MSI-PC on 2021/12/2.
//

#include "DielectricMaterial.h"
#include "Hittable.h"

DielectricMaterial::DielectricMaterial(double refIdx) : refIdx_(refIdx) {
}

bool DielectricMaterial::scatter(const Ray &inRay, const HitRecord &hitRecord, Color &attenuation, Ray &scatteredRay) {
    attenuation = Color{1.0, 1.0, 1.0};


    return false;
}
