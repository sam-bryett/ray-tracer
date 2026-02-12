#include "material.h"
#include "random.h"
#include "ray.h"
#include "vec3.h"

Vec3 Material::calculateReflection(const Ray &incoming_ray,
                                   const Vec3 &surface_normal,
                                   Vec3 &incoming_light, Vec3 &light_colour,
                                   uint32_t seed) {
  Vec3 outgoing_ray_direction{};
  // Randomly decide between specular or diffuse reflection from smoothness
  double specular_probability = random_double(0, 1, seed);

  if (specular_probability >= this->smoothness) {
    // Random uniform distribution of outgoing ray
    light_colour = light_colour * this->colour;
    outgoing_ray_direction = normalise(random_vector(-1, 1, seed));
    if (dotProduct(outgoing_ray_direction, surface_normal) < 0) {
      outgoing_ray_direction = outgoing_ray_direction * -1;
    }

  } else {
    outgoing_ray_direction = normalise(random_vector(-1, 1, seed));
    light_colour = light_colour * this->specular_colour;
    auto d = incoming_ray.direction();
    auto n = surface_normal;
    // Reflection formula
    outgoing_ray_direction = d - 2 * dotProduct(d, n) * n;
  }

  Vec3 emitted_light = this->emission_strength * this->emission_colour;
  incoming_light = incoming_light + emitted_light * light_colour;

  // Return zero vector if no light reflected
  return outgoing_ray_direction;
}
