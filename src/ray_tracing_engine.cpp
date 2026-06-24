#include "ray_tracing_engine.h"
#include "ml/adaptive_sampling.h"
#include "bsdf.h"
#include "msaa.h"
#include "camera.h"
#include "canvas.h"
#include "ray.h"
#include "utility.h"
#include "oidn.h"
#include "scene.h"
#include <cstdint>

void RayTracingEngine::render(Camera &camera, Scene &scene, Canvas &canvas) {
  scene.buildBVH();
  
  //   Loop over every pixel in the image
  auto width = camera.getImageWidth();
  auto height = camera.getImageHeight();

  // initialise buffer
  buffer = Buffer(width, height);

  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {

      int idx = j * width + i;
      Vec3 colour{};

      HitRecord first_hit_record{};

      for (size_t k = 0; k < samples_per_pixel; k++) {
        Sample offset = sampleSquareOffset();

        // Generate a ray for each sample
        Ray ray = camera.generateRay(i + offset.sx, j + offset.sy);

        colour = calculateColour(ray, scene, first_hit_record, idx) + colour;
      }

      colour = colour / samples_per_pixel;
      addPixelData(buffer, idx, colour, first_hit_record);
    }
  }
  
  if (denoise_enabled) {
    denoise(buffer);
  }

  for (auto &c : buffer.color) {
    c = toGamma(c);
  }
  canvas.setPixelByBuffer(buffer.color);
}

void RayTracingEngine::setDenoiser(bool denoise_enabled) {
  this->denoise_enabled = denoise_enabled;
}

void RayTracingEngine::setMaxLightBounces(int light_bounces) {
    max_light_bounces = light_bounces;
}

void RayTracingEngine::addMultiSampling(int samples_per_pixel) {
  this->samples_per_pixel = samples_per_pixel;
}

Vec3 RayTracingEngine::calculateColour(Ray &ray, Scene &scene, HitRecord &first_hit, uint32_t seed) {

  double epsilon = 1e-6;

  Vec3 incoming_light{};
  Vec3 light_colour{1, 1, 1};

  for (int i = 0; i < max_light_bounces; i++) {

    HitRecord record = scene.traceRay(ray).record;
    if (i == 0) first_hit = record;

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
