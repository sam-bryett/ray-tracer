#pragma once
#include <vector>
#include "vec3.h"
#include <cstdint>

class HitRecord;

  struct Buffer {
    std::vector<float> color;
    std::vector<float> albedo;
    std::vector<float> normal;
    std::vector<float> depth;
    std::vector<uint8_t> valid;
    int width, height;

    Buffer(int width=0, int height=0) 
      : width(width), height(height),
        color(width * height * 3, 0.0f),
        albedo(width * height * 3, 0.0f),
        normal(width * height * 3, 0.0f),
        depth(width * height, -1.0f),
        valid(width * height, 0)
        {}
  };

void addValid(Buffer& buf, int idx, uint8_t valid);

void addDepth(Buffer& buf, int idx, float depth);

void addColor(Buffer& buf, int idx, const Vec3& color);

void addPixelData(Buffer &buf, int idx, const Vec3& color, const HitRecord &record);

void addAlbedo(Buffer& buf, int idx, const Vec3& albedo);

void addNormal(Buffer& buf, int idx, const Vec3& normal);

void denoise(Buffer& buf);

