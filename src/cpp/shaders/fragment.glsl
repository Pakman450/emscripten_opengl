#version 300 es
precision mediump float;
in vec3 v_vertexColors;
out vec4 color;

// Offset of a uniform buffer
// uniform float u_Offsety; // uniform variable
// uniform float u_Offsetx; // uniform variable



void main()
{

   color = vec4(v_vertexColors.r , v_vertexColors.g, v_vertexColors.b, 1.0f);
   // color = vec4(v_vertexColors.r - u_Offsetx, v_vertexColors.g, v_vertexColors.b, 1.0f);

}