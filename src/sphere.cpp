#include "sphere.h"
#include "material.h"
#include "primitive.h"
#include "ray.h"
#include <memory>

HitRecord Sphere::raycast(const Ray &ray) {
  Vec3 oc = ray.origin() - orig;

  double a = dotProduct(ray.direction(), ray.direction());
  double b = 2 * dotProduct(ray.direction(), oc);
  double c = dotProduct(oc, oc) - rad * rad;

  double discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    return HitRecord{false};
  }
  // std::clog << "discriminant not 0" << '\n';
  double t = (-b - std::sqrt(discriminant)) / (2.0 * a);
  if (t < 1e-6) {
    return HitRecord{false};
  }
  // if (t > 0) {
  // std:: clog << "t value is " << t << '\n';
  // }
  Vec3 point = ray.parametric(t);
  // std::clog << "point of intersection is " << point << '\n';
  Vec3 normal = normalise(point - orig);
  return HitRecord{true, t, point, normal, this->material.get()};
}
