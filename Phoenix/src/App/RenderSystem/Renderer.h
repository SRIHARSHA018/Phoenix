#pragma once

#include "Shaders/Shader.h"
#include "Scene/SceneObjectManager.h"
#include "Camera/Camera.h"
#include "LightCasters/DirectionalLight.h"
#include "LightCasters/PointLight.h"
#include "LightCasters/SpotLight.h"
#include "Shaders/UniformManager.h"
#include "VertexBuffers/Vertexbuffer.h"
#include "VertexBuffers/VertexArray.h"
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

	std::unique_ptr<GUIManager> x_gui_manager;
	std::unique_ptr<SceneObjectManager> x_scene_object_manager;

};