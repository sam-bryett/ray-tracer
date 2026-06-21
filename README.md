# ray-tracer
Monte-Carlo path tracing engine from scratch using C++. So far I've added:
* Diffuse reflections using Lambertian scattering to simulate matte materials
* Specular reflections with fuzz for smooth, metal materials
* Global illumination through recursive light bounces to capture realistic, indirect lighting
* Bounding Volume Heirarchy (BVH) acceleration structure for efficient ray-object intersection queries in $O(\log( n))$ average time
