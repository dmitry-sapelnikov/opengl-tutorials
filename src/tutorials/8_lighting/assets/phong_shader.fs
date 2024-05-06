#version 330 core

in vec3 pos;
in vec3 normal;

out vec4 outColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	vec3 norm = normalize(normal);

	float ambientStrength = 0.2f;
	vec3 ambient = ambientStrength * lightColor;

	vec3 lightDirection = normalize(lightPos - pos);
	vec3 diffuse = max(0.0f, dot(norm, lightDirection)) * lightColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - pos);
	vec3 reflectDir = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	outColor =  vec4((ambient + diffuse + specular) * objectColor, 1.0f);
}
