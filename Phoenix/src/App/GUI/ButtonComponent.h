#pragma once
#include<GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "Window/WindowRender.h"
#include "IUIComponent.h"
#include "Events/MouseEvent.h"
#include "VertexBuffers/Vertexbuffer.h"
#include "Shaders/Shader.h"
#include "Shaders/UniformManager.h"

class ButtonComponent :public IUIComponent {
public:
	ButtonComponent(GLFWwindow* window);
	ButtonComponent(GLFWwindow* window, float x, float y, float width, float height);
	~ButtonComponent();

public:
	virtual void draw() override;
	virtual void onEvent(IEvent& event) override;
	virtual void update() override;

public:
	bool isMouseHovering(float xpos, float ypos);
	void createBoxTemplate();
	void updateUniforms();
	void updateConstraints(unsigned int width, unsigned int height);
	void updateMatrices();
	void paddingAnimation(float fact = 1.f);
	glm::mat4 getModelMatrix();
	glm::mat4 getProjectionMatrix();

public:
	int win_width, win_height;
	UIElementProps props;
	Shader* UI_shader;
	//TODO::vertex arrays and other stuff need to be decoupled and maintainable
	//TODO:Make it flexible so we can use.
	unsigned int vao, vbo, ibo;

private:
	glm::mat4 x_model_matrix;
	glm::mat4 x_projection_matrix;

};