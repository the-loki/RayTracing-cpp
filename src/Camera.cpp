//
// Created by MSI-PC on 2021/12/1.
//

#include "Camera.h"
#include "Utils.hpp"

Camera::Camera(Point3 lookFrom, Point3 lookAt, Vector3 vUp, double aspectRatio, double vFov) : origin_({0, 0, 0}) {
    auto theta = Utils::degreesToRadians(vFov);
    auto h = tan(theta / 2);
    auto vh = 2.0 * h;
    auto vw = aspectRatio * vh;
    vertical_ = {0, vh, 0};
    horizontal_ = {vw, 0, 0};
    double focalLength = 1.0;
    lowerLeftCorner_ = origin_ - horizontal_ / 2 - vertical_ / 2 - Vector3(0, 0, focalLength);
}

Ray Camera::getRay(double u, double v) {
    return Ray{origin_, lowerLeftCorner_ + u * horizontal_ + v * vertical_ - origin_};
}
