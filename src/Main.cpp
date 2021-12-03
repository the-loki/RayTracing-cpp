#include "omp.h"
#include "Ray.h"
#include "thread"
#include "Camera.h"
#include "Sphere.h"
#include "Hittable.h"
#include "Utils.hpp"
#include "stb_image_write.h"
#include "Lambertain.h"
#include "MetalMaterial.h"
#include "DielectricMaterial.h"

Color rayColor(const Ray &ray, const Hittable &world, int depth) {
    if (depth <= 0) {
        return Color{0.0, 0.0, 0.0};
    }

    if (HitRecord hitRecord;world.hit(ray, 0.001, Utils::Infinity, hitRecord)) {
        Ray scatteredRay;
        Color attenuation;

        if (hitRecord.material->scatter(ray, hitRecord, attenuation, scatteredRay)) {
            return attenuation * rayColor(scatteredRay, world, depth - 1);
        }

        return Color{0, 0, 0};
    }

    Vector3 direction = ray.direction().normalize();
    double t = 0.5 * (direction.y + 1.0);
    return (1.0 - t) * Color{1, 1, 1} + t * Color{0.5, 0.7, 1.0};
}

HittableList randomWorld() {
    HittableList world;
    auto groundMaterial = std::make_shared<LambertianMaterial>(Color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Point3(0.0, -1000, 0), 1000, groundMaterial));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto r = Utils::randomDouble();
            Point3 center(a + 0.9 * Utils::randomDouble(), 0.2, b + 0.9 * Utils::randomDouble());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphereMaterial;

                if (r < 0.8) {
                    auto albedo = Utils::randomVector3() * Utils::randomVector3();
                    sphereMaterial = std::make_shared<LambertianMaterial>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                } else if (r < 0.95) {
                    auto albedo = Utils::randomVector3();
                    auto fuzz = Utils::randomDouble(0, 0.5);
                    sphereMaterial = std::make_shared<MetalMaterial>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                } else {
                    sphereMaterial = std::make_shared<DielectricMaterial>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }

    auto m1 = std::make_shared<DielectricMaterial>(1.5);
    world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, m1));
    auto m2 = std::make_shared<LambertianMaterial>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, m2));
    auto m3 = std::make_shared<MetalMaterial>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, m3));

    return world;
}

Color calcRayTracing(int x,
                     int y,
                     Camera &camera,
                     const int imageWidth,
                     const int imageHeight,
                     const HittableList &world,
                     const int rayReflectionTimes,
                     const int samplePerPixel) {

    Color pixelColor(0, 0, 0);
    std::vector<Color> colorList(samplePerPixel);

#pragma omp parallel for
    for (int i = 0; i < samplePerPixel; ++i) {
        auto u = (x + Utils::randomDouble()) / (imageWidth - 1);
        auto v = (y + Utils::randomDouble()) / (imageHeight - 1);
        Ray ray = camera.getRay(u, v);
        colorList[i] = rayColor(ray, world, rayReflectionTimes);
    }

    for (int i = 0; i < samplePerPixel; ++i) {
        pixelColor += colorList[i];
    }

    return pixelColor;
}


int main() {
    auto logicCoreNum = static_cast<int>(std::thread::hardware_concurrency());
    omp_set_num_threads(logicCoreNum);

    const int width = 1200;
    const int samplePerPixel = 500;
    const int reflectionTimes = 50;
    const double aspectRatio = 3.0 / 2.0;
    const int height = static_cast<int>(width / aspectRatio);
    HittableList world = randomWorld();

    auto vUp = Vector3(0, 1, 0);
    auto lookAt = Point3(0, 0, 0);
    auto lookFrom = Point3(12, 2, 3);
    auto distToFocus = 10.0;
    Camera cam(lookFrom, lookAt, vUp, 20, aspectRatio, 0.1, distToFocus);
    std::vector<std::uint8_t> imgData;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Color pixelColor = calcRayTracing(x, y, cam, width, height, world, reflectionTimes, samplePerPixel);
            writeColor(imgData, pixelColor, samplePerPixel);
        }

        std::cout << "Current Progress : " << y * 100.0 / height << "%" << std::endl;
    }

    stbi_flip_vertically_on_write(true);
    stbi_write_bmp("../image.bmp", width, height, 3, imgData.data());
    return 0;
}
