#pragma once
#include "vec3.h"
#include <cstdint>

class Ray;

class Material {
public:
  float smoothness{};
  Vec3 colour{};
  Vec3 specular_colour{.9, .9, .9};

  float emission_strength{};
  Vec3 emission_colour{.9, .9, .9};

  Material() : colour{}, smoothness{} {};
  Material(Vec3 colour, float smoothness = 0.0f)
      : colour{colour}, smoothness{smoothness} {}

  virtual Vec3 calculateReflection(const Ray &incoming_ray,
                                   const Vec3 &surface_normal,
                                   Vec3 &incoming_light, Vec3 &light_colour,
                                   uint32_t seed);

  Material(const Material &) = default;
  ~Material() = default;
  Material(Material &&maerial) noexcept = default;
};
