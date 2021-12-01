#include "Ray.h"
#include "Camera.h"
#include "Sphere.h"
#include "Hittable.h"
#include "Utils.hpp"
#include "stb_image_write.h"

Color rayColor(const Ray &ray, const Hittable &world, int depth) {
    if (depth <= 0) {
        return Color{0.0, 0.0, 0.0};
    }

    HitRecord hitRecord;
    if (world.hit(ray, 0.001, Utils::Infinity, hitRecord)) {
        Sphere sphere(hitRecord.point + hitRecord.normal, 1.0);
        auto target = sphere.randomPointInSphere();
        return 0.5 * rayColor(Ray{hitRecord.point, target - hitRecord.point}, world, depth - 1);
    }

    Vector3 direction = ray.direction().normalize();
    double t = 0.5 * (direction.y + 1.0);
    return (1.0 - t) * Color{1, 1, 1} + t * Color{0.5, 0.7, 1.0};
}


int main() {
    const int imageWidth = 400;
    const double aspectRatio = 16.0 / 9.0;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplePerPixel = 100;
    const int rayReflectionTimes = 50;

    HittableList world;
    world.add(std::make_shared<Sphere>(Point3{0, 0, -1}, 0.5));
    world.add(std::make_shared<Sphere>(Point3{0, -100.5, -1}, 100));
    Camera camera(aspectRatio, 2.0, 1.0, Point3{0, 0, 0});
    std::vector<std::uint8_t> imgData;

    for (int y = 0; y < imageHeight; ++y) {
        for (int x = 0; x < imageWidth; ++x) {
            Color pixelColor(0, 0, 0);
            for (int i = 0; i < samplePerPixel; ++i) {
                auto u = (x + Utils::randomDouble()) / (imageWidth - 1);
                auto v = (y + Utils::randomDouble()) / (imageHeight - 1);
                Ray ray = camera.getRay(u, v);
                pixelColor += rayColor(ray, world, rayReflectionTimes);
            }

            writeColor(imgData, pixelColor, samplePerPixel);
        }
    }

    stbi_flip_vertically_on_write(true);
    stbi_write_bmp("../image.bmp", imageWidth, imageHeight, 3, imgData.data());
    return 0;
}
