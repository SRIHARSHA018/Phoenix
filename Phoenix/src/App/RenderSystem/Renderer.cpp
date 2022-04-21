#include "Renderer.h"

Renderer::Renderer()
{
	//this->x_gui_manager = std::unique_ptr<GUIManager>(new GUIManager());
	this->x_scene_object_manager = std::unique_ptr<SceneObjectManager>(new SceneObjectManager());
}
void Renderer::run(GLFWwindow* window)
{
	//Rendering settings
	initRenderSettings();

	Shader shader("src/App/Shaders/GlslShaders/simple_shader.vert", "src/App/Shaders/GlslShaders/simple_shader.frag");

	//TODO:CleanUp camera class
	//TODO:Really a messy code make sure to optimize
	Camera main_cam(shader.getShaderProgramId(), glm::vec3(0.f, 0.f, 10.f));
	main_cam.projection_matrix = glm::perspective(glm::radians(main_cam.zoom), Window::getAspectRatio(window), 0.1f, 100.f);

	//Lights stuff
	glm::vec3 light_color = glm::vec3(1.f);
	glm::vec3 diffuse_color = light_color * glm::vec3(0.5f);
	glm::vec3 ambient_color = diffuse_color * glm::vec3(0.2f);
	glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 direction = glm::vec3(0.f, 0.0f, 1.f);

	DirectionalLight directional_light(ambient_color, diffuse_color, specular, direction, shader.getShaderProgramId());
	PointLight point_light(ambient_color, glm::vec3(1.f, 0.f, 1.f), specular, glm::vec3(0.f, 2.f, 0.f), shader.getShaderProgramId());
	SpotLight spot_light(ambient_color, glm::vec3(0.f, 1.f, 0.3f), specular, glm::vec3(0.f, 0.f, 0.8f), glm::vec3(0.f, 0.f, 1.f), shader.getShaderProgramId());


	//TODO:Cleanup
	ModelImporter box("src/res/skull-downloadable/source/craneo.obj", shader.getShaderProgramId());

	ModelImporter gun("src/res/BakedJinx/jinx.obj", shader.getShaderProgramId());

	//TODO:clean stuff with SceneObjectManager and cam
	//TODO:Make automatic registeration to scene eligible objects
	this->x_scene_object_manager->addSceneObject(&main_cam);
	this->x_scene_object_manager->addSceneObject(&directional_light);
	this->x_scene_object_manager->addSceneObject(&point_light);
	this->x_scene_object_manager->addSceneObject(&spot_light);
	this->x_scene_object_manager->addSceneObject(&gun);
	this->x_scene_object_manager->addSceneObject(&box);

	//TODO:make things clean from here and optimize the GUI class
	//GUI Manager
	//TODO:clean stuff Temporary
	//ButtonComponent button(window);
	//x_gui_manager->addUIComponent(&button);

	std::cout << "Phoenix online\n";

	while (!glfwWindowShouldClose(window))
	{

		clear();

		//TODO:cleanup use program id for every draw and setup calls
		shader.useShaderProgram();

		Time::updateDeltaTime();

		spot_light.setPostion(main_cam.camera_position);
		spot_light.setDirection(main_cam.camera_front);

		//TODO:make clean class of scenemangaer
		this->x_scene_object_manager->updateObjects();

		//TODO:: create a GUI element for displaying.
		//simple window style box with slider or a button 
		//on hover it would change padding
		//UI->draw(UIElementType::button);
		//x_gui_manager->UpdateUIComponents();

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
	this->x_scene_object_manager->onEvent(event);
	//this->x_gui_manager->onEvent(event);
}

Renderer::~Renderer()
{
}