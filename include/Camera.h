//
// Created by MSI-PC on 2021/12/1.
//

#pragma once

#include "Vector3.hpp"
#include "Ray.h"

class Camera {
public:
    Camera(Point3 lookFrom, Point3 lookAt, Vector3 vUp, double vFov, double aspectRatio, double apertureRadius,
           double focusDist);

    Ray getRay(double s, double t);

private:
    Point3 lowerLeftCorner_;
    Vector3 vertical_;
    Vector3 horizontal_;
    Vector3 u_, v_, w_;
    double apertureRadius_;
    Point3 origin_{0, 0, 0};
};
