#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 WPos;
out vec3 WNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	WPos = vec3(model * vec4(aPos, 1.0));
	WNormal = mat3(transpose(inverse(model))) * aNormal;
}