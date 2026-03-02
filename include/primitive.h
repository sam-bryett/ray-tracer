#pragma once
#include "material.h"
#include "vec3.h"
#include <memory>

class Ray;
class BoundingBox;
struct HitRecord {
  bool hit{};
  double t{};
  Vec3 point{};
  Vec3 normal{};
  Material *material{};
};

class Primitive {
public:
  Primitive() { material = std::make_shared<Material>(); };
  std::shared_ptr<Material> material{};
  void setMaterial(std::shared_ptr<Material> material);
  void setMaterial(const Material &material);

  virtual HitRecord raycast(const Ray &ray) = 0;
  virtual Vec3 getMin() = 0;
  virtual Vec3 getMax() = 0;
  virtual Vec3 getCentre() = 0;
};
