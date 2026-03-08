#include "ray_tracing_engine.h"
#include "camera.h"
#include "canvas.h"
#include "msaa.h"
#include "ray.h"
#include "scene.h"
#include <cstdint>

void RayTracingEngine::render(Camera &camera, Scene &scene, Canvas &canvas) {
  scene.buildBVH();
  //   Loop over every pixel in the image
  for (int j = 0; j < camera.getImageHeight(); j++) {
    for (int i = 0; i < camera.getImageWidth(); i++) {
      std::vector<Ray> rays;
      rays.reserve(msaaSamples.size());

      // Generate a ray for each sample
      for (auto sample : msaaSamples) {
        Ray ray = camera.generateRay(i + sample.sx, j + sample.sy);
        rays.push_back(ray);
      }

      // Pixel is an edge if samples hit different objects
      // auto object = scene.traceRay(rays[0]).object;
      // bool isEdge = false;
      // for (auto i = 1; i < rays.size(); i++) {
      //   auto newObj = scene.traceRay(rays[i]).object;
      //   if (newObj != object) {
      //     isEdge = true;
      //     break;
      //   }
      // }

      Vec3 colour{};
      uint32_t seed = j * camera.getImageHeight() + i;
      // For edge pixels, take the average of each samples colour
      Vec3 sum{};
      for (auto ray : rays) {
        sum = calculateColour(ray, scene, seed) + sum;
        seed++;
      }
      colour = sum / rays.size();
      canvas.setPixelByScreen(colour, i, j);
    }
  }
}

void RayTracingEngine::addMultiSampling(int samplesPerPixel) {
  msaaSamples = setMsaa(samplesPerPixel);
}

Vec3 RayTracingEngine::calculateColour(Ray &ray, Scene &scene, uint32_t seed) {

  double epsilon = 1e-6;

  Vec3 incoming_light{};
  Vec3 light_colour{1, 1, 1};

  for (int i = 0; i < max_light_bounces; i++) {
    RayRecord ray_record = scene.traceRay(ray);
    HitRecord record = ray_record.record;
    if (record.hit) {
      auto material = record.material;
      // Use material of surface to modify light and colour
      // std::clog << "hello" << '\n';
      Vec3 reflection = material->calculateReflection(
          ray, record.normal, incoming_light, light_colour, seed);

      // If light is fully absorbed, don't create a reflection ray
      if (reflection.length() <= epsilon) {
        break;
      }
      // Offset to avoid self intersection with new ray
      ray = Ray(record.point, reflection);

    } else {
      light_colour = light_colour * background;
      incoming_light = incoming_light + background_intensity * light_colour;
      break;
    }
  }
  // std::clog << "incoming_light is " << incoming_light << '\n';
  return incoming_light;
}
