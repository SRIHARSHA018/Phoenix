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

	void run(GLFWwindow* window);
	void clear();
	void swapBuffers(GLFWwindow* window);
	void pollEvents();
	void onEvent(IEvent& event);

private:
	GUIManager* x_guiManager;
	SceneManager* x_sceneManager;

	//std::unique_ptr<GUIManager> x_guiManager;
	//std::unique_ptr<SceneManager> x_sceneManager;

};
