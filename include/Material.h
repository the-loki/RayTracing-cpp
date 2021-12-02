//
// Created by Toomimaya on 12/1/21.
//

#pragma once

#include "Ray.h"

struct HitRecord;

class Material {
public:
    virtual bool scatter(const Ray &inRay, const HitRecord &hitRecord, Color &attenuation, Ray &scatteredRay) = 0;
};