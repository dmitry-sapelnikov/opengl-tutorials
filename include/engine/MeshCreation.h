#ifndef OPENGL_TUTORIALS_MESH_CREATION_H
#define OPENGL_TUTORIALS_MESH_CREATION_H

// Includes
#include "Scene.h"

namespace gltut
{
// Global functions
/**
	\brief Creates a box mesh with non-smooth normals

	\param width The width of the box
	\param height The height of the box
	\param depth The depth of the box

	\return The mesh if it was created successfully, nullptr otherwise

	\note The mesh is created with the following vertex format:
	VertexFormat::VERTEX_FORMAT_POS3_NORM3_TEX2

	\note Negative dimentions produce an inverted mesh
*/
Mesh* createBoxMesh(Scene& scene, float width, float height, float depth) noexcept;

/**
	\brief Creates a sphere mesh with smooth normals

	\param scene The scene where the mesh will be created
	\param radius The radius of the sphere
	\param subdivisions The number of subdivisions for the sphere, must be greater than 0
	
	\return The mesh if it was created successfully, nullptr otherwise

	\note The mesh is created with the following vertex format:
	VertexFormat::VERTEX_FORMAT_POS3_NORM3_TEX2

	\note Negative radius produces an inverted mesh
*/
Mesh* createSphereMesh(Scene& scene, float radius, u32 subdivisions) noexcept;

// End of the namespace gltut
}

#endif
