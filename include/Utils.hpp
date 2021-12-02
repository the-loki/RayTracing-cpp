//
// Created by Toomimaya on 11/30/21.
//

#pragma once

#include "Vector3.hpp"
#include <cmath>
#include <random>

class Utils {
public:
    static double randomDouble();

    static double randomDouble(double min, double max);

    static double degreesToRadians(double degrees);

    static double clamp(double value, double min, double max);

    static Vector3 randomVector3();

    static Vector3 randomUnitVector3();

    static Vector3 randomVector3(double min, double max);

    static Vector3 reflect(const Vector3 &in, const Vector3 &n);

    static Vector3 refract(const Vector3 &in, const Vector3 &n, double e);

public:
    inline const static double Pi = 3.1415926535897932385;
    inline const static double Infinity = std::numeric_limits<double>::infinity();
};

inline double Utils::degreesToRadians(double degrees) {
    return degrees * Pi / 180;
}

inline double Utils::randomDouble() {
    static std::random_device device;
    static std::mt19937 generator(device());
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

inline double Utils::randomDouble(double min, double max) {
    return min + (max - min) * randomDouble();
}

inline double Utils::clamp(double value, double min, double max) {
    if (value < min)return min;
    if (value > max) return max;

    return value;
}

inline Vector3 Utils::randomVector3() {
    return {randomDouble(), randomDouble(), randomDouble()};
}

inline Vector3 Utils::randomVector3(double min, double max) {
    return {randomDouble(min, max), randomDouble(min, max), randomDouble(min, max)};
}

inline Vector3 Utils::randomUnitVector3() {
    auto a = randomDouble(0, 2 * Pi);
    auto z = randomDouble(-1, 1);
    auto r = sqrt(1 - z * z);
    return {r * cos(a), r * sin(a), z};
}

inline Vector3 Utils::reflect(const Vector3 &in, const Vector3 &n) {
    return in - 2 * dot(in, n) * n;
}

inline Vector3 Utils::refract(const Vector3 &in, const Vector3 &n, double e) {
    auto inNormalized = in.normalize();
    auto cosTheta = dot(-inNormalized, n);
    auto l2 = (inNormalized + n * cosTheta) * e;
    auto l1 = -n * sqrt(std::abs(1.0 - l2.lengthSquared()));
    return l1 + l2;
}

inline void writeColor(std::vector<std::uint8_t> &imgData, Color pixelColor, int samplesPerPixel) {
    auto[r, g, b] = pixelColor.store;
    const auto scale = 1.0 / samplesPerPixel;

    //Gamma校正
    r = sqrt(r * scale);
    g = sqrt(g * scale);
    b = sqrt(b * scale);

    imgData.push_back(static_cast<std::uint8_t>(256 * Utils::clamp(r, 0.0, 0.999)));
    imgData.push_back(static_cast<std::uint8_t>(256 * Utils::clamp(g, 0.0, 0.999)));
    imgData.push_back(static_cast<std::uint8_t>(256 * Utils::clamp(b, 0.0, 0.999)));
}
