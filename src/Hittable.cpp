//
// Created by Toomimaya on 11/30/21.
//

#include "Hittable.h"

HittableList::HittableList(const std::shared_ptr<Hittable> &objects) {
    add(objects);
}

void HittableList::clear() {
    objects.clear();
}

void HittableList::add(const std::shared_ptr<Hittable> &object) {
    objects.push_back(object);
}

bool HittableList::hit(const Ray &ray, double distanceMin, double distanceMax, HitRecord &hitRecord) const {
    HitRecord localHitRecord;
    bool hitAnything = false;
    double closetSoFar = distanceMax;

    for (const auto &object: objects) {
        if (object->hit(ray, distanceMin, closetSoFar, localHitRecord)) {
            hitAnything = true;
            closetSoFar = localHitRecord.distance;
            hitRecord = localHitRecord;
        }
    }

    return hitAnything;
}