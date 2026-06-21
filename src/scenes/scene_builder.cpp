#include "scene.h"
#include "scenes/scene_builder.h"
#include "sphere.h"

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

Scene makeGridScene() {
    Scene scene;
    int gridSize{100};
    float spacing{0.5};
    float offset{0.5};
    Vec3 red{0.9, 0.2, 0.2};
    float smoothness{0.5};
    Material sphereMaterial = Material{red, smoothness};
    makeGrid(scene, gridSize, spacing, offset, sphereMaterial);
    return scene;
}

Scene makeColourScene() {
  Scene scene;
  Vec3 sphere_origin = Vec3(0, 0, 2);
  float radius = 0.5;
  Vec3 red = Vec3(0.9, 0.2, 0.2);
  float smoothness = 0;

  auto sphere = std::make_shared<Sphere>(radius, sphere_origin);
  Material sphereMaterial = Material{red, smoothness};
  sphere->setMaterial(sphereMaterial);

  scene.addPrimitive(sphere);

  auto sphere2 = std::make_shared<Sphere>(radius, Vec3(1, 0, 1));
  sphereMaterial.colour = Vec3(0.1, 0.9, 0.1);
  sphere2->setMaterial(sphereMaterial);

  auto sphere3 = std::make_shared<Sphere>(radius, Vec3(-1, 0, 1));
  sphereMaterial.emission_strength = 2;
  sphereMaterial.colour = Vec3(0.1, 0.9, 0.1);
  sphere3->setMaterial(sphereMaterial);

  auto sphere4 = std::make_shared<Sphere>(radius, Vec3(2.5, 0, 1));
  sphereMaterial.emission_strength = 1;
  sphereMaterial.emission_colour = Vec3(0.9, 0.9, 0.5);
  sphereMaterial.colour = Vec3(0.1, 0.9, 0.1);
  sphere4->setMaterial(sphereMaterial);

  scene.addPrimitive(sphere2);
  scene.addPrimitive(sphere3);
  scene.addPrimitive(sphere4);

  auto ground = std::make_shared<Sphere>(100, Vec3(0, -100.5, 2));
  const Vec3 blue(0.1, 0.2, 0.9);
  ground->setMaterial(blue);
  scene.addPrimitive(ground);
  return scene;
}

Scene makeSimpleGreyScene() {
  Scene scene;
  Vec3 sphere_origin = Vec3(0, 0, 0);
  float radius = 0.5;
  Vec3 grey = Vec3(1,1,1);
  float smoothness = 0;

  auto sphere = std::make_shared<Sphere>(radius, sphere_origin);
  Material sphereMaterial = Material{grey, smoothness};
  sphere->setMaterial(sphereMaterial);

  scene.addPrimitive(sphere);

  auto ground = std::make_shared<Sphere>(100, Vec3(0, -100.5, 2));
  ground->setMaterial(grey);
  scene.addPrimitive(ground);
  return scene;
}

Scene smoothnessDemo()  {
  Scene scene;
  Vec3 sphere_origin = Vec3(-6, 0, 0);
  float radius = 0.5;
  Vec3 grey = Vec3(1,1,1);
  float smoothness = 0;

  for (int i = 0; i < 6; i++) {
      auto sphere = std::make_shared<Sphere>(radius, sphere_origin);
      Material sphereMaterial = Material{grey, smoothness};
      sphere_origin = sphere_origin + Vec3(1.5,0,0);
      sphere->setMaterial(sphereMaterial);

      smoothness += 0.2;
      scene.addPrimitive(sphere);
    }
  auto ground = std::make_shared<Sphere>(100, Vec3(0, -100.5, 2));
  ground->setMaterial(grey);
  scene.addPrimitive(ground);
  return scene;
}

Scene fuzzDemo()  {
  Scene scene;
  Vec3 sphere_origin = Vec3(-1.5, 0, 0);
  float radius = 0.5;
  Vec3 grey = Vec3(1,1,1);
  float smoothness = 1;

  auto metal1 = std::make_shared<Sphere>(radius, sphere_origin);
  Material sphereMaterial = Material{grey, smoothness};
  sphere_origin = sphere_origin + Vec3(1.5,0,0);
  metal1->setMaterial(sphereMaterial);
  scene.addPrimitive(metal1);

  

  auto sphere = std::make_shared<Sphere>(radius, sphere_origin);
  sphere_origin = sphere_origin + Vec3(1.5,0,0);
  sphere->setMaterial(Material{grey, 0});
  scene.addPrimitive(sphere);
    
  auto metal2 = std::make_shared<Sphere>(radius, sphere_origin);
  sphere_origin = sphere_origin + Vec3(1.5,0,0);
  metal2->setMaterial(Material{grey, smoothness});
  scene.addPrimitive(metal2);
  auto ground = std::make_shared<Sphere>(100, Vec3(0, -100.5, 2));
  ground->setMaterial(Vec3(0, 0.8, 0.2));
  scene.addPrimitive(ground);
  return scene;
  return scene;
}
