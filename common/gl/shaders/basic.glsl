#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

varying vec4 vColor;

uniform mat4 u_Proj;
uniform mat4 u_View;

void main()
{
   gl_Position = u_Proj * u_View * position;
   vColor = color;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

varying vec4 vColor;

void main()
{
   color = vColor;
}
