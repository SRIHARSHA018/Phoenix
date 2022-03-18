#include "ButtonComponent.h"
#include <iostream>

float boxVertices[] =
{
	-0.5f, 0.5f,
	 0.5f, 0.5f,
	 -0.5f,-0.5f,
	 0.5f,-0.5f
};
unsigned int boxIndices[] =
{
	0,1,2,
	1,2,3
};

//TODO: Optimize and cleanup stuff in here 
//Because its working now 
//  ^   ^
//    !
//  <--->
ButtonComponent::ButtonComponent(GLFWwindow* window)
{
	glfwGetFramebufferSize(window, &winwidth, &winHeight);
	props.x = 0.f;
	props.y = 0.5f;
	props.width = 0.2f;
	props.height =props.width;
	updateMatrices();
	createBoxTemplate();
}

ButtonComponent::ButtonComponent(GLFWwindow* window, float x, float y, float width, float height)
{
	glfwGetFramebufferSize(window, &winwidth, &winHeight);
	props.x = x;
	props.y = y;
	props.width = width;
	props.height = height;
	updateMatrices();
}

ButtonComponent::~ButtonComponent()
{
	glDeleteVertexArrays(1, &vao);
	if (this->UIshader) {
		delete UIshader;
	}
}

void ButtonComponent::draw()
{	
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void ButtonComponent::onEvent(IEvent& event)
{
	switch (event.getEventType())
	{
		case EventType::MOUSE_MOVED: 
		{

			auto xpos = static_cast<MouseMovedEvent&>(event).GetCursorX();
			auto ypos = static_cast<MouseMovedEvent&>(event).GetCursorY();
			if (isMouseHovering(xpos, ypos)) {
				paddingAnimation(1.5f);
			}
			else {
				paddingAnimation();
			}
			break;
		}
		case EventType::WINDOW_RESIZE:
		{
			updateConstraints(static_cast<WindowResizeEvent&>(event).getWidth(), static_cast<WindowResizeEvent&>(event).getHeight());
		}
	}
}

void ButtonComponent::update()
{
	this->UIshader->useShaderProgram();
	updateUniforms();
	draw();
}

bool ButtonComponent::isMouseHovering(float xpos, float ypos) {

	//TODO:Optimize this stuff
	float xglCoords = (xpos * 2.0f) / winwidth - 1.0f;
	float yglCoords = 1.0f-(ypos * 2.0f) / winHeight;
	std::cout << " ( " << xglCoords<< " , " << yglCoords<< " )\n";
	auto p  = props.x - props.width / 2.f;
	auto p_ = props.x + props.width / 2.f;
	auto q   = props.y - props.height / 2.f;
	auto q_ = props.y + props.height / 2.f;
	glm::vec4 ray_clip = glm::vec4(xglCoords,yglCoords,-1.f,1.f);
	glm::vec4 ray_eye = glm::inverse(this->x_projectionMatrix) * ray_clip;
	if ((ray_eye.x > p && ray_eye.x < p_) && (ray_eye.y > q && ray_eye.y < q_)) return true;
	return false;
}

void ButtonComponent::createBoxTemplate()
{
	//TODO: create a way to abstract and settle	vaos and vbo accordingly and easy to use
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(boxVertices),boxVertices,GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxIndices), boxIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindVertexArray(0);
	this->UIshader = new shader("src/App/Shaders/guiShader.vert", "src/App/Shaders/guiShader.frag");
}

void ButtonComponent::updateUniforms()
{
	UniformManager::getUniformManager()->setUniformMatrix4fv("u_uimodel", this->UIshader->getShaderProgramId(), glm::value_ptr(getModelMatrix()));
	UniformManager::getUniformManager()->setUniformMatrix4fv("u_uiproj", this->UIshader->getShaderProgramId(), glm::value_ptr(getProjectionMatrix()));
}

void ButtonComponent::updateConstraints(unsigned int width, unsigned int height)
{
	winwidth = width;
	winHeight = height;
	props.x = 0.f;
	props.y = 0.5f; 
	props.width = 0.2f;
	props.height = props.width;
	updateMatrices();
}

void ButtonComponent::updateMatrices()
{
	this->x_modelMatrix = glm::mat4(1.0f);
	this->x_modelMatrix = glm::translate(this->x_modelMatrix, glm::vec3(props.x, props.y, 0.f));
	this->x_modelMatrix = glm::scale(this->x_modelMatrix, glm::vec3(props.width, props.height, 1.f));

	this->x_projectionMatrix = glm::ortho(-1.f * winwidth / winHeight, 1.f * winwidth / winHeight, -1.f, 1.f);
}
void ButtonComponent::paddingAnimation(float fact)
{
	this->x_modelMatrix = glm::mat4(1.0f);
	this->x_modelMatrix = glm::translate(this->x_modelMatrix, glm::vec3(props.x, props.y, 0.f));
	this->x_modelMatrix = glm::scale(this->x_modelMatrix, glm::vec3(fact * props.width, fact * props.height, 1.f));
}
glm::mat4 ButtonComponent::getModelMatrix()
{
	return this->x_modelMatrix;
}

glm::mat4 ButtonComponent::getProjectionMatrix()
{
	return this->x_projectionMatrix;
}

