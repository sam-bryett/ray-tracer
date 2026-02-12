#include "canvas.h"
#include <math.h>

Canvas::Canvas(int width, int height) {
  pixels = *new std::vector<Pixel>(width * height);
  this->width = width;
  this->height = height;
}
void Canvas::writeHeader() {
  output << "P3\n" << width << " " << height << '\n' << max_colour << '\n';
}

void Canvas::writePixel(Pixel pixel) {
  output << toByte(pixel.x) << ' ' << toByte(pixel.y) << ' ' << toByte(pixel.z)
         << '\n';
}

int Canvas::toByte(double t) const {
  if (t < 0) {
    // std::clog << "error!" << '\n';
    t = 0;
  }
  if (t > 1) {
    t = 1;
  }
  return t * (max_colour + 0.999);
}

void Canvas::setPixelByCartesian(Pixel pixel, int x, int y) {
  // Convert cartesian coordinates to pixel index
  x += floor(width / 2);
  y = (-y) + floor(height / 2);

  setPixelByIndex(pixel, y * width + x);
}

void Canvas::setPixelByScreen(Pixel pixel, int x, int y) {
  setPixelByIndex(pixel, y * width + x);
}

void Canvas::setPixelByIndex(Pixel pixel, int index) {
  if (index < 0 || index >= width * height) {
    std::cout << "error: index invalid" << '\n';
    exit(1);
    return;
  }

  pixels[index] = pixel;
}

void Canvas::createImage() {
  writeHeader();
  for (Pixel pixel : pixels) {
    writePixel(pixel);
  }
  output.flush();
}
