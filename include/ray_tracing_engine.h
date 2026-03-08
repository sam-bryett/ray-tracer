#pragma once
#include "msaa.h"
#include "vec3.h"
#include <cstdint>
#include <span>

class Camera;
class Canvas;
class Ray;
class Sample;
class Scene;

constexpr Vec3 light_origin(-1, 1, -1);
constexpr Vec3 light_colour(1, 1, 1);
constexpr Vec3 background(0.4, 0.9, 0.8);
constexpr Vec3 background_intensity(1, 1, 1);

class RayTracingEngine {
public:
  RayTracingEngine() = default;
  int max_light_bounces = 10;

  void render(Camera &camera, Scene &scene, Canvas &canvas);

  void addMultiSampling(int samplesPerPixel);

  Vec3 calculateColour(Ray &ray, Scene &scene, uint32_t seed);

private:
  std::span<const Sample> msaaSamples = setMsaa(0);
};
