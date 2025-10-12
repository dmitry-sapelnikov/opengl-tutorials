#pragma once

// Includes
#include "engine/Engine.h"
#include "imgui/EngineImgui.h"

// Global classes

/// Class for GUI in the water tutorial
class WaterGui
{
public:
	/// Constructor
	WaterGui(
		gltut::EngineImgui* imgui,
		gltut::Engine* engine,
		gltut::Shader* waterShader,
		gltut::LightNode* directionalLight);

	/// Draws the GUI
	void draw();

private:
	/// Updates the light direction based on azimuth and elevation
	void updateLightDirection();

	/// Reference to the ImGui engine
	gltut::EngineImgui* mImgui;

	/// Reference to the engine
	gltut::Engine* mEngine;

	/// Reference to the water shader
	gltut::Shader* mWaterShader;

	/// Reference to the directional light
	gltut::LightNode* mDirectionalLight;

	/// Sea height
	float mSeaHeight = 0.0f;

	/// Distance at which water is considered deep
	float mDeepWaterDistance = 50.0f;

	/// Refraction scale
	float mRefractionScale = 2.0f;

	/// Number of steps for reflection tracing
	int mReflectionSteps = 16;

	/// Maximum distance for reflection tracing
	float mReflectionTraceDistance = 100.0f;

	/// Thickness for reflection ray marching
	float mReflectionThickness = 1.0f;

	/// Light azimuth angle in degrees
	float mLightAzimuth = 0.0f;

	/// Light elevation angle in degrees
	float mLightElevation = 45.0f;
};
