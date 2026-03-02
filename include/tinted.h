#pragma once
#include "material.h"
#include "vec3.h"

class Ray;

class TintedMaterial : public Material {
public:
  using Material::Material;
  Vec3 calculateReflection(const Ray &incoming_ray, const Vec3 &surface_normal,
                           Vec3 &incoming_light, Vec3 &light_colour,
                           uint32_t seed) override;
  double tint_factor{0.8};
};
