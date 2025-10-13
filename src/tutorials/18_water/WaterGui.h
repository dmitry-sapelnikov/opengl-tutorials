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
		gltut::LightNode* directionalLight,
		gltut::Texture2* backfaceTexture); 

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
	float mSeaHeight = 0.2f;

	/// Distance at which water is considered deep
	float mDeepWaterDistance = 15.0f;

	/// Refraction scale
	float mRefractionScale = 2.0f;

	/// Number of steps for reflection tracing
	int mTraceSteps = 50;

	/// Maximum distance for reflection/refraction ray marching
	float mTraceDistance = 200.0f;

	/// Thickness for reflection/refraction ray marching
	float mTraceThickness = 2.0f;

	/// Light azimuth angle in degrees
	float mLightAzimuth = 0.0f;

	/// Light elevation angle in degrees
	float mLightElevation = 45.0f;

	gltut::Texture2* mBackfaceTexture;
};
