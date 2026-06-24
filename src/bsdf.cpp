#include "vec3.h"
#include "random.h"
#include "material.h"
#include "ray.h"
#include "bsdf.h"
#include <cstdint>

Vec3 bsdf::calculateReflection(const Ray &incoming_ray,
                            const Vec3 &surface_normal,
                            const Material &material,
                            Vec3 &incoming_light,
                            Vec3 &light_colour,
                            uint32_t seed) {
      Vec3 outgoing_ray_direction{};
      Vec3 emitted_light = material.emission_strength * material.emission_colour;
      // incoming_light = incoming_light + emitted_light * light_colour;

      // Randomly decide between specular or diffuse reflection from smoothness
      double scatter_probability = random_double(0, 1);

      if (scatter_probability > material.smoothness) {
        light_colour = 0.5 * light_colour * material.colour;
        outgoing_ray_direction = surface_normal + random_unit_vec();
        if (outgoing_ray_direction.length_squared() < 1e-8) {
          outgoing_ray_direction = surface_normal;
        }

      } else {
        light_colour = 0.5 * light_colour * material.colour;
        auto d = incoming_ray.direction();
        auto n = surface_normal;
        // Reflection formula
        outgoing_ray_direction = d - 2 * dotProduct(d, n) * n;
        auto fuzz = (material.fuzz < 1) ? material.fuzz : 1;
        auto outgoing_normal = normalise(outgoing_ray_direction);
        outgoing_ray_direction = outgoing_normal + (random_unit_vec() * fuzz);
        if (outgoing_ray_direction.length_squared() < 1e-8) {
          outgoing_ray_direction = outgoing_normal;
        }
      }

      // Return zero vector if no light reflected
      return outgoing_ray_direction;
}
