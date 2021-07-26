//
// Created by Toomimaya on 11/30/21.
//

#pragma once

//
// Created by Toomimaya on 11/30/21.
//

#pragma once

#include <cmath>
#include <array>
#include <cstdlib>
#include <iostream>

template<typename Tp>
class TVector3 {
public:
    TVector3();

    TVector3(Tp v1, Tp v2, Tp v3);

    Tp operator[](int index) const;

    Tp &operator[](int index);

    TVector3 operator-() const {
        return {-x, -y, -z};
    }

    TVector3 &operator+=(const TVector3 &a);

    TVector3 &operator-=(const TVector3 &a);

    TVector3 &operator*=(double a);

    TVector3 &operator/=(double a);

    TVector3<Tp> normalize();

    [[nodiscard]] double length() const;

    [[nodiscard]] double lengthSquared() const;

public:
    union {
        struct {
            Tp x, y, z;
        };

        struct {
            Tp r, g, b;
        };

        struct {
            Tp v1, v2, v3;
        };

        std::array<Tp, 3> store;
    };
};

template<typename Tp>
inline TVector3<Tp>::TVector3():v1(0), v2(0), v3(0) {}

template<typename Tp>
inline TVector3<Tp>::TVector3(Tp v1, Tp v2, Tp v3):v1(v1), v2(v2), v3(v3) {}

template<typename Tp>
inline Tp TVector3<Tp>::operator[](int index) const {
    return store[index];
}

template<typename Tp>
inline Tp &TVector3<Tp>::operator[](int index) {
    return store[index];
}

template<typename Tp>
inline TVector3<Tp> &TVector3<Tp>::operator+=(const TVector3 &a) {
    store[0] += a.v1;
    store[1] += a.v2;
    store[2] += a.v3;
    return *this;
}

template<typename Tp>
inline TVector3<Tp> &TVector3<Tp>::operator-=(const TVector3 &a) {
    store[0] -= a.v1;
    store[1] -= a.v2;
    store[2] -= a.v3;
    return *this;
}

template<typename Tp>
inline TVector3<Tp> &TVector3<Tp>::operator*=(const double a) {
    store[0] *= a;
    store[1] *= a;
    store[2] *= a;
    return *this;
}

template<typename Tp>
inline TVector3<Tp> &TVector3<Tp>::operator/=(const double a) {
    return *this *= (1 / a);
}

template<typename Tp>
double TVector3<Tp>::length() const {
    return std::sqrt(lengthSquared());
}

template<typename Tp>
double TVector3<Tp>::lengthSquared() const {
    return v1 * v1 + v2 * v2 + v3 * v3;
}

template<typename Tp>
inline TVector3<Tp> TVector3<Tp>::normalize() {
    return (*this / length());
}

template<typename Tp>
inline std::ostream &operator<<(std::ostream &out, const TVector3<Tp> &v) {
    return out << v.v1 << " " << v.v2 << " " << v.v3;
}

template<typename Tp>
inline TVector3<Tp> operator+(const TVector3<Tp> &u, const TVector3<Tp> &v) {
    return {u.v1 + v.v1, u.v2 + v.v2, u.v3 + v.v3};
}

template<typename Tp>
inline TVector3<Tp> operator-(const TVector3<Tp> &u, const TVector3<Tp> &v) {
    return {u.v1 - v.v1, u.v2 - v.v2, u.v3 - v.v3};
}

template<typename Tp>
inline TVector3<Tp> operator*(const TVector3<Tp> &u, const TVector3<Tp> &v) {
    return {u.v1 * v.v1, u.v2 * v.v2, u.v3 * v.v3};
}

template<typename Tp>
inline TVector3<Tp> operator*(double a, const TVector3<Tp> &u) {
    return {a * u.v1, a * u.v2, a * u.v3};
}

template<typename Tp>
inline TVector3<Tp> operator*(const TVector3<Tp> &u, double a) {
    return a * u;
}

template<typename Tp>
inline TVector3<Tp> operator/(const TVector3<Tp> &u, double a) {
    return (1 / a) * u;
}

template<typename Tp>
inline double dot(const TVector3<Tp> &u, const TVector3<Tp> &v) {
    return u.v1 * v.v1 + u.v2 * v.v2 + u.v3 * v.v3;
}

template<typename Tp>
inline TVector3<Tp> cross(const TVector3<Tp> &u, const TVector3<Tp> &v) {
    return TVector3<Tp>{u.v2 * v.v3 - u.v3 * v.v2, u.v3 * v.v1 - u.v1 * v.v3, u.v1 * v.v2 - u.v2 * v.v1};
}

using Color = TVector3<double>;
using Point3 = TVector3<double>;
using Vector3 = TVector3<double>;



