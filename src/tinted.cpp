#include "tinted.h"
#include "ray.h"
#include "vec3.h"

Vec3 TintedMaterial::calculateReflection(const Ray &incoming_ray,
                                         const Vec3 &surface_normal,
                                         Vec3 &incoming_light,
                                         Vec3 &light_colour, uint32_t seed) {
  light_colour = light_colour + (this->colour - light_colour) * tint_factor;

  // Ray direction is not changed
  return incoming_ray.direction();
}
