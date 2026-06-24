#include "camera.h"
#include "canvas.h"
#include "ray_tracing_engine.h"
#include "scene.h"
#include "vec3.h"
#include <chrono>
#include "camera.h"
#include "scenes/scene_builder.h"
#include "ray_tracing_engine.h"

int main(int argc, char **argv) {
  auto start = std::chrono::high_resolution_clock::now();
  Scene scene = fuzzDemo(); 
    
  Vec3 camera_origin(0, 0, -5);
  Camera camera{camera_origin};

  int focal_length = 1;
  int image_height = 1080;
  int image_width = image_height * 16.0 / 9;

  camera.setResolution(image_width, image_height);
  camera.setFocalLength(focal_length);

  RayTracingEngine raytracer = RayTracingEngine();

  raytracer.addMultiSampling(20);
  raytracer.setMaxLightBounces(30);
  raytracer.setDenoiser(true);

  Canvas canvas{image_width, image_height};
  raytracer.render(camera, scene, canvas);
  canvas.createImage();
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::clog << "time to complete: " << duration.count() / 1000000.0
            << "seconds\n";
  return 0;
}
