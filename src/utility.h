#include "material.h"
#include "primitive.h"
#include "ray.h"
#include "vec3.h"
#include <array>
#include <optional>

inline double d_min(double a, double b) { return (a <= b) ? a : b; }
inline double d_max(double a, double b) { return (a >= b) ? a : b; }

static std::optional<double> slabIntersection(const Vec3 &l, const Vec3 &h,
                                              const Ray &ray, Vec3 &normal) {
  auto o = ray.origin();
  auto r = ray.direction();
  double epsilon = 1e-6;

  // Remove zeroes
  auto rx = 1.0 / r.x;
  auto ry = 1.0 / r.y;
  auto rz = 1.0 / r.z;

  auto t_low_x = (l.x - o.x) * rx;
  auto t_low_y = (l.y - o.y) * ry;
  auto t_low_z = (l.z - o.z) * rz;

  auto t_high_x = (h.x - o.x) * rx;
  auto t_high_y = (h.y - o.y) * ry;
  auto t_high_z = (h.z - o.z) * rz;

  auto t_close_x = d_min(t_low_x, t_high_x);
  auto t_close_y = d_min(t_low_y, t_high_y);
  auto t_close_z = d_min(t_low_z, t_high_z);

  auto t_far_x = d_max(t_low_x, t_high_x);
  auto t_far_y = d_max(t_low_y, t_high_y);
  auto t_far_z = d_max(t_low_z, t_high_z);

  auto t_close = d_max(t_close_z, d_max(t_close_x, t_close_y));

  std::array<double, 6> planes = {t_low_x,  t_low_y,  t_low_z,
                                  t_high_x, t_high_y, t_high_z};
  auto index = 0;
  for (auto p : planes) {
    if (p == t_close) {
      int x = index % 3 == 0;
      int y = index % 3 == 1;
      int z = index % 3 == 2;
      normal = Vec3(x, y, z);
    }
    normal = (index < 3) ? -1 * normal : normal;
    index++;
  }
  auto t_far = d_min(t_far_z, d_min(t_far_x, t_far_y));
  if (t_far < t_close or t_far < epsilon) {
    return {};
  }
  return (t_close >= epsilon) ? t_close : t_far;
}
