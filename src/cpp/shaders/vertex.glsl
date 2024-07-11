#version 300 es

// Set float type
precision mediump float;


// layout(location) on the VBO
layout(location=0) in vec3 position;
layout(location=1) in vec3 vertexColors;


// Offset of a uniform buffer
uniform float u_Offsety; // uniform variable
uniform float u_Offsetx; // uniform variable

out vec3 v_vertexColors;


void main()
{
   gl_Position = vec4(position.x+ u_Offsetx, position.y + u_Offsety, position.z, 1.0f);
   v_vertexColors = vertexColors;

}