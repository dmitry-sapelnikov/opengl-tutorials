#version 330 core
in vec2 TexCoord;

out vec4 outColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	outColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
}
