#ifndef OPENGL_TUTORIALS_SHADERS_H
#define OPENGL_TUTORIALS_SHADERS_H

// Includes
#include <glad/glad.h>

namespace gltut
{

/**
	\brief Creates a shader
	\return The shader ID, or 0 if an error occurred
*/
unsigned createShader(GLenum shaderType, const char* shaderSource);

/**
	\brief Creates a shader program
	\return The shader program ID, or 0 if an error occurred
*/
unsigned createShaderProgram(
	const char* vertexShaderSource,
	const char* fragmentShaderSource);

// End of the namespace gltut
}

#endif
