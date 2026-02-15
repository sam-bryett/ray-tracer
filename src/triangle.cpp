#include "triangle.h"
#include "primitive.h"
#include "ray.h"

HitRecord Triangle::raycast(const Ray &ray) {
  // Moller–Trumbore intersection algorithm
  Vec3 edge1 = p2 - p1;
  Vec3 edge2 = p3 - p1;
  Vec3 pvec = crossProduct(ray.direction(), edge2);
  Vec3 normal = crossProduct(edge1, edge2);
  // Epsilon to account for floating point precision errors
  double epsilon = 1e-6;

  // Check that the ray isnt parallel
  double det = dotProduct(edge1, pvec);
  if (fabs(det) <= epsilon)
    return HitRecord{false};

  double inv_det = 1.0 / det;

  // Use barycentric coordinates to check if point lies outside triangle
  Vec3 tvec = ray.origin() - p1;
  double u = dotProduct(tvec, pvec) * inv_det;
  if (u < 0 || u > 1)
    return HitRecord{false};

  Vec3 qvec = crossProduct(tvec, edge1);
  double v = dotProduct(ray.direction(), qvec) * inv_det;
  if (v < 0 || u + v > 1)
    return HitRecord{false};

  double t = dotProduct(edge2, qvec) * inv_det;
  if (t <= epsilon)
    return HitRecord{false};

  // Flip normal so it faces the ray
  normal = normalise(normal);
  if (dotProduct(normal, ray.direction()) > 0) {
    normal = -1 * normal;
  }

  Vec3 point = ray.parametric(t);
  return HitRecord{true, t, point, normal, this->material.get()};
}
