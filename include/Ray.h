//
// Created by Toomimaya on 11/30/21.
//

#pragma once

#include "Vector3.hpp"

class Ray {
public:
    Ray() = default;

    Ray(const Point3 &origin, const Vector3 &direction);

    [[nodiscard]] Point3 origin() const;

    [[nodiscard]] Vector3 direction() const;

    [[nodiscard]] Point3 at(double length) const;

protected:
    Point3 origin_;
    Vector3 direction_;
};


