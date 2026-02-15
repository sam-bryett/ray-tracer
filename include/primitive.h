#pragma once
#include "material.h"
#include "vec3.h"
#include <memory>

class Ray;
struct HitRecord {
  bool hit{};
  double t{};
  Vec3 point{};
  Vec3 normal{};
  Material *material{};
};

class Primitive {
public:
  Primitive(){};
  std::shared_ptr<Material> material{};
  void setMaterial(std::shared_ptr<Material> material);
  void setMaterial(const Material &material);

  virtual HitRecord raycast(const Ray &ray) = 0;
};
