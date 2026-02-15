#include "primitive.h"
#include "vec3.h"
class BoundingBox : public Primitive {
public:
  BoundingBox(Vec3 min, Vec3 max);
  HitRecord raycast(const Ray &ray) override;

private:
  Vec3 min{};
  Vec3 max{};
};
