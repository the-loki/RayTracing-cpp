//
// Created by MSI-PC on 2021/12/2.
//

#include "Material.h"

class DielectricMaterial : public Material {
public:
    explicit DielectricMaterial(double refIdx);

    bool scatter(const Ray &inRay, const HitRecord &hitRecord, Color &attenuation, Ray &scatteredRay) override;

protected:
    double refIdx_;//折射率
};