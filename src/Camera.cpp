//
// Created by MSI-PC on 2021/12/1.
//

#include "Camera.h"

Camera::Camera(double aspectRatio, double vpHeight, double focalLength, Point3 origin) : origin_(origin) {
    auto vpWidth = aspectRatio * vpHeight;
    vertical_ = {0, vpHeight, 0};
    horizontal_ = {vpWidth, 0, 0};
    lowerLeftCorner_ = origin - horizontal_ / 2 - vertical_ / 2 - Vector3(0, 0, focalLength);
}

Ray Camera::getRay(double u, double v) {
    return Ray{origin_, lowerLeftCorner_ + u * horizontal_ + v * vertical_ - origin_};
}
