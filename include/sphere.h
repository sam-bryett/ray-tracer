#pragma once
#include "primitive.h"
#include "vec3.h"
class Sphere : public Primitive {
public:
  Sphere(double radius, Vec3 origin) : rad(radius), orig(origin) {}
  double radius() const { return rad; }
  Vec3 origin() const { return orig; }

  HitRecord raycast(const Ray &ray) override;

private:
  double rad;
  Vec3 orig;
};
