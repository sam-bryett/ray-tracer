#pragma once
#include "primitive.h"
#include "vec3.h"
class BoundingBox : public Primitive {
public:
  BoundingBox(Vec3 min, Vec3 max);
  HitRecord raycast(const Ray &ray) override;
  Vec3 getMin() override;
  Vec3 getMax() override;
  Vec3 getCentre() override;

private:
  Vec3 min{};
  Vec3 max{};
};
