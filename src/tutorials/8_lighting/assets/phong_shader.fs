#version 330 core

in vec3 pos;
in vec3 normal;

out vec4 outColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	vec3 lightDirection = normalize(lightPos - pos);
	vec3 diffuse = max(0.0f, dot(normal, lightDirection)) * lightColor;

	outColor =  vec4((ambient + diffuse) * objectColor, 1.0f);
}
