#include "bounding_box.h"
#include "primitive.h"
#include "utility.h"

BoundingBox::BoundingBox(Vec3 min, Vec3 max) : min{min}, max{max} {};

HitRecord BoundingBox::raycast(const Ray &ray) {
  std::optional<HitRecord> record = slabIntersection(min, max, ray);
  if (!record) {
    return HitRecord{false};
  }

  record->material = this->material.get();
  return record.value();
}
