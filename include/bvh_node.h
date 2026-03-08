#pragma once
#include "vec3.h"

struct BVHNode {
  Vec3 min{};
  Vec3 max{};

  // Store indices
  int left_node{};
  int right_node{};
  int first_primitive{};
  int num_primitives{};
};
