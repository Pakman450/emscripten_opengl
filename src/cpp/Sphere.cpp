#include <vector>
#include <cmath>
#include "Sphere.h"
#include <GLES3/gl3.h>

namespace Sphere
{
    struct Vertex {
        float x, y, z; // Position
        float r, g, b; // Color
    };


    std::vector<Vertex> generateSphere(float radius, int latitudeBands, int longitudeBands, const Vertex& colorvertex) {
        std::vector<Vertex> vertices;

        for (int latNumber = 0; latNumber <= latitudeBands; ++latNumber) {
            float theta = latNumber * M_PI / latitudeBands;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);

            for (int longNumber = 0; longNumber <= longitudeBands; ++longNumber) {
                float phi = longNumber * 2 * M_PI / longitudeBands;
                float sinPhi = sin(phi);
                float cosPhi = cos(phi);

                Vertex vertex;
                vertex.x = radius * cosPhi * sinTheta;
                vertex.y = radius * cosTheta;
                vertex.z = radius * sinPhi * sinTheta;
                vertex.r = colorvertex.r;
                vertex.g = colorvertex.g;
                vertex.b = colorvertex.b;
                vertices.push_back(vertex);
            }
        }

        return vertices;
    }


    void drawSphere() {
        GLuint vao, vbo;
        Vertex colorvertex {1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}; // Position and color
        std::vector<Vertex> sphereVertices = generateSphere(0.5f, 30, 30, colorvertex);

        // Create and bind the VAO
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Create and bind the VBO
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(Vertex), &sphereVertices[0], GL_STATIC_DRAW);

        // Specify the layout of the vertex data
        glEnableVertexAttribArray(0); // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1); // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));

        // Draw the sphere
        glDrawArrays(GL_TRIANGLE_STRIP, 0, sphereVertices.size());

        // Unbind the VAO
        glBindVertexArray(0);

        // Clean up
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }
}
