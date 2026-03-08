#pragma once
#include "bvh_node.h"
#include "primitive.h"
#include <memory>
#include <vector>

class Primitive;

struct RayRecord {
  HitRecord record{};
  std::shared_ptr<Primitive> object;
};

class Scene {
public:
  void addPrimitive(std::shared_ptr<Primitive> object);

  RayRecord traceRay(const Ray &ray);

  void buildBVH();

private:
  void subdivide(int node_index);
  std::vector<std::shared_ptr<Primitive>> primitives{};
  std::vector<BVHNode> nodes;
  int num_nodes{};
};
