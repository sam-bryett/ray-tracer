#include "primitive.h"

void Primitive::setMaterial(std::shared_ptr<Material> material) {
  this->material = material;
}

void Primitive::setMaterial(const Material &material) {
  this->material = std::make_shared<Material>(material);
}
