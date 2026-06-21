#pragma once
#include <cstdint>

class Scene;
class Material;
class Ray;
class Vec3;

namespace bsdf {
    Vec3 calculateReflection(const Ray &incoming_ray,
                        const Vec3 &surface_normal,
                        const Material &material,
                        Vec3 &incoming_light,
                        Vec3 &light_colour,
                        uint32_t seed);
}
