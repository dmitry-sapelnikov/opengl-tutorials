// Includes
#include "GraphicsDeviceBase.h"

#include <iostream>
#include "../core/File.h"

namespace gltut
{

// Local functions
namespace
{

template <typename T>
void removeElement(
	std::vector<std::unique_ptr<T>>&container,
	T * element,
	const char* elementName) noexcept
{
	if (element == nullptr)
	{
		return;
	}

	auto findResult = std::find_if(
		container.begin(),
		container.end(),
		[&element](const auto& e)
		{
			return e.get() == element;
		});

	if (findResult != container.end())
	{
		container.erase(findResult);
	}
	else
	{
		std::cerr << "Failed to remove the element: " << elementName << std::endl;
	}
}

}

GraphicsDeviceBase::GraphicsDeviceBase(Window& window) noexcept :
	mWindow(window),
	mTextures(*this)
{
}

Mesh* GraphicsDeviceBase::createMesh(
	VertexFormat vertexFormat,
	u32 vertexCount,
	const float* vertices,
	u32 indexCount,
	const u32* indices) noexcept
{
	Mesh* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = mMeshes.emplace_back(createBackendMesh(
			vertexFormat,
			vertexCount,
			vertices,
			indexCount,
			indices)).get();
	GLTUT_CATCH_ALL_END("Failed to create mesh")
	return result;
}

void GraphicsDeviceBase::removeMesh(Mesh* mesh) noexcept
{
	removeElement(mMeshes, mesh, "Mesh");
}

Shader* GraphicsDeviceBase::createShader(
	const char* vertexShader,
	const char* fragmentShader) noexcept
{
	Shader* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = mShaders.emplace_back(
			createBackendShader(vertexShader, fragmentShader)).get();
	GLTUT_CATCH_ALL_END("Failed to create shader program")
	return result;
}

Shader* GraphicsDeviceBase::loadShader(
	const char* vertexShaderPath,
	const char* fragmentShaderPath) noexcept
{
	Shader* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = createShader(
			readFileToString(vertexShaderPath).c_str(),
			readFileToString(fragmentShaderPath).c_str());
	GLTUT_CATCH_ALL_END("Failed to load shader from files")
	return result;
}

void GraphicsDeviceBase::removeShader(Shader* shader) noexcept
{
	removeElement(mShaders, shader, "Shader");
}

const Texture* GraphicsDeviceBase::createSolidColorTexture(
	float r,
	float g,
	float b,
	float a) noexcept
{
	const u8 r8 = static_cast<u8>(std::clamp(r, 0.0f, 1.0f) * 255);
	const u8 g8 = static_cast<u8>(std::clamp(g, 0.0f, 1.0f) * 255);
	const u8 b8 = static_cast<u8>(std::clamp(b, 0.0f, 1.0f) * 255);
	const u8 a8 = static_cast<u8>(std::clamp(a, 0.0f, 1.0f) * 255);
	const u32 color_hex = ((u32)r8 << 24) | ((u32)g8 << 16) | ((u32)b8 << 8) | (u32)a8;

	Texture* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		if (auto findResult = mSolidColorTextures.find(color_hex);
			findResult != mSolidColorTextures.end())
		{
			return findResult->second;
		}

		const u8 colorData[] = { r8, g8, b8, a8 };
		result = getTextures()->create(
			colorData,
			{ 1, 1 },
			TextureFormat::RGBA, 
			{ TextureFilterMode::NEAREST,
			TextureFilterMode::NEAREST,
			TextureWrapMode::CLAMP_TO_EDGE });
		if (result != nullptr)
		{
			mSolidColorTextures[color_hex] = result;
		}
	GLTUT_CATCH_ALL_END("Failed to create solid color texture")
	
	return result;
}

TextureFramebuffer* GraphicsDeviceBase::createTextureFramebuffer(
	Texture* color,
	Texture* depth) noexcept
{
	TextureFramebuffer* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = mFramebuffers.emplace_back(createBackendTextureFramebuffer(
			color,
			depth)).get();
	GLTUT_CATCH_ALL_END("Failed to create framebuffer")
	return result;
}

void GraphicsDeviceBase::removeTextureFramebuffer(TextureFramebuffer* frameBuffer) noexcept
{
	removeElement(mFramebuffers, frameBuffer, "Framebuffer");
}

void GraphicsDeviceBase::bindFramebuffer(
	Framebuffer* framebuffer,
	Rectangle2u* viewport) noexcept
{
	if (framebuffer == nullptr)
	{
		return;
	}

	framebuffer->bind();
	if (viewport != nullptr)
	{
		setViewport(*viewport);
	}
	else
	{
		// If no viewport is provided, use the framebuffer size
		setViewport({ { 0, 0 }, framebuffer->getSize() });
	}
}

// End of the namespace gltut
}
