#include <vector>
#include <cmath>
#include <GLES3/gl3.h>
#include "Vertex.h"
#include "Cube.h"


namespace Cube
{

    std::vector<Vertex::Vertex> GenerateCubeVertices(float length, const Vertex::Vertex& cv) {
        std::vector<Vertex::Vertex> vertices {};

        for (int i =0; i < 8; i++){
            Vertex::Vertex v;



            //--+
            if (i == 0){
                v.x = -length/2;
                v.y = -length/2;
                v.z = length/2;
            }

            //+-+
            if (i == 1){
                v.x = length/2;
                v.y = -length/2;
                v.z = length/2;
            }

            //+++
            if (i == 2){
                v.x = length/2;
                v.y = length/2;
                v.z = length/2;
            }

            //-++
            if (i == 3){
                v.x = -length/2;
                v.y = length/2;
                v.z = length/2;
            }





            //---
            if (i == 4){
                v.x = -length/2;
                v.y = -length/2;
                v.z = -length/2;
            }


            //+--
            if (i == 5){
                v.x = length/2;
                v.y = -length/2;
                v.z = -length/2;
            }


            //++-
            if (i == 6){
                v.x = length/2;
                v.y = length/2;
                v.z = -length/2;
            }

            //-+-
            if (i == 7){
                v.x = -length/2;
                v.y = length/2;
                v.z = -length/2;
            }




            v.r = cv.r;
            v.g = cv.g;
            v.b = cv.b;
            vertices.push_back(v);
        }



        return vertices;
    }
    
    void drawCube() {
        unsigned int indices[] = {
            0, 1, 2, 2, 3, 0, // Front face
            4, 5, 6, 6, 7, 4, // Back face
            0, 4, 7, 7, 3, 0, // Left face
            1, 5, 6, 6, 2, 1, // Right face
            3, 2, 6, 6, 7, 3, // Top face
            0, 1, 5, 5, 4, 0  // Bottom face
        };


        GLuint vao, vbo, ebo;
        Vertex::Vertex colorvertex {1.0f, 0.0f, 0.0f, 
                                    1.0f, 0.0f, 0.0f}; // Position and color

        std::vector<Vertex::Vertex> cubeVertices = GenerateCubeVertices(1.0f, colorvertex);

        // Generate Vertex arrays and buffers
        // This one has a ebo and a vbo
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        //Let's bind the Vertex array
        glBindVertexArray(vao);
        // Bind the buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        //Then add the data to the vbo
        glBufferData(GL_ARRAY_BUFFER, cubeVertices.size() * sizeof(Vertex::Vertex), &cubeVertices[0], GL_STATIC_DRAW);

        // Bind the buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        // add the data to the ebo
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Activate the Vertex positions array
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex::Vertex), (void*)0);
        
        // ACtivate the color array
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex::Vertex), (void*)(3 * sizeof(float)));
        
        // Bind the buffer for ebo
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

        //Un bind
        glBindVertexArray(0);

        // Delete the arrays
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }
}
