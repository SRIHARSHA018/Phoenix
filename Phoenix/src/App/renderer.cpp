#include "renderer.h"

Renderer::Renderer()
{
	//this->x_guiManager = std::unique_ptr<GUIManager>(new GUIManager());
	this->x_sceneManager = std::unique_ptr<SceneManager>(new SceneManager());
}
void Renderer::run(GLFWwindow* window)
{
	//Rendering settings
	initRenderSettings();

	Shader shader("src/App/Shaders/glslShaders/simple_shader.vert", "src/App/Shaders/glslShaders/simple_shader.frag");

	//TODO:CleanUp camera class
	//TODO:Really a messy code make sure to optimize
	camera mainCam(shader.getShaderProgramId(), glm::vec3(0.f, 0.f, 10.f));
	mainCam.projectionMatrix = glm::perspective(glm::radians(mainCam.zoom), windowRender::getAspectRatio(window), 0.1f, 100.f);

	//Lights stuff
	glm::vec3 lightColor = glm::vec3(1.f);
	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
	glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 direction = glm::vec3(0.f, 0.0f, 1.f);

	DirectionalLight directionalLight(ambientColor, diffuseColor, specular, direction, shader.getShaderProgramId());
	PointLight pointLight(ambientColor, glm::vec3(1.f, 0.f, 1.f), specular, glm::vec3(0.f, 2.f, 0.f), shader.getShaderProgramId());
	SpotLight spotLight(ambientColor, glm::vec3(0.f, 1.f, 0.3f), specular, glm::vec3(0.f, 0.f, 0.8f), glm::vec3(0.f, 0.f, 1.f), shader.getShaderProgramId());


	//TODO:Cleanup
	ModelImporter box("src/res/skull-downloadable/source/craneo.obj", shader.getShaderProgramId());

	ModelImporter gun("src/res/BakedJinx/jinx.obj", shader.getShaderProgramId());

	//TODO:clean stuff with sceneManager and cam
	//TODO:Make automatic registeration to scene eligible objects
	this->x_sceneManager->addSceneObject(&mainCam);
	this->x_sceneManager->addSceneObject(&directionalLight);
	this->x_sceneManager->addSceneObject(&pointLight);
	this->x_sceneManager->addSceneObject(&spotLight);
	this->x_sceneManager->addSceneObject(&gun);
	this->x_sceneManager->addSceneObject(&box);

	//TODO:make things clean from here and optimize the GUI class
	//GUI Manager
	//TODO:clean stuff Temporary
	//ButtonComponent button(window);
	//x_guiManager->addUIComponent(&button);

	std::cout << "Phoenix online\n";

	while (!glfwWindowShouldClose(window))
	{

		clear();

		//TODO:cleanup use program id for every draw and setup calls
		shader.useShaderProgram();

		Time::updateDeltaTime();

		spotLight.setPostion(mainCam.cameraPosition);
		spotLight.setDirection(mainCam.cameraFront);

		//TODO:make clean class of scenemangaer
		this->x_sceneManager->updateObjects();

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

void Renderer::swapBuffers(GLFWwindow* window)
{
	glfwSwapBuffers(window);
}
void Renderer::pollEvents()
{
	glfwPollEvents();
}

void Renderer::initRenderSettings()
{
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
}

void Renderer::onEvent(IEvent& event)
{
	this->x_sceneManager->onEvent(event);
	//this->x_guiManager->onEvent(event);
}



Renderer::~Renderer()
{
}