// Includes
#include "SceneShaderBindingC.h"
#include "engine/graphics/shader/Shader.h"
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

static void setMatrix4(
	Shader& shader,
	const std::pair<std::string, std::string>& parameterAttribute,
	u32 index,
	const Matrix4& value) noexcept
{
	if (const auto fullName = getFullParameter(parameterAttribute, index);
		!fullName.empty())
	{
		shader.setMat4(fullName.c_str(), value.data());
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
void SceneShaderBindingC::update(const Scene* scene) const noexcept
{
	if (getShader() == nullptr || scene == nullptr)
	{
		return;
	}
	getShader()->bind();
	updateLights(*scene);
}

void SceneShaderBindingC::updateLight(
	const LightNode& light,
	u32 lightInd,
	SceneShaderBinding::Parameter position,
	SceneShaderBinding::Parameter ambientColor,
	SceneShaderBinding::Parameter diffuseColor,
	SceneShaderBinding::Parameter specularColor) const noexcept
{
	Shader* shader = getShader();
	GLTUT_ASSERT(shader != nullptr);

	setVector3(
		*shader,
		getShaderParameterParts(position),
		lightInd,
		light.getGlobalTransform().getTranslation());

	setVector3(
		*shader,
		getShaderParameterParts(ambientColor),
		lightInd,
		toVector3(light.getAmbient()));

	setVector3(
		*shader,
		getShaderParameterParts(diffuseColor),
		lightInd,
		toVector3(light.getDiffuse()));

	setVector3(
		*shader,
		getShaderParameterParts(specularColor),
		lightInd,
		toVector3(light.getSpecular()));
}

void SceneShaderBindingC::updateLights(const Scene& scene) const
{
	Shader* shader = getShader();
	GLTUT_ASSERT(shader != nullptr);

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
			updateLight(
				*light,
				directionalInd,
				Parameter::DIRECTIONAL_LIGHT_POSITION,
				Parameter::DIRECTIONAL_LIGHT_AMBIENT_COLOR,
				Parameter::DIRECTIONAL_LIGHT_DIFFUSE_COLOR,
				Parameter::DIRECTIONAL_LIGHT_SPECULAR_COLOR);

			setVector3(
				*shader,
				getShaderParameterParts(Parameter::DIRECTIONAL_LIGHT_DIRECTION),
				lightInd,
				light->getGlobalDirection());

			setMatrix4(
				*shader,
				getShaderParameterParts(Parameter::DIRECTIONAL_LIGHT_SHADOW_MATRIX),
				directionalInd,
				light->getShadowMap() != nullptr ?
					light->getShadowMap()->getShadowMatrix() :
					// Set zero matrix
					Matrix4());
			++directionalInd;
		}
		break;

		case LightNode::Type::POINT:
		{
			updateLight(
				*light,
				pointInd,
				Parameter::POINT_LIGHT_POSITION,
				Parameter::POINT_LIGHT_AMBIENT_COLOR,
				Parameter::POINT_LIGHT_DIFFUSE_COLOR,
				Parameter::POINT_LIGHT_SPECULAR_COLOR);

			setFloat(
				*shader,
				getShaderParameterParts(Parameter::POINT_LIGHT_LINEAR_ATTENUATION),
				spotInd,
				light->getLinearAttenuation());

			setFloat(
				*shader,
				getShaderParameterParts(Parameter::POINT_LIGHT_QUADRATIC_ATTENUATION),
				spotInd,
				light->getQuadraticAttenuation());

			++pointInd;
		}
		break;

		case LightNode::Type::SPOT:
		{
			const Parameter direction = Parameter::SPOT_LIGHT_DIRECTION;
			updateLight(
				*light,
				spotInd,
				Parameter::SPOT_LIGHT_POSITION,
				Parameter::SPOT_LIGHT_AMBIENT_COLOR,
				Parameter::SPOT_LIGHT_DIFFUSE_COLOR,
				Parameter::SPOT_LIGHT_SPECULAR_COLOR);

			setVector3(
				*shader,
				getShaderParameterParts(Parameter::SPOT_LIGHT_DIRECTION),
				spotInd,
				light->getGlobalDirection());

			setFloat(
				*shader,
				getShaderParameterParts(Parameter::SPOT_LIGHT_INNER_ANGLE_COS),
				spotInd,
				std::cos(light->getInnerAngle()));

			setFloat(
				*shader,
				getShaderParameterParts(Parameter::SPOT_LIGHT_OUTER_ANGLE_COS),
				spotInd,
				std::cos(light->getOuterAngle()));

			setFloat(
				*shader,
				getShaderParameterParts(Parameter::SPOT_LIGHT_LINEAR_ATTENUATION),
				spotInd,
				light->getLinearAttenuation());

			setFloat(
				*shader,
				getShaderParameterParts(Parameter::SPOT_LIGHT_QUADRATIC_ATTENUATION),
				spotInd,
				light->getQuadraticAttenuation());

			setMatrix4(
				*shader,
				getShaderParameterParts(Parameter::SPOT_LIGHT_SHADOW_MATRIX),
				spotInd,
				light->getShadowMap() != nullptr ?
					light->getShadowMap()->getShadowMatrix() :
					// Set zero matrix
					Matrix4());
			++spotInd;
		}
		break;

		GLTUT_UNEXPECTED_SWITCH_DEFAULT_CASE(light->getType())
		}
	}
}

// End of the namespace gltut
}
