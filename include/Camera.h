//
// Created by MSI-PC on 2021/12/1.
//

#pragma once

#include "Vector3.hpp"
#include "Ray.h"

class Camera {
public:
    Camera(Point3 lookFrom, Point3 lookAt, Vector3 vUp, double aspectRatio, double vFov);

    Ray getRay(double u, double v);

private:
    Point3 origin_;
    Point3 lowerLeftCorner_;
    Vector3 vertical_;
    Vector3 horizontal_;
};
