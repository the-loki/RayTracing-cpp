//
// Created by MSI-PC on 2021/12/1.
//

#include "Camera.h"
#include "Utils.hpp"

Camera::Camera(Point3 lookFrom,
               Point3 lookAt,
               Vector3 vUp,
               double vFov,
               double aspectRatio,
               double apertureRadius,
               double focusDist)
        : apertureRadius_(apertureRadius) {

    auto theta = Utils::degreesToRadians(vFov);
    auto h = tan(theta / 2);
    auto vh = 2.0 * h;
    auto vw = aspectRatio * vh;

    w_ = (lookFrom - lookAt).normalize();
    u_ = cross(vUp, w_).normalize();
    v_ = cross(w_, u_);

    origin_ = lookFrom;
    vertical_ = focusDist * vh * v_;
    horizontal_ = focusDist * vw * u_;
    lowerLeftCorner_ = origin_ - horizontal_ / 2 - vertical_ / 2 - focusDist * w_;
}

Ray Camera::getRay(double s, double t) {//景深的原理还有些许疑惑
    auto rd = apertureRadius_ * Utils::randomInUnitDisk();//从圆盘随机发射射线
    auto offset = u_ * rd.x + v_ * rd.y;
    return Ray{origin_ + offset, lowerLeftCorner_ + s * horizontal_ + t * vertical_ - origin_ - offset};
}
