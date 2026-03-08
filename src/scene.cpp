#include "scene.h"
#include "bvh_node.h"
#include "primitive.h"
#include "ray.h"
#include "tinted.h"
#include "utility.h"
#include "vec3.h"
#include <limits>
#include <optional>

void Scene::addPrimitive(std::shared_ptr<Primitive> object) {
  primitives.push_back(object);
}

RayRecord Scene::traceRay(const Ray &ray) {
  if (nodes.size() == 0) {
    return RayRecord(HitRecord(false));
  }

  HitRecord closest_hit{false, -1};
  closest_hit.t = std::numeric_limits<float>::infinity();
  std::shared_ptr<Primitive> object;

  double epsilon = 1e-8;

  std::vector<int> stack;
  stack.push_back(0);

  // Check if ray hit any bvh nodes and traverse down tree with DFS
  while (stack.size() > 0) {
    BVHNode &box = nodes[stack.back()];
    stack.pop_back();

    Vec3 n = Vec3(1, 1, 1);
    std::optional<double> t = slabIntersection(box.min, box.max, ray, n);
    if (!t) {
      continue;
    }

    if (box.num_primitives > 0) {
      if (t > closest_hit.t) {
        continue;
      }
      // Find closest object inside the bvh node that was hit
      for (int i = 0; i < box.num_primitives; i++) {

        auto obj = primitives[i + box.first_primitive];
        HitRecord current_record = obj->raycast(ray);

        if (current_record.hit && current_record.t >= epsilon) {
          if (!closest_hit.hit || closest_hit.t > current_record.t) {
            closest_hit = current_record;
            object = obj;
          }
        }
      }
    } else {
      stack.push_back(box.left_node);
      stack.push_back(box.right_node);
    }
  }

  return RayRecord(closest_hit, object);
}

void Scene::buildBVH() {
  if (!primitives.size()) {
    return;
  }
  this->nodes = std::vector<BVHNode>(2 * primitives.size() + 1);
  nodes[0].num_primitives = primitives.size();
  nodes[0].first_primitive = 0;
  num_nodes++;
  subdivide(0);

  Vec3 box_colour = Vec3(0.15, 0.15, 0.18);
  int i = 0;
}

void Scene::subdivide(int node_index) {
  BVHNode &root = nodes[node_index];
  float inf = std::numeric_limits<float>::infinity();
  Vec3 totalMin{inf, inf, inf};
  Vec3 totalMax{-inf, -inf, -inf};

  for (int i = 0; i < root.num_primitives; i++) {
    auto p = primitives[i + root.first_primitive];
    Vec3 min = p->getMin();
    Vec3 max = p->getMax();

    totalMin.x = std::min(min.x, totalMin.x);
    totalMin.y = std::min(min.y, totalMin.y);
    totalMin.z = std::min(min.z, totalMin.z);

    totalMax.x = std::max(max.x, totalMax.x);
    totalMax.y = std::max(max.y, totalMax.y);
    totalMax.z = std::max(max.z, totalMax.z);
  }

  root.min = totalMin;
  root.max = totalMax;
  double axis_size = totalMax.x - totalMin.x;
  Vec3 axis = Vec3(1, 0, 0);
  if (totalMax.y - totalMin.y > axis_size) {
    axis_size = totalMax.y - totalMin.y;
    axis = Vec3(0, 1, 0);
  }
  if (totalMax.z - totalMin.z > axis_size) {
    axis_size = totalMax.z - totalMin.z;
    axis = Vec3(0, 0, 1);
  }

  double centre = dotProduct(totalMax + totalMin, axis) * 0.5;
  if (root.num_primitives <= 1) {
    return;
  }

  int i = root.first_primitive,
      j = root.first_primitive + root.num_primitives - 1;
  while (i <= j) {
    if (dotProduct(axis, primitives[i]->getCentre()) < centre) {
      i++;
    } else {
      std::swap(primitives[i], primitives[j--]);
    }
  }

  int left_count = i - root.first_primitive;
  if (left_count == 0 || left_count == root.num_primitives)
    return;

  // Create child nodes
  int left_index = num_nodes++;
  int right_index = num_nodes++;

  BVHNode &left_child = nodes[left_index];
  left_child.first_primitive = root.first_primitive;
  left_child.num_primitives = left_count;

  BVHNode &right_child = nodes[right_index];
  right_child.first_primitive = i;
  right_child.num_primitives = root.num_primitives - left_count;

  // Set current node to an internal node and recursively subdivide
  root.left_node = left_index;
  root.right_node = right_index;
  root.num_primitives = 0;

  subdivide(left_index);
  subdivide(right_index);
}
