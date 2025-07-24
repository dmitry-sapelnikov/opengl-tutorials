#ifndef OPENGL_TUTORIALS_SHADER_C_H
#define OPENGL_TUTORIALS_SHADER_C_H

// Includes
#include <array>
#include "engine/core/NonCopyable.h"
#include "engine/renderer/shader/Shader.h"

namespace gltut
{

class ShaderC : public Shader, public NonCopyable
{
public:
	/// Returns the name of a scene parameter
	const char* getSceneParameterName(SceneParameter parameter) const noexcept final;

	/// Sets the name of a scene parameter
	void setSceneParameterName(SceneParameter parameter, const char* name) noexcept final;

private:
	/// Names of scene parameters
	std::array<std::string, static_cast<size_t>(SceneParameter::TOTAL_COUNT)> mSceneParameterNames;
};

// End of the namespace gltut
}

#endif
