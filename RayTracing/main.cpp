#include "Ray.h"
#include "Camera.h"
#include "Sphere.h"
#include "Hittable.h"
#include "Utils.hpp"


Color rayColor(const Ray &ray, const Hittable &world) {
    HitRecord hitRecord;
    if (world.hit(ray, 0, Utils::Infinity, hitRecord)) {
        return 0.5 * (hitRecord.normal + Color{1, 1, 1});
    }

    Vector3 direction = ray.direction().normalize();
    double t = 0.5 * (direction.y + 1.0);
    return (1.0 - t) * Color{1, 1, 1} + t * Color{0.5, 0.7, 1.0};
}


int main() {
    const double aspectRatio = 16.0 / 9.0;
    const int imageWidth = 10;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplePerPixel = 100;

    HittableList world;
    world.add(std::make_shared<Sphere>(Point3{0, 0, -1}, 0.5));
    world.add(std::make_shared<Sphere>(Point3{0, -100.5, -1}, 100));
    Camera camera(aspectRatio, 2.0, 1.0, Point3{0, 0, 0});

    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
    for (int y = imageHeight - 1; y >= 0; --y) {
        for (int x = 0; x < imageWidth; ++x) {
            Color pixelColor(0, 0, 0);
            for (int i = 0; i < samplePerPixel; ++i) {
                auto u = (x + Utils::randomDouble()) / (imageWidth - 1);
                auto v = (y + Utils::randomDouble()) / (imageHeight - 1);
                Ray ray = camera.getRay(u, v);
                pixelColor += rayColor(ray, world);
            }

            writeColor(std::cout, pixelColor, samplePerPixel);
        }
    }


    return 0;
}
