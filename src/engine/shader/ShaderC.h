#ifndef OPENGL_TUTORIALS_SHADER_C_H
#define OPENGL_TUTORIALS_SHADER_C_H

// Includes
#include <array>
#include "engine/core/NonCopyable.h"
#include "engine/shader/Shader.h"

namespace gltut
{

class ShaderC : public Shader, public NonCopyable
{
public:
	/// Returns the name of standard matrix variable
	const char* getMatrixName(Matrix matrix) const noexcept final;

	/// Sets the name of the standard matrix variable
	void setMatrixName(Matrix matrix, const char* name) noexcept final;

private:
	/// Names of standard matrix variables
	std::array<std::string, static_cast<size_t>(Matrix::TOTAL_COUNT)> mMatrixNames;
};

// End of the namespace gltut
}

#endif
