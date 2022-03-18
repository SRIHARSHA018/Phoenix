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
#include "windowRender.h"
#include "GUI/ButtonComponent.h"
#include "GUI/GUIManager.h"


class Renderer
{
public:
    ~Renderer();

    void run(GLFWwindow* window);
    void clear();
    void swapBuffers(GLFWwindow *window);
    void pollEvents();
    void onEvent(IEvent& event);
    
private:
    Shader* x_shader;
    GUIManager* x_guiManager;
    SceneManager* x_sceneManager;
    UniformManager *x_glUniformsManager = UniformManager::getUniformManager();

};
