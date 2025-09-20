// OpenGL tutorials and engine (https://github.com/dmitry-sapelnikov/opengl-tutorials)
// SPDX-FileCopyrightText: 2024-2025 Dmitry Sapelnikov
// SPDX-License-Identifier: MIT

// Includes
#include "ShaderArguments.h"

namespace gltut
{

namespace
{
// Local functions
template <typename TargetType, typename T>
void addParameterValue(
	TargetType& target,
	int32 location,
	const T& value) noexcept
{
	GLTUT_ASSERT(location >= 0);
	try
	{
		// We use a simple linear search to find the location assuming that
		// the number of parameters is small enough.
		auto findResult = std::find_if(
			target.begin(), target.end(), [location](const auto& pair)
			{ return pair.first == location; });

		if (findResult != target.end())
		{
			findResult->second = value;
		}
		else
		{
			target.emplace_back(location, value);
		}
	}
	GLTUT_CATCH_ALL("Failed to set shader parameter")
}

// End of the anonymous namespace
}

// Global classes
ShaderArguments::ShaderArguments(Shader* shader) noexcept :
	mShader(shader)
{
}

Shader* ShaderArguments::getShader() const noexcept
{
	return mShader;
}

void ShaderArguments::setShader(Shader* shader) noexcept
{
	if (mShader != shader)
	{
		mParameterValues.clear();
		mShader = shader;
	}
}

int32 ShaderArguments::getParameterLocation(const char* name) const noexcept
{
	GLTUT_ASSERT_STRING(name);
	GLTUT_ASSERT(mShader != nullptr);
	return mShader->getParameterLocation(name);
}

int32 ShaderArguments::getUniformBlockIndex(const char* name) const noexcept
{
	GLTUT_ASSERT_STRING(name);
	GLTUT_ASSERT(mShader != nullptr);
	return mShader->getUniformBlockIndex(name);
}

void ShaderArguments::setInt(int32 location, int value) noexcept
{
	addParameterValue(mParameterValues, location, value);
}

void ShaderArguments::setFloat(int32 location, float value) noexcept
{
	addParameterValue(mParameterValues, location, value);
}

void ShaderArguments::setVec2(int32 location, float x, float y) noexcept
{
	addParameterValue(mParameterValues, location, std::array<float, 2> {x, y});
}

void ShaderArguments::setVec3(int32 location, float x, float y, float z) noexcept
{
	addParameterValue(mParameterValues, location, std::array<float, 3> {x, y, z});
}

void ShaderArguments::setVec4(int32 location, float x, float y, float z, float w) noexcept
{
	addParameterValue(mParameterValues, location, std::array<float, 4> {x, y, z, w});
}

void ShaderArguments::setMat3(int32 location, const float* value) noexcept
{
	addParameterValue(mParameterValues, location, Matrix3(value));
}

void ShaderArguments::setMat4(int32 location, const float* value) noexcept
{
	addParameterValue(mParameterValues, location, Matrix4(value));
}

void ShaderArguments::setUniformBlockBindingPoint(int32 location, u32 bindingPoint) noexcept
{
	addParameterValue(mUniformBlockBindingPoints, location, bindingPoint);
}

void ShaderArguments::bind() const noexcept
{
	if (mShader == nullptr)
	{
		return;
	}

	mShader->bind();
	for (const auto& [location, value] : mParameterValues)
	{
		switch (value.index())
		{
		case 0:
		{
			mShader->setInt(location, std::get<int>(value));
		}
		break;

		case 1:
		{
			mShader->setFloat(location, std::get<float>(value));
		}
		break;

		case 2:
		{
			const auto& vec2 = std::get<std::array<float, 2>>(value);
			mShader->setVec2(location, vec2[0], vec2[1]);
		}
		break;

		case 3:
		{
			const auto& vec3 = std::get<std::array<float, 3>>(value);
			mShader->setVec3(location, vec3[0], vec3[1], vec3[2]);
		}
		break;

		case 4:
		{
			const auto& vec4 = std::get<std::array<float, 4>>(value);
			mShader->setVec4(location, vec4[0], vec4[1], vec4[2], vec4[3]);
		}
		break;

		case 5:
		{
			mShader->setMat3(location, std::get<Matrix3>(value).data());
		}
		break;

		case 6:
		{
			mShader->setMat4(location, std::get<Matrix4>(value).data());
		}
		break;

		GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(value.index());
		}
	}

	for (const auto& [location, bindingPoint] : mUniformBlockBindingPoints)
	{
		mShader->setUniformBlockBindingPoint(location, bindingPoint);
	}
}

// End of the namespace gltut
}
