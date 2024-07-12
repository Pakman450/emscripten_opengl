#ifndef SPHERE_H_
#define SPHERE_H_
#include <vector>
#include "Vertex.h"


namespace Sphere
{
    extern std::vector<Vertex::Vertex> generateSphere(float, int, int, Vertex::Vertex );
    extern void drawSphere();
    
} // namespace name

#endif