#include <vector>
#include <cmath>
#include <GLES3/gl3.h>
#include "Vertex.h"
#include "Sphere.h"

namespace Sphere
{

    std::vector<Vertex::Vertex> GenerateSphereVertices(float r, int latB, int longB, const Vertex::Vertex& cv) {
        std::vector<Vertex::Vertex> vertices;

        for (int latNumber = 0; latNumber <= latB; ++latNumber) {
            float theta = latNumber * M_PI / latB;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);

            for (int longNumber = 0; longNumber <= longB; ++longNumber) {
                float phi = longNumber * 2 * M_PI / longB;
                float sinPhi = sin(phi);
                float cosPhi = cos(phi);

                Vertex::Vertex v;
                v.x = r * cosPhi * sinTheta;
                v.y = r * cosTheta;
                v.z = r * sinPhi * sinTheta;
                v.r = cv.r;
                v.g = cv.g;
                v.b = cv.b;
                vertices.push_back(v);
            }
        }

        return vertices;
    }

    std::vector<GLuint> GenerateSphereIndices(int latB, int longB) {
        std::vector<GLuint> indices;

        for (int latNumber = 0; latNumber < latB; ++latNumber) {
            for (int longNumber = 0; longNumber < longB; ++longNumber) {
                int first = (latNumber * (longB + 1)) + longNumber;
                int second = first + longB + 1;

                indices.push_back(first);
                indices.push_back(second);
                indices.push_back(first + 1);

                indices.push_back(second);
                indices.push_back(second + 1);
                indices.push_back(first + 1);
            }
        }

        return indices;
    }

    void drawSphere() {
        GLuint vao, vbo, ebo;
        Vertex::Vertex colorvertex {1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}; // Position and color
        std::vector<Vertex::Vertex> sphereVertices = GenerateSphereVertices(0.5f, 30, 30, colorvertex);
        std::vector<GLuint> sphereIndices = GenerateSphereIndices(30, 30);

        // Create and bind the VAO
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Create and bind the VBO
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(Vertex::Vertex), &sphereVertices[0], GL_STATIC_DRAW);

        // Create and bind the EBO
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(GLuint), &sphereIndices[0], GL_STATIC_DRAW);

        // Specify the layout of the vertex data
        glEnableVertexAttribArray(0); // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex::Vertex), (void*)0);

        glEnableVertexAttribArray(1); // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex::Vertex), (void*)(sizeof(float) * 3));

        // Draw the sphere
        glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);

        // Unbind the VAO
        glBindVertexArray(0);

        // Clean up
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteVertexArrays(1, &vao);
    }
}
