# ray-tracer
Monte-Carlo path tracing engine from scratch using C++. So far I've added:
* Diffuse reflections using Lambertian scattering to simulate matte materials
* Specular reflections for mirror-like materials
* Global illumination through recursive light bounces to capture realistic, indirect lighting
* Bounding Volume Heirarchy (BVH) acceleration structure for efficient ray-object intersection queries
  
I've prioritised making the codebase as modular as possible, so it's easy to add your own primitives, materials, or light scattering implementation.
