#ifndef SPHERE_H_
#define SPHERE_H_
#include <vector>

namespace Sphere
{
    struct Vertex;
    struct ColorVertex;
    extern std::vector<Vertex> generateSphere(float, int, int,ColorVertex );
    extern void drawSphere();
    
} // namespace name

#endif