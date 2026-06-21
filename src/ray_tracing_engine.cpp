#include "ray_tracing_engine.h"
#include "bsdf.h"
#include "camera.h"
#include "canvas.h"
#include "msaa.h"
#include "ray.h"
#include "utility.h"
#include "scene.h"
#include <cstdint>

void RayTracingEngine::render(Camera &camera, Scene &scene, Canvas &canvas) {
  scene.buildBVH();
  //   Loop over every pixel in the image
  for (int j = 0; j < camera.getImageHeight(); j++) {
    for (int i = 0; i < camera.getImageWidth(); i++) {
      std::vector<Ray> rays;
      rays.reserve(samples_per_pixel);

      // Generate a ray for each sample
      for (size_t k = 0; k < samples_per_pixel; k++) {
        Sample offset = sampleSquareOffset();
        Ray ray = camera.generateRay(i + offset.sx, j + offset.sy);
        rays.push_back(ray);
      }

      Vec3 colour{};
      uint32_t seed = j * camera.getImageHeight() + i;
      Vec3 sum{};
      for (auto ray : rays) {
        sum = calculateColour(ray, scene, seed) + sum;
        seed++;
      }
      colour = sum / samples_per_pixel;
      colour = toGamma(colour);
      canvas.setPixelByScreen(colour, i, j);
    }
  }
}

void RayTracingEngine::setMaxLightBounces(int light_bounces) {
    max_light_bounces = light_bounces;
}

void RayTracingEngine::addMultiSampling(int samples_per_pixel) {
  this->samples_per_pixel = samples_per_pixel;
}

Vec3 RayTracingEngine::calculateColour(Ray &ray, Scene &scene, uint32_t seed) {

  double epsilon = 1e-4;

  Vec3 incoming_light{};
  Vec3 light_colour{1, 1, 1};

  for (int i = 0; i < max_light_bounces; i++) {

    HitRecord record = scene.traceRay(ray).record;

    if (record.hit) {
      const auto &material = *record.material;
      // Use material of surface to modify light and colour
      Vec3 reflection = bsdf::calculateReflection(ray, record.normal, material, incoming_light, light_colour, seed);
      

      // If light is fully absorbed, don't create a reflection ray
      if (reflection.length() <= epsilon) {
        break;
      }
      // Offset to avoid self intersection with new ray
      ray = Ray(record.point + epsilon * record.normal, reflection);

    } else {

      Vec3 unit_direction = normalise(ray.direction());
      auto a = 0.5*(unit_direction.y + 1.0);
      Vec3 background = (1.0-a)*Vec3(1.0, 1.0, 1.0) + a*Vec3(0.5, 0.7, 1.0);
      light_colour = light_colour * background;
      incoming_light = incoming_light + background_intensity * light_colour;
      break;
    }
  }
  // std::clog << "incoming_light is " << incoming_light << '\n';
  return incoming_light;
}
