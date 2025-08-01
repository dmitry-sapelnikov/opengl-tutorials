// Includes
#include "RendererBase.h"

#include <iostream>
#include "../core/File.h"
#include "./texture/stb_image.h"

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

Mesh* RendererBase::createMesh(
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

void RendererBase::removeMesh(Mesh* mesh) noexcept
{
	removeElement(mMeshes, mesh, "Mesh");
}

Shader* RendererBase::createShader(
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

Shader* RendererBase::loadShader(
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

void RendererBase::removeShader(Shader* shader) noexcept
{
	removeElement(mShaders, shader, "Shader");
}

Texture* RendererBase::createTexture(
	const void* data,
	u32 width,
	u32 height,
	Texture::Format format,
	Texture::FilterMode minFilter,
	Texture::FilterMode magFilter,
	Texture::WrapMode wrapMode) noexcept
{
	Texture* result = nullptr;
	GLTUT_CATCH_ALL_BEGIN
		result = mTextures.emplace_back(createBackendTexture(
			data,
			width,
			height,
			format,
			minFilter,
			magFilter,
			wrapMode)).get();
	GLTUT_CATCH_ALL_END("Failed to create texture from data")
	return result;
}

Texture* RendererBase::loadTexture(
	const char* imagePath,
	Texture::FilterMode minFilter,
	Texture::FilterMode magFilter,
	Texture::WrapMode wrapMode) noexcept
{
	stbi_set_flip_vertically_on_load(true);
	int width = 0;
	int height = 0;
	int channels = 0;
	void* data = stbi_load(imagePath, &width, &height, &channels, 0);
	if (data == nullptr)
	{
		std::cerr << "Failed to load the image: " << imagePath << std::endl;
		stbi_image_free(data);
		return nullptr;
	}

	if (channels != 3 && channels != 4)
	{
		std::cerr << "Unsupported image format in: " << imagePath << std::endl;
		stbi_image_free(data);
		return nullptr;
	}

	Texture* result = createTexture(
		data,
		width,
		height,
		channels == 3 ? Texture::Format::RGB : Texture::Format::RGBA,
		minFilter,
		magFilter,
		wrapMode);
	
	stbi_image_free(data);
	return result;
}

Texture* RendererBase::createSolidColorTexture(
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
		result = createTexture(
			colorData,
			1U,
			1U,
			Texture::Format::RGBA, 
			Texture::FilterMode::NEAREST,
			Texture::FilterMode::NEAREST,
			Texture::WrapMode::CLAMP_TO_EDGE);
		if (result != nullptr)
		{
			mSolidColorTextures[color_hex] = result;
		}
	GLTUT_CATCH_ALL_END("Failed to create solid color texture")
	
	return result;
}

void RendererBase::removeTexture(Texture* texture) noexcept
{
	// If the texture is a solid color texture, remove it from the map
	GLTUT_CATCH_ALL_BEGIN
		auto findResult = std::find_if(
			mSolidColorTextures.begin(),
			mSolidColorTextures.end(),
			[&texture](const auto& pair)
			{
				return pair.second == texture;
			});

		if (findResult != mSolidColorTextures.end())
		{
			mSolidColorTextures.erase(findResult);
		}
	GLTUT_CATCH_ALL_END("Failed to remove solid color texture from the map")
	removeElement(mTextures, texture, "Texture");
}

void RendererBase::onEvent(const Event& event) noexcept
{
	if (event.type == Event::Type::WINDOW_RESIZE)
	{
		clear();
		onResize(event.windowResize.size);
	}
}

// End of the namespace gltut
}
