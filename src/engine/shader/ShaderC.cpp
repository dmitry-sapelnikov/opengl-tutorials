// Includes
#include "ShaderC.h"
#include "engine/core/Check.h"

namespace gltut
{
// Global classes
const char* ShaderC::getMatrixName(Matrix matrix) const noexcept
{
	const auto& result = mMatrixNames[static_cast<size_t>(matrix)];
	return result.empty() ? nullptr : result.c_str();
}

void ShaderC::setMatrixName(Matrix matrix, const char* name) noexcept
{
	mMatrixNames[static_cast<size_t>(matrix)] = (name != nullptr) ? name : "";
}

// End of the namespace gltut
}
