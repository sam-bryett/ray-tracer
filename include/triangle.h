#pragma once
#include "primitive.h"
#include "vec3.h"

class Triangle : public Primitive {
public:
  Triangle() : p1{0, 1, 2}, p2{-1, 0, 2}, p3{1, 0, 2} {}
  Triangle(Vec3 v1, Vec3 v2, Vec3 v3) : p1{v1}, p2{v2}, p3{v3} {}

  Triangle(double x1, double y1, double x2, double y2, double x3, double y3,
           double z)
      : p1{x1, y1, z}, p2{x2, y2, z}, p3{x3, y3, z} {}

  HitRecord raycast(const Ray &ray);

private:
  Vec3 p1;
  Vec3 p2;
  Vec3 p3;
};
