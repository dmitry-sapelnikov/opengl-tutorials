// Includes
#include <array>
#include <chrono>
#include <iostream>
#include <string>

#include "engine/Engine.h"
#include "engine/core/Check.h"
#include "engine/math/Rng.h"
#include "imgui/EngineImgui.h"

#include "WaterGui.h"
#include "Waves.h"

/// Vertex shader for texture-to-window rendering
static const char* WATER_VERTEX_SHADER = R"(
	#version 330 core
	layout(location = 0) in vec3 inPos;
    layout(location = 1) in vec2 inTexCoord;

    out vec2 texCoord;

	void main()
	{
		gl_Position = vec4(inPos, 1.0);
        texCoord = inTexCoord;
	};
)";

static const char* WATER_FRAGMENT_SHADER = R"(
#version 330 core

/*
 * "Seascape" by Alexander Alekseev aka TDM - 2014
 * License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * Contact: tdmaav@gmail.com
*/
 
uniform vec3      iResolution;           // viewport resolution (in pixels)
uniform float     iTime;                 // shader playback time (in seconds)

const int NUM_STEPS = 32;
const float PI	 	= 3.141592;
const float EPSILON	= 1e-3;
#define EPSILON_NRM (0.1 / iResolution.x)
//#define AA

// sea
const int ITER_GEOMETRY = 5;
const int ITER_FRAGMENT = 5;
uniform float SEA_HEIGHT;

const float SEA_CHOPPY = 3.0;
const float SEA_SPEED = 0.8;
const float SEA_FREQ = 0.16;
const vec3 SEA_BASE = vec3(0.0,0.09,0.18);
const vec3 SEA_WATER_COLOR = vec3(0.8,0.9,0.6)*0.6;
#define SEA_TIME (1.0 + iTime * SEA_SPEED)
const mat2 octave_m = mat2(1.6,1.2,-1.2,1.6);

uniform mat4 iViewMatrix;
uniform mat4 iProjectionMatrix;
uniform vec3 iCameraPosition;
uniform vec3 iLightDirection;

uniform samplerCube skyboxSampler;
uniform sampler2D colorSampler;
uniform sampler2D depthSampler;
uniform sampler2D backfaceDepthSampler;

uniform float iRefractionScale;
uniform float zNear;
uniform float zFar;
uniform float iDeepWaterDistance;

// math
float hash( vec2 p ) {
	float h = dot(p,vec2(127.1,311.7));	
    return fract(sin(h)*43758.5453123);
}

float noise( in vec2 p ) {
    vec2 i = floor( p );
    vec2 f = fract( p );	
	vec2 u = f*f*(3.0-2.0*f);
    return -1.0+2.0*mix( mix( hash( i + vec2(0.0,0.0) ), 
                     hash( i + vec2(1.0,0.0) ), u.x),
                mix( hash( i + vec2(0.0,1.0) ), 
                     hash( i + vec2(1.0,1.0) ), u.x), u.y);
}

float getGlobalDistance(float depth)
{
	return zNear * (zFar / (zFar + depth * (zNear - zFar)) - 1.0);
}

// lighting
float diffuse(vec3 n,vec3 l,float p) {
    return pow(dot(n,l) * 0.4 + 0.6,p);
}

float specular(vec3 n,vec3 l,vec3 e,float s) {    
    float nrm = (s + 8.0) / (PI * 8.0);
    return pow(max(dot(reflect(e,n),l),0.0),s) * nrm;
}

// sky
vec3 globalToScreen(vec3 p) {
	vec4 clipSpacePos = iProjectionMatrix * iViewMatrix * vec4(p, 1.0);
	clipSpacePos /= clipSpacePos.w;
	return clipSpacePos.xyz * 0.5 + 0.5;
}

uniform int iReflectionSteps;
uniform float iReflectionTraceDistance;

vec2 getScreenSpaceUV(vec3 surfaceP, vec3 e) 
{
	vec3 end = surfaceP + iReflectionTraceDistance * e;
	float stepSize = iReflectionTraceDistance / float(iReflectionSteps);

	for (int i = 1; i <= iReflectionSteps; i++)
	{
		float t = float(i) / float(iReflectionSteps);
		vec3 screenPos = globalToScreen(mix(surfaceP, end, t));
		if (!(0.0 <= screenPos.x && screenPos.x <= 1.0 &&
			  0.0 <= screenPos.y && screenPos.y <= 1.0 &&
			  screenPos.z < 1.0))
		{
			break;
		}

		float sampleDepth = getGlobalDistance(screenPos.z);
		if (sampleDepth < getGlobalDistance(texture(backfaceDepthSampler, screenPos.xy).r) + stepSize)
		{
			float depth = texture(depthSampler, screenPos.xy).r;
			if (depth < 1.0 && getGlobalDistance(depth) - stepSize < sampleDepth)
			{
				return screenPos.xy;
			}
		}
	}
	return vec2(-1.0);
}

vec3 getReflectedColor(vec3 p, vec3 e) {
	vec2 screenUV = getScreenSpaceUV(p, e);
	if (screenUV.x < 0.0)
	{
		return texture(skyboxSampler, e).rgb;
	}
	return texture(colorSampler, screenUV.xy).rgb;
}

// sky
vec3 getSkyColor(vec2 uv, vec3 e) {
	float depth = texture(depthSampler, uv).r;
	if (depth < 1.0)
	{
		return texture(colorSampler, uv).rgb;
	}
    return texture(skyboxSampler, e).rgb;
}

// sea
float sea_octave(vec2 uv, float choppy) {
    uv += noise(uv);        
    vec2 wv = 1.0-abs(sin(uv));
    vec2 swv = abs(cos(uv));    
    wv = mix(wv,swv,wv);
    return pow(1.0-pow(wv.x * wv.y,0.65),choppy);
}

float map(vec3 p) {
    float freq = SEA_FREQ;
    float amp = SEA_HEIGHT;
    float choppy = SEA_CHOPPY;
    vec2 uv = p.xz; uv.x *= 0.75;
    
    float d, h = 0.0;    
    for(int i = 0; i < ITER_GEOMETRY; i++) {        
    	d = sea_octave((uv+SEA_TIME)*freq,choppy);
    	d += sea_octave((uv-SEA_TIME)*freq,choppy);
        h += d * amp;        
    	uv *= octave_m; freq *= 1.9; amp *= 0.22;
        choppy = mix(choppy,1.0,0.2);
    }
    return p.y - h;
}

float map_detailed(vec3 p) {
    float freq = SEA_FREQ;
    float amp = SEA_HEIGHT;
    float choppy = SEA_CHOPPY;
    vec2 uv = p.xz; uv.x *= 0.75;
    
    float d, h = 0.0;    
    for(int i = 0; i < ITER_FRAGMENT; i++) {        
    	d = sea_octave((uv+SEA_TIME)*freq,choppy);
    	d += sea_octave((uv-SEA_TIME)*freq,choppy);
        h += d * amp;        
    	uv *= octave_m; freq *= 1.9; amp *= 0.22;
        choppy = mix(choppy,1.0,0.2);
    }
    return p.y - h;
}


vec3 getSeaColor(vec3 p, vec3 n, vec3 l, vec3 eye, vec3 dist) {
	// Transform point to screen space
	vec4 clipSpacePos = iProjectionMatrix * iViewMatrix * vec4(p, 1.0);
	clipSpacePos /= clipSpacePos.w;
	vec3 ndc = clipSpacePos.xyz * 0.5 + 0.5;

	// Compare depth with the depth buffer
	float sceneDepth = texture(depthSampler, ndc.xy).r;
	if (ndc.z > sceneDepth)
	{
		return texture(colorSampler, ndc.xy).rgb;
	}

    float fresnel = clamp(1.0 - dot(n, -eye), 0.0, 1.0);
    fresnel = min(fresnel * fresnel * fresnel, 0.5);

    vec3 reflected = getReflectedColor(p, reflect(eye, n));

	// refraction
	vec3 waterColor = SEA_BASE + diffuse(n, l, 80.0) * SEA_WATER_COLOR * 0.12;

	vec3 refractDir = normalize(refract(eye, n, 1.0 / 1.33));

	vec2 posDepthUV = getScreenSpaceUV(p, refractDir);
	vec3 refracted = waterColor;
	if (posDepthUV.x >= 0.0)
	{
		float posDepth = texture(depthSampler, posDepthUV).r;
		float traceDepth = getGlobalDistance(posDepth) - getGlobalDistance(ndc.z);
		float depthFactor = clamp(traceDepth / iDeepWaterDistance, 0.0, 1.0);
		refracted = mix(texture(colorSampler, posDepthUV.xy).rgb, waterColor, mix(0.3, 1.0, depthFactor));
	}

	vec3 color = mix(refracted, reflected, fresnel);
	float atten = max(1.0 - dot(dist, dist) * 0.001, 0.0);
	color += SEA_WATER_COLOR * (p.y - SEA_HEIGHT) * 0.18 * atten;
    
    color += specular(n, l, eye, 600.0 * inversesqrt(length(dist)));
    
    return color;
}

// tracing
vec3 getNormal(vec3 p, float eps) {
    vec3 n;
    n.y = map_detailed(p);    
    n.x = map_detailed(vec3(p.x+eps,p.y,p.z)) - n.y;
    n.z = map_detailed(vec3(p.x,p.y,p.z+eps)) - n.y;
    n.y = eps;
    return normalize(n);
}

float heightMapTracing(vec3 ori, vec3 dir, out vec3 p) {  
    float tm = 0.0;
    float tx = 2000.0;    
    float hx = map(ori + dir * tx);
    if(hx > 0.0) {
        p = ori + dir * tx;
        return tx;   
    }
    float hm = map(ori);    
    for(int i = 0; i < NUM_STEPS; i++) {
        float tmid = mix(tm, tx, hm / (hm - hx));
        p = ori + dir * tmid;
        float hmid = map(p);        
        if(hmid < 0.0) {
            tx = tmid;
            hx = hmid;
        } else {
            tm = tmid;
            hm = hmid;
        }        
        if(abs(hmid) < EPSILON) break;
    }
    return mix(tm, tx, hm / (hm - hx));
}

vec3 getPixel(vec2 uv, float time)
{
    // ray
    // Convert from screen space to NDC
    vec2 xy = uv * 2.0 - 1.0;
    // Convert from NDC to clip space
    vec4 ray_clip = vec4(xy, -1.0, 1.0);
    // Convert from clip space to eye space
    vec4 ray_eye = inverse(iProjectionMatrix) * ray_clip;
    ray_eye = vec4(ray_eye.xy, -1.0, 0.0);
    // Convert from eye space to world space
    vec3 dir = normalize((inverse(iViewMatrix) * ray_eye).xyz);

    vec3 ori = iCameraPosition;

    // tracing
    vec3 p;
    heightMapTracing(ori,dir,p);
    vec3 dist = p - ori;
    vec3 n = getNormal(p, dot(dist, dist) * EPSILON_NRM);
             
    // color
    return mix(
        getSkyColor(uv, dir),
        getSeaColor(p,n,-iLightDirection,dir,dist),
    	pow(smoothstep(0.0,-0.02,dir.y),0.2));
}

in vec2 texCoord;
out vec4 fragColor;

void main()
{
    vec3 color = getPixel(texCoord, 0.0f);
    // post-processing
	fragColor = vec4(pow(color,vec3(0.8)), 1.0);
}
)";

static float getInfiniteWaterDepthWaveNumber(
	float wavePeriod,
	float gravityAcceleration)
{
	GLTUT_ASSERT(wavePeriod > 0.0);
	GLTUT_ASSERT(gravityAcceleration > 0.0);
	const float frequency = float(2.0) * gltut::PI / wavePeriod;
	return (frequency * frequency) / gravityAcceleration;
}

static constexpr gltut::u32 BACKFACE_DEPTH_PASS_INDEX = 2;

/// Creates a Phong material model
gltut::PhongMaterialModel* createMaterialModel(gltut::Engine* engine)
{
	gltut::MaterialFactory* materialFactory = engine->getFactory()->getMaterial();
	gltut::PhongShaderModel* phongShader = materialFactory->createPhongShader(1, 0, 0);
	GLTUT_CHECK(phongShader, "Failed to create Phong shader");

	gltut::PhongMaterialModel* materialModel = materialFactory->createPhongMaterial(phongShader);
	GLTUT_CHECK(materialModel, "Failed to create Phong material model");

	gltut::GraphicsDevice* device = engine->getDevice();
	gltut::Texture* diffuseTexture = device->getTextures()->load(
		"assets/container2.png",
		gltut::TextureParameters(
			gltut::TextureFilterMode::LINEAR_MIPMAP,
			gltut::TextureFilterMode::LINEAR,
			gltut::TextureWrapMode::CLAMP_TO_EDGE));
	GLTUT_CHECK(diffuseTexture, "Failed to create diffuse texture");

	materialModel->setDiffuse(diffuseTexture);

	// Create a pass for reverse depth
	gltut::Material* material = materialModel->getMaterial();
	gltut::MaterialPass* backfaceDepthPass = material->createPass(
		BACKFACE_DEPTH_PASS_INDEX,
		materialFactory->getDepthShader(),
		0,
		0);

	GLTUT_CHECK(backfaceDepthPass, "Failed to create backface depth pass");
	backfaceDepthPass->setFaceCulling(gltut::FaceCullingMode::FRONT);

	return materialModel;
}

/// Creates boxes
gltut::SceneNode* createObjectsInWater(
	gltut::Engine& engine,
	const gltut::Material* material)
{
	const int COUNT = 4;
	const float GEOMETRY_SIZE = 5.0f;
	const float STRIDE = 15.0f;

	gltut::SceneNode* group = engine.getScene()->createGeometryGroup();
	GLTUT_CHECK(group, "Failed to create geometry group");

	auto* geometry = engine.getFactory()->getGeometry()->createCylinder(
		GEOMETRY_SIZE * 0.5f,
		GEOMETRY_SIZE,
		48,
		true,
		{true, true, false});
	/*auto* geometry = engine.getFactory()->getGeometry()->createBox(
		{ GEOMETRY_SIZE, GEOMETRY_SIZE, GEOMETRY_SIZE},
		{true, true, false});*/
	GLTUT_CHECK(geometry, "Failed to create geometry");

	gltut::Rng rng;
	for (int k = 0; k < 1; ++k)
	{
		for (int i = 0; i < COUNT; ++i)
		{
			for (int j = 0; j < COUNT; ++j)
			{
				const float sizeXZ = rng.nextFloat(0.25f, 0.5f);
				const gltut::Vector3 size(
					sizeXZ,
					rng.nextFloat(3.0f, 5.0f),
					sizeXZ);

				const gltut::Vector3 position(
					(i - (COUNT - 1.0f) * 0.5f + rng.nextFloat(-0.25f, 0.25f)) * STRIDE,
					-k * STRIDE - GEOMETRY_SIZE * size.y * 0.3f,
					(j - (COUNT - 1.0f) * 0.5f + rng.nextFloat(-0.25f, 0.25f)) * STRIDE);

				auto* object = engine.getScene()->createGeometry(
					geometry,
					material,
					gltut::Matrix4::transformMatrix(
						position,
						gltut::Vector3(0, rng.nextFloat(0.0f, gltut::PI * 2.0), 0),
						size),
					group);

				GLTUT_CHECK(object, "Failed to create object");
			}
		}
	}

	return group;
}

std::unique_ptr<gltut::CameraController> createCameraAndController(gltut::Engine& engine)
{
	gltut::Camera* camera = engine.getScene()->createCamera(
		{16.0f, 3.0f, 20.0f},
		{0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		45.0f,
		1.0f,
		2000.0f);
	GLTUT_CHECK(camera != nullptr, "Failed to create camera");

	std::unique_ptr<gltut::CameraController> controller(
		gltut::createMouseCameraController(*camera, 0.2f, 100.0f, 1.0f, 1000.0f));
	GLTUT_CHECK(controller.get() != nullptr, "Failed to create camera controller");

	engine.getScene()->addCameraController(controller.get());

	return controller;
}

gltut::TextureFramebuffer* createTextureFramebuffer(gltut::Engine& engine, bool useColor, bool useDepth)
{
	gltut::Factory* factory = engine.getFactory();

	gltut::Texture2* colorTexture = nullptr;
	if (useColor)
	{
		colorTexture = factory->getTexture()->createWindowSizeTexture(
			gltut::TextureFormat::RGBA);
		GLTUT_CHECK(colorTexture != nullptr, "Failed to create color texture");
	}

	gltut::Texture2* depthTexture = nullptr;

	if (useDepth)
	{
		depthTexture = factory->getTexture()->createWindowSizeTexture(
			gltut::TextureFormat::FLOAT);
		GLTUT_CHECK(depthTexture != nullptr, "Failed to create depth texture");
	}

	gltut::TextureFramebuffer* framebuffer = engine.getRenderer()->getDevice()->getFramebuffers()->create(
		colorTexture,
		depthTexture);
	GLTUT_CHECK(framebuffer, "Failed to create framebuffer");

	return framebuffer;
}

gltut::TextureCubemap* loadSkyboxTexture(gltut::Engine& engine)
{
	gltut::TextureCubemap* skyboxTexture = engine.getDevice()->getTextures()->load(
		"assets/skybox/negx.bmp",
		"assets/skybox/posx.bmp",
		"assets/skybox/negy.bmp",
		"assets/skybox/posy.bmp",
		"assets/skybox/negz.bmp",
		"assets/skybox/posz.bmp",
		gltut::TextureParameters(
			gltut::TextureFilterMode::LINEAR,
			gltut::TextureFilterMode::LINEAR,
			gltut::TextureWrapMode::CLAMP_TO_EDGE));
	GLTUT_CHECK(skyboxTexture != nullptr, "Failed to load skybox texture");
	return skyboxTexture;
}

gltut::ShaderRendererBinding* createWaterShader(gltut::Engine& engine)
{
	gltut::Shader* waterShader = engine.getDevice()->getShaders()->create(
		WATER_VERTEX_SHADER,
		WATER_FRAGMENT_SHADER);
	GLTUT_CHECK(waterShader != nullptr, "Failed to create water shader");

	waterShader->setInt("skyboxSampler", 0);
	waterShader->setInt("colorSampler", 1);
	waterShader->setInt("depthSampler", 2);
	waterShader->setInt("backfaceDepthSampler", 3);

	gltut::ShaderRendererBinding* waterShaderBinding = engine.getRenderer()->createShaderBinding(waterShader);
	GLTUT_CHECK(waterShaderBinding != nullptr, "Failed to create water shader binding");

	waterShaderBinding->bind(gltut::ShaderRendererBinding::Parameter::VIEWPOINT_VIEW_MATRIX, "iViewMatrix");
	waterShaderBinding->bind(gltut::ShaderRendererBinding::Parameter::VIEWPOINT_PROJECTION_MATRIX, "iProjectionMatrix");
	waterShaderBinding->bind(gltut::ShaderRendererBinding::Parameter::VIEWPOINT_POSITION, "iCameraPosition");

	return waterShaderBinding;
}

gltut::RenderPass* createWaterRenderPass(
	gltut::Engine& engine,
	gltut::TextureFramebuffer& framebuffer,
	gltut::TextureFramebuffer& backcullFramebuffer,
	gltut::Shader& waterShader)
{
	gltut::TextureCubemap* skyboxTexture = loadSkyboxTexture(engine);

	std::array<const gltut::Texture*, 4> textures = {
		skyboxTexture,
		framebuffer.getColor(),
		framebuffer.getDepth(),
		backcullFramebuffer.getDepth()};

	gltut::RenderPass* waterPass = engine.getFactory()->getRenderPass()->createTexturesToWindowRenderPass(
		nullptr,
		&waterShader,
		textures.data(),
		static_cast<gltut::u32>(textures.size()));

	waterPass->setViewpoint(engine.getScene()->getActiveCameraViewpoint());

	GLTUT_CHECK(waterPass != nullptr, "Failed to create water rendering pass");

	return waterPass;
}

gltut::LightNode* createSunlight(gltut::Engine& engine)
{
	gltut::LightNode* directionalLight = engine.getScene()->createLight(
		gltut::LightNode::Type::DIRECTIONAL,
		gltut::Matrix4::translationMatrix(gltut::Vector3(0.0f, 1.0f, 1.0f)));
	GLTUT_CHECK(directionalLight != nullptr, "Failed to create directional light");

	directionalLight->setAmbient(gltut::Color(0.37f, 0.37f, 0.4f));
	directionalLight->setDiffuse(gltut::Color(1.05f, 1.05f, 1.0f));
	directionalLight->setDirection(-directionalLight->getTransform().getTranslation());

	gltut::ShadowMap* shadow = engine.getFactory()->getScene()->createShadowMap(
		directionalLight,
		engine.getScene()->getRenderGroup(),
		200.0f,	   // Frustum size
		1.0f,	   // Near plane
		400.0f,	   // Far plane
		1024 * 4); // Shadow map size
	GLTUT_CHECK(shadow, "Failed to create shadow map");
	directionalLight->setShadowMap(shadow);

	return directionalLight;
}

///	The program entry point
int main()
{
	std::unique_ptr<gltut::Engine> engine;
	gltut::EngineImgui* imgui = nullptr;
	try
	{
		engine.reset(gltut::createEngine(1024, 768));
		GLTUT_CHECK(engine != nullptr, "Failed to create engine");
		engine->getWindow()->setTitle("Water");

		imgui = gltut::createEngineImgui(engine.get());
		GLTUT_CHECK(imgui != nullptr, "Failed to create ImGui engine");

		auto cameraController = createCameraAndController(*engine);
		gltut::Camera& camera = cameraController->getCamera();

		// Create something to reflect/refract
		gltut::SceneNode* objectsInWater = createObjectsInWater(
			*engine, 
			createMaterialModel(engine.get())->getMaterial());

		// Create texture framebuffer
		gltut::TextureFramebuffer* framebuffer = createTextureFramebuffer(*engine, true, true);
		engine->getSceneRenderPass()->setTarget(framebuffer);

		gltut::TextureFramebuffer* backcullFramebuffer = createTextureFramebuffer(*engine, true, true);
		engine->getRenderer()->createPass(
			engine->getScene()->getActiveCameraViewpoint(),
			engine->getScene()->getRenderGroup(),
			backcullFramebuffer,
			BACKFACE_DEPTH_PASS_INDEX,
			nullptr,
			true,
			nullptr);

		gltut::Shader* waterShader = createWaterShader(*engine)->getTarget();
		createWaterRenderPass(*engine, *framebuffer, *backcullFramebuffer, *waterShader);

		auto start = std::chrono::high_resolution_clock::now();

		waterShader->setFloat("zNear", camera.getProjection().getNearPlane());
		waterShader->setFloat("zFar", camera.getProjection().getFarPlane());

		gltut::LightNode* directionalLight = createSunlight(*engine);
		WaterGui gui(imgui, engine.get(), waterShader, directionalLight, objectsInWater);

		do
		{
			auto time = std::chrono::duration<float>(
							std::chrono::high_resolution_clock::now() - start)
							.count();
			waterShader->setFloat("iTime", time);

			waterShader->setVec3("iResolution",
								 static_cast<float>(engine->getWindow()->getSize().x),
								 static_cast<float>(engine->getWindow()->getSize().y),
								 0.0f);

			gui.draw();

		} while (engine->update());
	}
	GLTUT_APPLICATION_CATCH;

	gltut::deleteEngineImgui(imgui);
	engine.reset();

	return 0;
}
