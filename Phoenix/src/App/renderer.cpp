#include "renderer.h"
float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.f,0.f,-1.f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.f,0.f,-1.f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.f,0.f,-1.f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.f,0.f,-1.f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.f,0.f,-1.f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.f,0.f,-1.f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.f,0.f, 1.f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f,0.f, 1.f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.f,0.f, 1.f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.f,0.f, 1.f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.f,0.f, 1.f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.f,0.f, 1.f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.f,0.f,0.f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.f,0.f,0.f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.f,0.f,0.f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.f,0.f,0.f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.f,0.f,0.f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.f,0.f,0.f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.f,0.f, 0.f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.f,0.f, 0.f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.f,0.f, 0.f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.f,0.f, 0.f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.f,0.f, 0.f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.f,0.f, 0.f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.f,-1.f,0.f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.f,-1.f,0.f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f,-1.f,0.f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f,-1.f,0.f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.f,-1.f,0.f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.f,-1.f,0.f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.f,1.f,0.f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.f,1.f,0.f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.f,1.f,0.f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.f,1.f,0.f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.f,1.f,0.f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.f,1.f,0.f
};

void Renderer::run(GLFWwindow* window)
{
    this->x_shader = new Shader("src/App/Shaders/simple_shader.vert", "src/App/Shaders/simple_shader.frag");
    Shader guiShader("src/App/Shaders/guiShader.vert", "src/App/Shaders/guiShader.frag");

    //TODO:CleanUp camera class
    camera mainCam(glm::vec3(0.f,0.f,10.f));
    mainCam.projectionMatrix = glm::perspective(glm::radians(mainCam.zoom), windowRender::getAspectRatio(window),0.1f,100.f);
    mainCam.shaderProgramId = this->x_shader->getShaderProgramId();

    //TODO:DirectionalLight class
    glm::vec3 lightColor = glm::vec3(1.f);
    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
    glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 direction = glm::vec3(0.f, 0.0f, 1.f);

    //TODO: Directional light
    DirectionalLight directionalLight(ambientColor,diffuseColor,specular,direction,this->x_shader->getShaderProgramId());

    //TODO:point light cleanup
    PointLight pointLight(ambientColor, glm::vec3(1.f, 0.f, 1.f),specular,glm::vec3(0.f,2.f,0.f),this->x_shader->getShaderProgramId());

    //TODO:spotLight cleanup
    SpotLight spotLight(ambientColor,glm::vec3(0.f,1.f,0.3f),specular,glm::vec3(0.f,0.f,0.8f),glm::vec3(0.f,0.f,1.f),this->x_shader->getShaderProgramId());


    //TODO:Cleanup
    ModelImporter box("src/res/skull-downloadable/source/craneo.obj");
    ModelImporter gun("src/res/BakedJinx/jinx.obj");

    glm::vec3 gunPosition = glm::vec3(0.f);
    glm::vec3 gunRotation = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 gunScale = glm::vec3(1.f);

    glm::vec3 boxPosition = glm::vec3(0.f,0.f,-10.f);
    glm::vec3 boxRotation = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 boxScale = glm::vec3(1.f);


    //TODO:clean stuff with sceneManager and cam
    this->x_sceneManager = new SceneManager();
    this->x_sceneManager->addSceneObject(&mainCam);
    this->x_sceneManager->addSceneObject(&directionalLight);
    this->x_sceneManager->addSceneObject(&pointLight);
    this->x_sceneManager->addSceneObject(&spotLight);

    //TODO:make things clean from here and optimize the GUI class
    //GUI Manager
    //TODO:clean stuff Temporary
    //ButtonComponent button(window,0.f,20.f,10.f,10.f);
    x_guiManager = new GUIManager();
    ButtonComponent button(window);
    x_guiManager->addUIComponent(&button);

    std::cout << "Phoenix online\n";
    while (!glfwWindowShouldClose(window))
    {

        clear();

        Time::updateDeltaTime();

        this->x_shader->useShaderProgram();

        //TODO:make clean class of scenemangaer
        this->x_sceneManager->UpdateObjects();
    
        spotLight.setPostion(mainCam.cameraPosition);
        spotLight.setDirection(mainCam.cameraFront);


        glm::mat4 boxModel = glm::mat4(1.f);
        boxModel = glm::scale(boxModel, boxScale);
        boxModel = glm::rotate(boxModel, glm::radians(boxRotation.x), glm::vec3(1.f, 0.f, 0.f));
        boxModel = glm::rotate(boxModel, glm::radians(boxRotation.z), glm::vec3(0.f, 0.f, 1.f));
        boxModel = glm::rotate(boxModel, glm::radians(boxRotation.y), glm::vec3(0.f, 1.f, 0.f));
        boxModel = glm::translate(boxModel, boxPosition);
        this->x_glUniformsManager->setUniformMatrix4fv("model", this->x_shader->getShaderProgramId(), glm::value_ptr(boxModel));

        box.draw(this->x_shader->getShaderProgramId());
        
        glm::mat4 gunModel = glm::mat4(1.f);
        gunModel = glm::scale(gunModel, gunScale);
        gunModel = glm::rotate(gunModel, glm::radians(gunRotation.x), glm::vec3(1.f, 0.f, 0.f));
        gunModel = glm::rotate(gunModel, glm::radians(gunRotation.z), glm::vec3(0.f, 0.f, 1.f));
        gunModel = glm::rotate(gunModel, glm::radians(gunRotation.y), glm::vec3(0.f, 1.f, 0.f));
        gunModel = glm::translate(gunModel, gunPosition);
        this->x_glUniformsManager->setUniformMatrix4fv("model", this->x_shader->getShaderProgramId(), glm::value_ptr(gunModel));

        gun.draw(this->x_shader->getShaderProgramId());


        //TODO:: create a GUI element for displaying.
        //simple window style box with slider or a button 
        //on hover it would change padding
        //UI->draw(UIElementType::button);
        x_guiManager->UpdateUIComponents();

        swapBuffers(window);
        pollEvents();
    }
}


void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Renderer::swapBuffers(GLFWwindow *window)
{
    glfwSwapBuffers(window);
}
void Renderer::pollEvents()
{
    glfwPollEvents();
}

void Renderer::onEvent(IEvent& event)
{
    this->x_sceneManager->onEvent(event);
   //this->x_guiManager->onEvent(event);
}

Renderer::~Renderer()
{
    delete this->x_sceneManager;
    //delete this->x_guiManager;
    delete this->x_shader;
}