#version 300 es

// Set float type
precision mediump float;


// layout(location) on the VBO
layout(location=0) in vec3 position;
layout(location=1) in vec3 vertexColors;


// Offset of a uniform buffer
// uniform float u_Offsety; // uniform variable
// uniform float u_Offsetx; // uniform variable
uniform mat4 u_ModelMatrix;
uniform mat4 u_Projection; 
uniform mat4 u_ViewMatrix;


out vec3 v_vertexColors;

void main()
{
   // the M V P matrix. Model -> View -> Projection
   vec4 newPosition = u_Projection * u_ViewMatrix * u_ModelMatrix * vec4(position,1.0f);
                                                                     // dont forget w
   gl_Position = vec4(newPosition.x, newPosition.y, newPosition.z, newPosition.w);

   v_vertexColors = vertexColors;

}