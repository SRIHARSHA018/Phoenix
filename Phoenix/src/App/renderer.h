#pragma once
#include "Shaders/shader.h"
#include "SceneManager.h"
#include "camera.h"
#include "LightCasters/DirectionalLight.h"
#include "LightCasters/PointLight.h"
#include "LightCasters/SpotLight.h"
#include "UniformManager.h"
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
	std::unique_ptr<SceneManager> x_sceneManager;

};
