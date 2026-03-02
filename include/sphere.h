#pragma once
#include "primitive.h"
#include "vec3.h"
class Sphere : public Primitive {
public:
  Sphere(double radius, Vec3 origin) : rad(radius), orig(origin) {}
  double radius() const { return rad; }
  Vec3 origin() const { return orig; }

  HitRecord raycast(const Ray &ray) override;
  Vec3 getMin() override;
  Vec3 getMax() override;
  Vec3 getCentre() override;

private:
  double rad;
  Vec3 orig;
};
