#version 300 es

// layout(location) 
layout(location=0) in vec3 position;
layout(location=1) in vec3 vertexColors;

out vec3 v_vertexColors;


void main()
{
   gl_Position = vec4(position.x, position.y, position.z, 1.0f);
   v_vertexColors = vertexColors;

}