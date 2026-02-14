#include "vec3.h"
#include <cstdint>
#include <random>
inline thread_local std::mt19937 generator(42);

inline double random_double(double min, double max, uint32_t seed) {
  if (min > max) {
    std::clog << "Invalid use of random_vector: min must be <= max" << '\n';
    exit(0);
  }
  std::uniform_real_distribution<> dis{min, max};
  return dis(generator);
}

inline Vec3 random_vector(double min, double max, uint32_t seed) {
  if (min > max) {
    std::clog << "Invalid use of random_vector: min must be <= max" << '\n';
    exit(0);
  }
  std::uniform_real_distribution<> dis{min, max};
  while (true) {
    Vec3 rand_vec = Vec3(dis(generator), dis(generator), dis(generator));
    // if random vector is non-zero, return it
    if (rand_vec.length() > 1e-6) {
      return rand_vec;
    }
  }
}
