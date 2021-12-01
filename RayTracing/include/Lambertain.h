//
// Created by toomimaya on 12/1/21.
//

#pragma once

#include "Material.h"

class LambertianMaterial : public Material{
public:
    explicit LambertianMaterial(const Color &albedo);

    bool scatter(const Ray &inRay, const HitRecord &hitRecord, Color &attenuation, Ray &scatteredRay) override;
protected:
    Color albedo_;
};
