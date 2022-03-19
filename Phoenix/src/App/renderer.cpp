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
    //Shader guiShader("src/App/Shaders/guiShader.vert", "src/App/Shaders/guiShader.frag");

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
    box.shaderProgramId = this->x_shader->getShaderProgramId();
    ModelImporter gun("src/res/BakedJinx/jinx.obj");
    gun.shaderProgramId = this->x_shader->getShaderProgramId();

    //TODO:clean stuff with sceneManager and cam
    this->x_sceneManager = new SceneManager();
    this->x_sceneManager->addSceneObject(&mainCam);
    this->x_sceneManager->addSceneObject(&directionalLight);
    this->x_sceneManager->addSceneObject(&pointLight);
    this->x_sceneManager->addSceneObject(&spotLight);
    this->x_sceneManager->addSceneObject(&gun);
    this->x_sceneManager->addSceneObject(&box);

    //TODO:make things clean from here and optimize the GUI class
    //GUI Manager
    //TODO:clean stuff Temporary
    //ButtonComponent button(window,0.f,20.f,10.f,10.f);
    //x_guiManager = new GUIManager();
    //ButtonComponent button(window);
    //x_guiManager->addUIComponent(&button);

    std::cout << "Phoenix online\n";
    while (!glfwWindowShouldClose(window))
    {

        clear();

        Time::updateDeltaTime();

        //TODO:cleanup use program id for every draw and setup calls
        this->x_shader->useShaderProgram();

        //TODO:make clean class of scenemangaer
        this->x_sceneManager->updateObjects();
    
        spotLight.setPostion(mainCam.cameraPosition);
        spotLight.setDirection(mainCam.cameraFront);


        //TODO:: create a GUI element for displaying.
        //simple window style box with slider or a button 
        //on hover it would change padding
        //UI->draw(UIElementType::button);
        //x_guiManager->UpdateUIComponents();

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