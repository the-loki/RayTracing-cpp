//
// Created by Toomimaya on 11/30/21.
//

#include <cmath>
#include <random>

class Utils {
public:
    static double randomDouble();

    static double randomDouble(double min, double max);

    static double degreesToRadians(double degrees);

    static double clamp(double value, double min, double max);

public:
    inline const static double Pi = 3.1415926535897932385;
    inline const static double Infinity = std::numeric_limits<double>::infinity();
};

inline double Utils::degreesToRadians(double degrees) {
    return degrees * Pi / 180;
}

double Utils::randomDouble() {
    static std::random_device device;
    static std::mt19937 generator(device());
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

double Utils::randomDouble(double min, double max) {
    return min + (max - min) * randomDouble();
}

double Utils::clamp(double value, double min, double max) {
    if (value < min)return min;
    if (value > max) return max;

    return value;
}


void writeColor(std::ostream &out, Color pixelColor, int samplesPerPixel) {
    auto[r, g, b] = pixelColor.store;
    const auto scale = 1.0 / samplesPerPixel;

    r *= scale;
    g *= scale;
    b *= scale;

    out << static_cast<int>(256 * Utils::clamp(r, 0.0, 0.999)) << " "
        << static_cast<int>(256 * Utils::clamp(g, 0.0, 0.999)) << " "
        << static_cast<int>(256 * Utils::clamp(b, 0.0, 0.999)) << "\n";
}
