#pragma once

#include "scene.h"
#include "scenes/scene_builder.h"


void makeGrid(Scene &scene, int gridSize, float spacing, float offset,
              Material sphereMaterial, float radius = .2) {
  for (int i = 0; i < gridSize; i++) {
    for (int j = 0; j < gridSize; j++) {

      double x = i * spacing - offset;
      double y = j * spacing - offset;
      double z = 0.0; // flat grid on ground

      Vec3 center(x, y, z);
      auto sphere = std::make_shared<Sphere>(radius, center);
      sphere->setMaterial(sphereMaterial);
      scene.addPrimitive(sphere);
    }
  }
}

Scene makeSphereGridScene() {
    Scene scene;
    int gridSize{100};
    float spacing{0.5};
    float offset{0.5};
    Vec3 red{0.9, 0.5, 0.2};
    float smoothness{0.5};
    Material sphereMaterial = Material{red, smoothness};
    makeGrid(scene, gridSize, spacing, offset, sphereMaterial);
    return scene;
}
Scene makeColouredSphereDemo();
Scene specularDiffuseDemo();
