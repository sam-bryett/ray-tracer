#include "material.h"
#include "random.h"
#include "ray.h"
#include "vec3.h"

Vec3 Material::calculateReflection(const Ray &incoming_ray,
                                   const Vec3 &surface_normal,
                                   Vec3 &incoming_light, Vec3 &light_colour,
                                   uint32_t seed) {
  // Return zero vector if no light reflected
  return surface_normal;
}
