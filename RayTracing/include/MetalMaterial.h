//
// Created by toomimaya on 12/1/21.
//

#pragma once

#include "Material.h"

class MetalMaterial : public Material {
public:
    explicit MetalMaterial(const Color &albedo, double fuzz);

    bool scatter(const Ray &inRay, const HitRecord &hitRecord, Color &attenuation, Ray &scatteredRay) override;

public:
    double fuzz_;
    Color albedo_;
};


