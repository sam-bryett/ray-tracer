namespace ml {
  struct PixelFeatures {
    float r, g, b;
    float nx, ny, nz;
    float depth;
  };
  constexpr int low_spp = 4;
}
