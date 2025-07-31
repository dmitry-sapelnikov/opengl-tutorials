// Includes
#include "SceneShaderBindingC.h"
#include "engine/renderer/shader/Shader.h"
#include "engine/scene/Scene.h"

namespace gltut
{

// Local functions
namespace
{

static std::string getFullParameter(
	const std::pair<std::string, std::string>& parameterAttribute,
	u32 index)
{
	const auto& [parameter, attribute] = parameterAttribute;
	if (parameter.empty())
	{
		return "";
	}
	return
		parameter + "[" + std::to_string(index) + "]" +
		(attribute.empty() ? "" : "." + attribute);
}

static void setVector3(
	Shader& shader,
	const std::pair<std::string, std::string>& parameterAttribute,
	u32 index,
	const Vector3& value) noexcept
{
	if (const auto fullName = getFullParameter(parameterAttribute, index);
		!fullName.empty())
	{
		shader.setVec3(fullName.c_str(), value.x, value.y, value.z);
	}
}

static void setFloat(
	Shader& shader,
	const std::pair<std::string, std::string>& parameterAttribute,
	u32 index,
	float value) noexcept
{
	if (const auto fullName = getFullParameter(parameterAttribute, index);
		!fullName.empty())
	{
		shader.setFloat(fullName.c_str(), value);
	}
}

}

// Global classes
Shader* SceneShaderBindingC::getShader() const noexcept
{
	return mShader;
}

void SceneShaderBindingC::setShader(
	Shader* shader,
	bool resetParameters) noexcept
{
	mShader = shader;
	if (resetParameters)
	{
		for (auto& name : mShaderParameters)
		{
			name.clear();
		}
	}
}

const char* SceneShaderBindingC::getBoundShaderParameter(
	Parameter parameter) const noexcept
{
	const auto& result = mShaderParameters[static_cast<size_t>(parameter)];
	return result.empty() ? nullptr : result.c_str();
}

void SceneShaderBindingC::bind(
	Parameter parameter,
	const char* shaderParameter) noexcept
{
	const size_t index = static_cast<size_t>(parameter);
	const std::string param((shaderParameter != nullptr) ? shaderParameter : "");

	mShaderParameters[index] = param;

	// Find the first dot in the shader parameter name
	size_t dotPos = param.find('.');
	if (dotPos != std::string::npos)
	{
		// Split the shader parameter name into two parts
		mShaderParameterParts[index] = { param.substr(0, dotPos), param.substr(dotPos + 1) };
	}
	else
	{
		// No dot found, use the whole name as the first part
		mShaderParameterParts[index] = { param, "" };
	}

	if (!mShaderParameterParts[index].second.empty())
	{
		GLTUT_ASSERT(!mShaderParameterParts[index].first.empty());
	}
}

void SceneShaderBindingC::activate(const Scene* scene) const noexcept
{
	if (mShader == nullptr ||
		scene == nullptr ||
		scene->getActiveCamera() == nullptr)
	{
		return;
	}

	mShader->activate();

	const Camera* camera = scene->getActiveCamera();

	if (const char* cameraView = getBoundShaderParameter(Parameter::CAMERA_VIEW_MATRIX);
		cameraView != nullptr)
	{
		mShader->setMat4(cameraView, camera->getView().getMatrix().data());
	}

	if (const char* cameraProjection = getBoundShaderParameter(Parameter::CAMERA_PROJECTION_MATRIX);
		cameraProjection != nullptr)
	{
		mShader->setMat4(cameraProjection, camera->getProjection().getMatrix().data());
	}

	if (const char* cameraPosition = getBoundShaderParameter(Parameter::CAMERA_POSITION);
		cameraPosition != nullptr)
	{
		const Vector3& position = camera->getView().getPosition();
		mShader->setVec3(cameraPosition, position.x, position.y, position.z);
	}

	activateLights(*scene);
}


/// Activates the shader binding for a scene object
void SceneShaderBindingC::activate(const GeometryNode* node) const noexcept
{
	if (mShader == nullptr || node == nullptr)
	{
		return;
	}

	mShader->activate();

	if (const char* objectMatrix = getBoundShaderParameter(Parameter::GEOMETRY_MATRIX);
		objectMatrix != nullptr)
	{
		mShader->setMat4(objectMatrix, node->getGlobalTransform().data());
	}

	if (const char* objectNormalMatrix = getBoundShaderParameter(Parameter::GEOMETRY_NORMAL_MATRIX);
		objectNormalMatrix != nullptr)
	{
		const Matrix3 normalMatrix = getNormalMatrix(node->getGlobalTransform().getMatrix3());
		mShader->setMat3(objectNormalMatrix, normalMatrix.data());
	}
}

void SceneShaderBindingC::activateLight(
	const LightNode& light,
	u32 lightInd,
	SceneShaderBinding::Parameter position,
	SceneShaderBinding::Parameter ambientColor,
	SceneShaderBinding::Parameter diffuseColor,
	SceneShaderBinding::Parameter specularColor) const noexcept
{
	GLTUT_ASSERT(mShader != nullptr);

	setVector3(
		*mShader,
		getShaderParameterParts(position),
		lightInd,
		light.getGlobalTransform().getTranslation());

	setVector3(
		*mShader,
		getShaderParameterParts(ambientColor),
		lightInd,
		toVector3(light.getAmbient()));

	setVector3(
		*mShader,
		getShaderParameterParts(diffuseColor),
		lightInd,
		toVector3(light.getDiffuse()));

	setVector3(
		*mShader,
		getShaderParameterParts(specularColor),
		lightInd,
		toVector3(light.getSpecular()));
}

void SceneShaderBindingC::activateLights(const Scene& scene) const
{
	u32 directionalInd = 0;
	u32 pointInd = 0;
	u32 spotInd = 0;

	for (u32 lightInd = 0; lightInd < scene.getLightCount(); ++lightInd)
	{
		const LightNode* light = scene.getLight(lightInd);
		if (light == nullptr)
		{
			continue;
		}

		switch (light->getType())
		{
		case LightNode::Type::DIRECTIONAL:
		{
			activateLight(
				*light,
				directionalInd,
				Parameter::DIRECTIONAL_LIGHT_POSITION,
				Parameter::DIRECTIONAL_LIGHT_AMBIENT_COLOR,
				Parameter::DIRECTIONAL_LIGHT_DIFFUSE_COLOR,
				Parameter::DIRECTIONAL_LIGHT_SPECULAR_COLOR);

			setVector3(
				*mShader,
				getShaderParameterParts(Parameter::DIRECTIONAL_LIGHT_DIRECTION),
				lightInd,
				light->getGlobalDirection());

			++directionalInd;
		}
		break;

		case LightNode::Type::POINT:
		{
			activateLight(
				*light,
				pointInd,
				Parameter::POINT_LIGHT_POSITION,
				Parameter::POINT_LIGHT_AMBIENT_COLOR,
				Parameter::POINT_LIGHT_DIFFUSE_COLOR,
				Parameter::POINT_LIGHT_SPECULAR_COLOR);

			++pointInd;
		}
		break;

		case LightNode::Type::SPOT:
		{
			const Parameter direction = Parameter::SPOT_LIGHT_DIRECTION;
			activateLight(
				*light,
				spotInd,
				Parameter::SPOT_LIGHT_POSITION,
				Parameter::SPOT_LIGHT_AMBIENT_COLOR,
				Parameter::SPOT_LIGHT_DIFFUSE_COLOR,
				Parameter::SPOT_LIGHT_SPECULAR_COLOR);

			setVector3(
				*mShader,
				getShaderParameterParts(Parameter::SPOT_LIGHT_DIRECTION),
				spotInd,
				light->getGlobalDirection());

			setFloat(
				*mShader,
				getShaderParameterParts(Parameter::SPOT_LIGHT_INNER_ANGLE_COS),
				spotInd,
				std::cos(light->getInnerAngle()));

			setFloat(
				*mShader,
				getShaderParameterParts(Parameter::SPOT_LIGHT_OUTER_ANGLE_COS),
				spotInd,
				std::cos(light->getOuterAngle()));

			++spotInd;
		}
		break;

		GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(light->getType())
		}
	}
}

const SceneShaderBindingC::ShaderParamterParts& SceneShaderBindingC::getShaderParameterParts(
	Parameter parameter) const noexcept
{
	return mShaderParameterParts[static_cast<size_t>(parameter)];
}

// End of the namespace gltut
}
