#ifndef OPENGL_TUTORIALS_VERTEX_FORMAT_H
#define OPENGL_TUTORIALS_VERTEX_FORMAT_H

// Includes
#include "engine/core/Types.h"
#include "engine/core/Check.h"

namespace gltut
{
// Global classes
/// Vertex format
class VertexFormat
{
public:
	///	Maximum size of a vertex component, in float numbers
	static constexpr u32 MAX_COMPONENT_SIZE = 4;

	///	Stride of a vertex component, in bits
	static constexpr u32 COMPONENT_STRIDE = 4;

	///	Maximum number of vertex components
	static constexpr u32 MAX_VERTEX_COMPONENTS = (8 * sizeof(u64)) / COMPONENT_STRIDE;

	///	Returns the number of float numbers in a vertex component
	u32 getComponentSize(u32 index) const
	{
		GLTUT_ASSERT(index < MAX_VERTEX_COMPONENTS);
		return (mFormat >> (index * COMPONENT_STRIDE)) & VERTEX_COMPONENT_MASK;
	}

	///	Sets the number of float numbers in a vertex component
	void setComponentSize(u32 index, u32 size)
	{
		GLTUT_ASSERT(index < MAX_VERTEX_COMPONENTS);
		GLTUT_ASSERT(size <= MAX_COMPONENT_SIZE);
#ifdef _DEBUG
		//	Check that all previous elements are set
		for (u32 i = 0; i < index; ++i)
		{
			GLTUT_ASSERT(getComponentSize(i) != 0);
		}
#endif
		const u32 offset = index * COMPONENT_STRIDE;
		mFormat &= ~(VERTEX_COMPONENT_MASK << offset);
		mFormat |= static_cast<u64>(size) << offset;
	}

	///	Returns the size of a vertex component in bytes
	u32 getComponentSizeInBytes(u32 index) const
	{
		return getComponentSize(index) * sizeof(float);
	}

	///	Returns the total size of the vertex in float numbers
	u32 getTotalSize() const
	{
		u32 result = 0;
		for (u32 i = 0; i < MAX_VERTEX_COMPONENTS; ++i)
		{
			result += getComponentSize(i);
		}
		return result;
	}

	///	Returns the total size of the vertex in bytes
	u32 getTotalSizeInBytes() const
	{
		return getTotalSize() * sizeof(float);
	}

private:
	/// Vertex component mask
	static constexpr u64 VERTEX_COMPONENT_MASK = (1 << COMPONENT_STRIDE) - 1;

	/// Encoded vertex format
	u64 mFormat = 0;
};

// Global functions
/// Creates a vertex format from an array of component sizes
template <u32 ElementsCount>
VertexFormat createVertexFormat(const u32(&elements)[ElementsCount])
{
	VertexFormat result;
	for (u32 i = 0; i < ElementsCount; ++i)
	{
		result.setComponentSize(i, elements[i]);
	}
	return result;
}

//	Predefined vertex formats

/// Vertex format with position only
const VertexFormat VERTEX_FORMAT_POS3 = createVertexFormat({ 3 });

/// Vertex format with position and texture coordinates
const VertexFormat VERTEX_FORMAT_POS3_TEX2 = createVertexFormat({ 3, 2 });

/// Vertex format with position and color
const VertexFormat VERTEX_FORMAT_POS3_COLOR4 = createVertexFormat({ 3, 4 });

/// Vertex format with position and texture coordinates
const VertexFormat VERTEX_FORMAT_POS3_COLOR4_TEX2 = createVertexFormat({ 3, 4, 2 });

/// Vertex format with position and normal
const VertexFormat VERTEX_FORMAT_POS3_NORM3 = createVertexFormat({ 3, 3 });

/// Vertex format with position, normal and color
const VertexFormat VERTEX_FORMAT_POS3_NORM3_COLOR4 = createVertexFormat({ 3, 3, 4 });

/// Vertex format with position, normal and texture coordinates
const VertexFormat VERTEX_FORMAT_POS3_NORM3_TEX2 = createVertexFormat({ 3, 3, 2 });

/// Vertex format with position, normal, color and texture coordinates
const VertexFormat VERTEX_FORMAT_POS3_NORM3_COLOR4_TEX2 = createVertexFormat({ 3, 3, 4, 2 });

// End of the namespace gltut
}

#endif
