#pragma once

// Includes
#include "engine/factory/material/phong/PhongMaterialModel.h"

namespace gltut
{
// Global classes
/// The material factory interface. Creates various scene materials.
class MaterialFactory
{
public:
	///	Creates a Phong material model
	virtual PhongMaterialModel* createPhongModel() noexcept = 0;
};

// End of the namespace gltut
}
