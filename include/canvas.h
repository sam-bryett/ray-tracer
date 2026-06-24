#pragma once
#include <iostream>
#include <ostream>
#include <vector>
#include <vector>
#include "vec3.h"

using Pixel = Vec3;
class Canvas {

private:
  std::vector<Pixel> pixels;
  std::ostream &output = std::cout;
  int max_colour = 255;
  int width;
  int height;

  void writeHeader();

  void writePixel(Pixel pixel);

public:
  Canvas(int width, int height);
  int toByte(double t) const;
  void setPixelByScreen(Pixel pixel, int x, int y);
  void setPixelByCartesian(Pixel pixel, int x, int y);
  void setPixelByIndex(Pixel pixel, int index);
  void setPixelByBuffer(const std::vector<float> &colours);
  void createImage();
  int getWidth() { return width; }
  int getHeight() { return height; }
};

