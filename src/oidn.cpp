#include "oidn.h" 
#include "primitive.h"
#include <iostream>
#include <OpenImageDenoise/oidn.h>

void assert(bool expression, std::string msg) {
  if (expression == false) {
    std::cerr << msg << '\n';
    std::exit(1);
  }
}

void denoise(Buffer& buf) {

  assert(buf.color.size() == buf.normal.size() 
      && buf.albedo.size() == buf.color.size(), "mismatch");
  assert(buf.color.size() == buf.width * buf.height * 3, "incorrect");

  assert(buf.depth.size() == buf.valid.size() && buf.depth.size() == buf.width * buf.height,
      "problems with depth/valid buffers");
  // create device
  OIDNDevice device = oidnNewDevice(OIDN_DEVICE_TYPE_CPU);
  oidnCommitDevice(device);

  // create ray tracing filter
  OIDNFilter filter = oidnNewFilter(device, "RT");

  // set buffers 
  oidnSetSharedFilterImage(filter, "color",  buf.color.data(),
                            OIDN_FORMAT_FLOAT3, buf.width, buf.height, 0, 0, 0);
  oidnSetSharedFilterImage(filter, "albedo", buf.albedo.data(),
                          OIDN_FORMAT_FLOAT3, buf.width, buf.height, 0, 0, 0);

  oidnSetSharedFilterImage(filter, "normal", buf.normal.data(),
                          OIDN_FORMAT_FLOAT3, buf.width, buf.height, 0, 0, 0);

  // denoise in-place
  oidnSetSharedFilterImage(filter, "output", buf.color.data(),  
                          OIDN_FORMAT_FLOAT3, buf.width, buf.height, 0, 0, 0);

  oidnCommitFilter(filter);

  oidnExecuteFilter(filter);

  oidnReleaseFilter(filter);
  oidnReleaseDevice(device);
}


void addPixelData(Buffer &buf, int idx, const Vec3& color, const HitRecord &record) {
  
  Vec3 albedo{};
  Vec3 normal{};
  float depth = -1;
  bool is_valid = false;

  if (record.hit == true) {
    is_valid = true;
    albedo = record.material->colour; 
    normal = record.normal;
    // normalise depth
    depth = std::log(1.0f + record.t);
  }

  addColor(buf, idx, color);
  addAlbedo(buf, idx, albedo);
  addNormal(buf, idx, normal);
  addValid(buf, idx, is_valid);
  addDepth(buf, idx, depth);
}


void addValid(struct Buffer& buf, int idx, uint8_t is_valid) {
  buf.valid[idx] = is_valid;
}

void addDepth(struct Buffer& buf, int idx, float depth) {
  buf.depth[idx] = depth;
}


void addColor(struct Buffer& buf, int idx, const Vec3& color) {
  buf.color[idx * 3] = static_cast<float>(color.x);
  buf.color[idx * 3 + 1] = static_cast<float>(color.y);
  buf.color[idx * 3 + 2] = static_cast<float>(color.z);
}

void addAlbedo(struct Buffer& buf, int idx, const Vec3& albedo) {
  buf.albedo[idx * 3] = static_cast<float>(albedo.x);
  buf.albedo[idx * 3 + 1] = static_cast<float>(albedo.y);
  buf.albedo[idx * 3 + 2] = static_cast<float>(albedo.z);
}

void addNormal(struct Buffer& buf, int idx, const Vec3& n) {
  buf.normal[idx * 3] = static_cast<float>(n.x);
  buf.normal[idx * 3 + 1] = static_cast<float>(n.y);
  buf.normal[idx * 3 + 2] = static_cast<float>(n.z);
}

