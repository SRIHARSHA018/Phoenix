#pragma once

#include "Shaders/shader.h"
#include "Scene/SceneObjectManager.h"
#include "Camera/camera.h"
#include "LightCasters/DirectionalLight.h"
#include "LightCasters/PointLight.h"
#include "LightCasters/SpotLight.h"
#include "Shaders/UniformManager.h"
#include "vertexBuffers/vertexbuffer.h"
#include "vertexBuffers/vertexArray.h"
#include "ModelImporters/ModelImporter.h"
#include "Materials/TexturedMaterial.h"
#include "GUI/ButtonComponent.h"
#include "GUI/GUIManager.h"


class Renderer
{
public:
	Renderer();
	~Renderer();

public:
	void clear();
	void pollEvents();
	void initRenderSettings();
	void run(GLFWwindow* window);
	void swapBuffers(GLFWwindow* window);
	void onEvent(IEvent& event);

private:

	std::unique_ptr<GUIManager> x_guiManager;
	std::unique_ptr<SceneObjectManager> x_SceneObjectManager;

};