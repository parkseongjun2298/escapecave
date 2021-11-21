#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ex_Color;
out vec3 FragPos;
out vec3 Normal;

void main()
{
	gl_Position = projection * view * model * vec4(vPos, 1.0);
	FragPos = vec3(model * vec4(vPos, 1.0));
	Normal = vNormal;
	ex_Color = vColor;
}