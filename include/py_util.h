#include <string>
#include "cnpy.h"
#include <cstdint>
#include <vector>

namespace PyUtil {
  inline void saveNpy(std::string path_str, const std::vector<float> &data_vec, int height, int width, int channels) {

    if (channels == 1) {
      cnpy::npy_save(path_str, data_vec.data(), 
        {static_cast<unsigned long>(height), 
        static_cast<unsigned long>(width)}, "w");

    } else {
      cnpy::npy_save(path_str, data_vec.data(), 
        {static_cast<unsigned long>(height), 
        static_cast<unsigned long>(width), 
        static_cast<unsigned long>(channels)}, "w");
    } 
  }

  inline void saveNpy(std::string path_str, const std::vector<uint8_t> &data_vec, int height, int width) {
    cnpy::npy_save(path_str, data_vec.data(), 
      {static_cast<unsigned long>(height), 
      static_cast<unsigned long>(width)}, "w");
  }
}

