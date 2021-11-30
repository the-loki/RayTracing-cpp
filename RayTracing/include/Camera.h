//
// Created by MSI-PC on 2021/12/1.
//

#pragma once

#include "Vector3.hpp"
#include "Ray.h"

class Camera {
public:
    Camera(double aspectRatio, double vpHeight, double focalLength, Point3 origin);

    Ray getRay(double u, double v);

private:
    Point3 origin_;
    Point3 lowerLeftCorner_;
    Vector3 vertical_;
    Vector3 horizontal_;
};
