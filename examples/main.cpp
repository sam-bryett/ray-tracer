#include "camera.h"
#include "canvas.h"
#include "material.h"
#include "msaa.h"
#include "ray_tracing_engine.h"
#include "scene.h"
#include "sphere.h"
#include "vec3.h"
#include <chrono>
#include <memory>


int main(int argc, char **argv) {
  auto start = std::chrono::high_resolution_clock::now();
  Scene scene;
  Vec3 red = Vec3(0.9, 0.2, 0.2);
  float smoothness = 0;

  Material sphereMaterial = Material{red, smoothness};

  // shared pointer for material int gridSize = 10;
  int gridSize = 100;
  double spacing = .5; // distance between sphere centers
  double radius = 0.2;

  double offset = (gridSize - 1) * spacing * 0.5;
  makeGrid(scene, gridSize, spacing, offset, sphereMaterial);
  Vec3 camera_origin(0, 0, -10);
  Camera camera{camera_origin};

  int focal_length = 1;
  int image_height = 720;
  int image_width = image_height * 16.0 / 9;

  camera.setResolution(image_width, image_height);
  camera.setFocalLength(focal_length);

  RayTracingEngine raytracer = RayTracingEngine();

  raytracer.addMultiSampling(1);

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
