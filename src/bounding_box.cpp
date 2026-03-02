#include "bounding_box.h"
#include "primitive.h"
#include "utility.h"

BoundingBox::BoundingBox(Vec3 min, Vec3 max) : min{min}, max{max} {};

HitRecord BoundingBox::raycast(const Ray &ray) {
  Vec3 normal{};
  std::optional<double> t = slabIntersection(min, max, ray, normal);
  if (!t) {
    return HitRecord{false};
  }
  double t_val = t.value();
  HitRecord record = {true, t_val, ray.parametric(t_val), normal,
                      this->material.get()};
  return record;
}

Vec3 BoundingBox::getMin() { return min; }
Vec3 BoundingBox::getMax() { return max; }
Vec3 BoundingBox::getCentre() { return 0.5 * (min + max); }
