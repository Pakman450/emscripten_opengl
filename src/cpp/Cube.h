#ifndef CUBE_H_
#define CUBE_H_
#include <vector>
#include "Vertex.h"


namespace Cube
{
    extern std::vector<Vertex::Vertex> generateCube(float, int, int, Vertex::Vertex );
    extern void drawCube();
    
} // namespace name

#endif