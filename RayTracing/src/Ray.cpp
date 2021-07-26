//
// Created by Toomimaya on 11/30/21.
//

#include "Ray.h"

Vector3 Ray::direction() const {
    return direction_;
}

Point3 Ray::origin() const {
    return origin_;
}

Point3 Ray::at(double length) const {
    return origin_ * length * direction_;
}

Ray::Ray(const Point3 &origin, const Vector3 &direction) : origin_(origin), direction_(direction) {}
