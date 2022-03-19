#include "camera.h"
#include "global.h"
#include<iostream>

camera::camera(glm::vec3 position, glm::vec3 up, glm::vec3 front, float movementSpeed, float zoomVal,float sensitivity, float yaw, float pitch)
	:cameraPosition(position),cameraUp(up),cameraFront(front),
	cameraMovementSpeed(movementSpeed),zoom(zoomVal),cameraRotationSensitivity(sensitivity),
	cameraYaw(yaw),cameraPitch(pitch)
{
	firstMouseMovement = true;
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 0.f, -10.f));
	x_updateCameraVectors();
	projectionMatrix = glm::mat4(1.0f);
}

void camera::moveForward()
{

	cameraPosition += cameraMovementSpeed *Time::getDeltaTime() * cameraFront;
}

void camera::moveBackward()
{
	cameraPosition -= cameraMovementSpeed * Time::getDeltaTime() * cameraFront;
}

void camera::moveRight()
{
	cameraPosition += cameraMovementSpeed * Time::getDeltaTime() * glm::normalize(glm::cross(cameraFront, worldUp));
}
void camera::moveLeft()
{
	cameraPosition -= cameraMovementSpeed * Time::getDeltaTime() * glm::normalize(glm::cross(cameraFront, worldUp));
}

void camera::processScrollWheel(float val)
{
	zoom -= static_cast<float>(val);
	if (zoom < 1.0f) zoom = 1.f;
	if (zoom > 45.f) zoom = 45.f;
}

void camera::processCursorMovement(float xPos, float yPos)
{
	float xPosIn = static_cast<float>(xPos);
	float yPosIn = static_cast<float>(yPos);
	if (firstMouseMovement) {
		lastCursorXPos = xPosIn;
		lastCursorYPos = yPosIn;
		firstMouseMovement = false;
	}
	float xoff = xPosIn - lastCursorXPos;
	float yoff = lastCursorYPos - yPosIn;

	lastCursorXPos = xPosIn;
	lastCursorYPos = yPosIn;
	this->x_processCursorMovement(xoff, yoff);
}

void camera::update()
{
	if (InputControls::isKeyPressed(GLFW_KEY_W)) moveForward();
	if (InputControls::isKeyPressed(GLFW_KEY_A)) moveLeft();
	if (InputControls::isKeyPressed(GLFW_KEY_D)) moveRight();
	if (InputControls::isKeyPressed(GLFW_KEY_S)) moveBackward();
	if (InputControls::isKeyReleased(GLFW_KEY_LEFT_ALT)) {
			this->firstMouseMovement = true;
	}
	this->x_updateUniforms();
}
void camera::x_updateUniforms() 
{
	UniformManager::getUniformManager()->setUniformVec3("u_viewPosition",shaderProgramId , glm::value_ptr(this->cameraPosition));
	UniformManager::getUniformManager()->setUniformMatrix4fv("model", shaderProgramId, glm::value_ptr(this->modelMatrix));
	UniformManager::getUniformManager()->setUniformMatrix4fv("view", shaderProgramId, glm::value_ptr(this->getViewMatrix()));
	UniformManager::getUniformManager()->setUniformMatrix4fv("proj", shaderProgramId, glm::value_ptr(this->projectionMatrix));
}

void camera::x_processCursorMovement(float xoff, float yoff, bool constrain)
{
	xoff *= cameraRotationSensitivity;
	yoff *= cameraRotationSensitivity;
	
	cameraYaw += xoff;
	cameraPitch += yoff;

	if (constrain) {
		if (cameraPitch > 89.f) cameraPitch = 89.f;
		if (cameraPitch < -89.f) cameraPitch = -89.f;
	}
	x_updateCameraVectors();
}
void camera::onEvent(IEvent& event)
{
	switch (event.getEventType()) {
		case EventType::MOUSE_MOVED: 
		{
			if (InputControls::isKeyPressed(GLFW_KEY_LEFT_ALT)) {
				processCursorMovement(InputControls::getCursorPos().x, InputControls::getCursorPos().y);
			}
			break;
		}
		case EventType::MOUSE_SCROLLED:
		{
			processScrollWheel(static_cast<MouseScrolledEvent&>(event).getYoffset());
			break;
		}
		case EventType::WINDOW_RESIZE:
		{
			auto windowResizeEvent= static_cast<WindowResizeEvent&>(event);
			auto aspectRatio = (float)windowResizeEvent.getWidth() / (float)windowResizeEvent.getHeight();

			x_updateProjectionMatrix(aspectRatio);
			break;
		}
		default:break;
	}
}
void camera::x_updateCameraVectors() 
{
	glm::vec3 front;
	front.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
	front.y = sin(glm::radians(cameraPitch));
	front.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
	cameraFront = glm::normalize(front);
}
void camera::x_updateProjectionMatrix(float aspectRatio)
{
	projectionMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::perspective(glm::radians(this->zoom), aspectRatio, 0.1f, 100.0f);
}
glm::mat4 camera::getViewMatrix()
{
	return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}



