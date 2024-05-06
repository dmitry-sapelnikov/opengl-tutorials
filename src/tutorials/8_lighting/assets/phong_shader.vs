#version 330 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;

out vec3 pos;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMat;

void main()
{
	gl_Position = projection * view * model * vec4(inPos, 1.0f);
	pos = vec3(model * vec4(inPos, 1.0f));
	normal = normalize(normalMat * inNormal);
}
