#include "scene.h"
#include "random.h"
#include "scenes/scene_builder.h"
#include "sphere.h"

void makeGrid(Scene &scene, int grid_size, float spacing, 
              Material sphereMaterial, float radius = .2) {
  for (int i = 0; i < grid_size; i++) {
    for (int j = 0; j < grid_size; j++) {

      float offset = (grid_size * (radius)) / 2.0;
      double x = i * spacing - offset;
      double y = j * spacing - offset;
      double z = 1; 

      Vec3 center(x, y, z);
      auto sphere = std::make_shared<Sphere>(radius, center);
      sphere->setMaterial(sphereMaterial);
      scene.addPrimitive(sphere);
    }
  }
}

Scene makeGridScene() {
    Scene scene;
    int grid_size{1000};
    float spacing{0.5};
    Vec3 colour{1, 1, 1};
    float smoothness{1};
    Material sphereMaterial = Material{colour, smoothness};
    makeGrid(scene, grid_size, spacing, sphereMaterial);
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
  Vec3 sphere_origin = Vec3(-5, 0, 0);
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
  Vec3 sphere_origin = Vec3(-4, 0, 0);
  float radius = 0.5;
  Vec3 grey = Vec3(1,1,1);
  float smoothness = 1;
  float fuzz = 0;
  

  for (int i = 0; i < 6; i++) {
      auto sphere = std::make_shared<Sphere>(radius, sphere_origin);
      Vec3 colour = random_vec(0.0,1.0);
      Material sphereMaterial = Material{colour, smoothness};
      sphereMaterial.fuzz = fuzz;
      fuzz += 0.1;
      sphere_origin = sphere_origin + Vec3(1.5,0,0);
      sphere->setMaterial(sphereMaterial);
      scene.addPrimitive(sphere);
    }
  auto ground = std::make_shared<Sphere>(100, Vec3(0, -100.5, 2));
  ground->setMaterial(grey);
  scene.addPrimitive(ground);
  return scene;
}
