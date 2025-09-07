#pragma once

// Includes

namespace gltut
{

class RenderGeometry;
class Viewpoint;

/// Binds renderer parameters with a binding target
class RendererBinding
{
public:
	enum class Parameter
	{
		/// View matrix
		VIEWPOINT_VIEW_MATRIX = 0,

		/// Projection matrix
		VIEWPOINT_PROJECTION_MATRIX,

		/// Viewpoint position
		VIEWPOINT_POSITION,

		/// The model matrix
		GEOMETRY_MATRIX,

		/// The normal matrix
		GEOMETRY_NORMAL_MATRIX,

		/// Total number of parameters
		TOTAL_COUNT
	};

	/// Virtual destructor
	virtual ~RendererBinding() noexcept = default;

	/// Updates the binding for a viewpoint
	virtual void update(const Viewpoint* viewpoint, float aspectRatio) const noexcept = 0;

	/// Updates the binding for a render geometry
	virtual void update(const RenderGeometry* geometry) const noexcept = 0;
};

// End of the namespace gltut
}
