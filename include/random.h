#include "vec3.h"
#include <random>
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline Vec3 random_vec(double min, double max) {
    return Vec3(random_double(min,max), random_double(min,max), random_double(min,max));
}

inline Vec3 random_unit_vec() {
  while (true) {
    Vec3 p = random_vec(-1, 1);
    double len_squared = p.length_squared();
    if (len_squared <= 1.0 && len_squared > 1e-160) {
      return p / std::sqrt(len_squared); // normalised, uniform ON the sphere
    }
  }
}

inline Vec3 random_on_hemisphere(const Vec3& normal) {
    Vec3 on_unit_sphere = random_unit_vec();
    if (dotProduct(on_unit_sphere, normal) > 0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -1 * on_unit_sphere;
}
