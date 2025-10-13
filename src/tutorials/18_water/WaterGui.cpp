// Includes
#include "WaterGui.h"

// Global classes
WaterGui::WaterGui(
	gltut::EngineImgui* imgui,
	gltut::Engine* engine,
	gltut::Shader* waterShader,
	gltut::LightNode* directionalLight,
	gltut::SceneNode* objectsInWater) :

	mImgui(imgui),
	mEngine(engine),
	mWaterShader(waterShader),
	mDirectionalLight(directionalLight),
	mObjectsInWater(objectsInWater)
{
	mWaterShader->setInt("iReflectionSteps", mTraceSteps);
	mWaterShader->setFloat("iReflectionTraceDistance", mTraceDistance);
	mWaterShader->setFloat("iReflectionThickness", mTraceThickness);
	mWaterShader->setFloat("iRefractionScale", mRefractionScale);
	mWaterShader->setFloat("iDeepWaterDistance", mDeepWaterDistance);
	mWaterShader->setFloat("SEA_HEIGHT", mSeaHeight);

	updateLightDirection();
}

void WaterGui::draw()
{
	mImgui->newFrame();
	ImGui::SetNextWindowPos({10, 10}, ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize({300, 400}, ImGuiCond_FirstUseEver);

	ImGui::Begin("Settings");
	ImGui::Text("FPS: %u", mEngine->getWindow()->getFPS());

	ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);
	if (ImGui::CollapsingHeader("Water", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::SliderFloat("Sea Height", &mSeaHeight, 0.0f, 1.0f))
		{
			mWaterShader->setFloat("SEA_HEIGHT", mSeaHeight);
		}

		if (ImGui::CollapsingHeader("Reflection", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::SliderInt("Steps", &mTraceSteps, 1, 256))
			{
				mWaterShader->setInt("iReflectionSteps", mTraceSteps);
			}
			if (ImGui::SliderFloat("Trace Distance", &mTraceDistance, 1.0f, 500.0f))
			{
				mWaterShader->setFloat("iReflectionTraceDistance", mTraceDistance);
			}
			if (ImGui::SliderFloat("Thickness", &mTraceThickness, 0.1f, 10.0f))
			{
				mWaterShader->setFloat("iReflectionThickness", mTraceThickness);
			}
		}

		if (ImGui::CollapsingHeader("Refraction", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::SliderFloat("Deep Water Distance", &mDeepWaterDistance, 1.0f, 200.0f))
			{
				mWaterShader->setFloat("iDeepWaterDistance", mDeepWaterDistance);
			}

			if (ImGui::SliderFloat("Refraction Scale", &mRefractionScale, 0.0f, 10.0f))
			{
				mWaterShader->setFloat("iRefractionScale", mRefractionScale);
			}
		}
	}

	if (ImGui::CollapsingHeader("Sun", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::SliderFloat("Azimuth", &mLightAzimuth, -180.0f, 180.0f))
		{
			updateLightDirection();
		}

		if (ImGui::SliderFloat("Elevation", &mLightElevation, 0.0f, 89.0f))
		{
			updateLightDirection();
		}
	}

	if (ImGui::CollapsingHeader("Objects in Water", ImGuiTreeNodeFlags_DefaultOpen))
	{
		const bool yScaleChanged = ImGui::SliderFloat("Y Scale", &mObjectsInWaterScaleY, 0.1, 5.0f);
		const bool transformChanged = ImGui::SliderFloat("Y Position", &mObjectsInWaterY, -20.0f, 20.0f);
		const bool rotationChanged = ImGui::SliderFloat("X Rotation", &mObjectsInWaterRotationX, -180.0f, 180.0f);

		if (yScaleChanged || transformChanged || rotationChanged)
		{
			mObjectsInWater->setTransform(
				gltut::Matrix4::translationMatrix({0.0f, mObjectsInWaterY, 0.0f}) *
				gltut::Matrix4::rotationMatrix({gltut::toRadians(mObjectsInWaterRotationX), 0.0f, 0.0f}) *
				gltut::Matrix4::scaleMatrix({1.0f, mObjectsInWaterScaleY, 1.0f}));
		}
	}

	ImGui::End();
}

void WaterGui::updateLightDirection()
{
	const float azimuthRad = gltut::toRadians(mLightAzimuth);
	const float elevationRad = gltut::toRadians(mLightElevation);
	const gltut::Vector3 direction = gltut::setDistanceAzimuthInclination(
		{1.0f,
		 azimuthRad,
		 elevationRad});

	const gltut::Vector3 lightDirection(-direction.x, -direction.z, -direction.y);
	mDirectionalLight->setTransform(gltut::Matrix4::translationMatrix(200.0f * -lightDirection));
	mDirectionalLight->setDirection(lightDirection);
	mWaterShader->setVec3("iLightDirection", lightDirection.x, lightDirection.y, lightDirection.z);
}
