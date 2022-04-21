#include "Camera.h"
#include "Global.h"
#include<iostream>

Camera::Camera(unsigned int shader_program_id, glm::vec3 position, glm::vec3 up, glm::vec3 front, float movement_speed, float zoom_val, float sensitivity, float yaw, float pitch)
	:camera_position(position), camera_up(up), camera_front(front),
	camera_movement_speed(movement_speed), zoom(zoom_val), camera_rotation_sensitivity(sensitivity),
	camera_yaw(yaw), camera_pitch(pitch), x_shader_program_id(shader_program_id)
{
	first_mouse_movement = true;
	model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(model_matrix, glm::vec3(0.f, 0.f, -10.f));
	x_updateCameraVectors();
	projection_matrix = glm::mat4(1.0f);
}

void Camera::moveForward()
{

	camera_position += camera_movement_speed * Time::getDeltaTime() * camera_front;
}

void Camera::moveBackward()
{
	camera_position -= camera_movement_speed * Time::getDeltaTime() * camera_front;
}

void Camera::moveRight()
{
	camera_position += camera_movement_speed * Time::getDeltaTime() * glm::normalize(glm::cross(camera_front, world_up));
}
void Camera::moveLeft()
{
	camera_position -= camera_movement_speed * Time::getDeltaTime() * glm::normalize(glm::cross(camera_front, world_up));
}

void Camera::processScrollWheel(float val)
{
	zoom -= static_cast<float>(val);
	if (zoom < 1.0f) zoom = 1.f;
	if (zoom > 45.f) zoom = 45.f;
}

void Camera::processCursorMovement(float xPos, float yPos)
{
	float xPosIn = static_cast<float>(xPos);
	float yPosIn = static_cast<float>(yPos);
	if (first_mouse_movement) {
		last_cursor_x_pos = xPosIn;
		last_cursor_y_pos = yPosIn;
		first_mouse_movement = false;
	}
	float xoff = xPosIn - last_cursor_x_pos;
	float yoff = last_cursor_y_pos - yPosIn;

	last_cursor_x_pos = xPosIn;
	last_cursor_y_pos = yPosIn;
	this->x_processCursorMovement(xoff, yoff);
}

void Camera::update()
{
	if (InputControls::isKeyPressed(GLFW_KEY_W)) moveForward();
	if (InputControls::isKeyPressed(GLFW_KEY_A)) moveLeft();
	if (InputControls::isKeyPressed(GLFW_KEY_D)) moveRight();
	if (InputControls::isKeyPressed(GLFW_KEY_S)) moveBackward();
	if (InputControls::isKeyReleased(GLFW_KEY_LEFT_ALT)) {
		this->first_mouse_movement = true;
	}
	this->x_updateUniforms();
}
void Camera::x_updateUniforms()
{
	UniformManager::get()->setUniformVec3("u_viewPosition", this->x_shader_program_id, glm::value_ptr(this->camera_position));
	UniformManager::get()->setUniformMatrix4fv("model", this->x_shader_program_id, glm::value_ptr(this->model_matrix));
	UniformManager::get()->setUniformMatrix4fv("view", this->x_shader_program_id, glm::value_ptr(this->getViewMatrix()));
	UniformManager::get()->setUniformMatrix4fv("proj", this->x_shader_program_id, glm::value_ptr(this->projection_matrix));
}

void Camera::x_processCursorMovement(float xoff, float yoff, bool constrain)
{
	xoff *= camera_rotation_sensitivity;
	yoff *= camera_rotation_sensitivity;

	camera_yaw += xoff;
	camera_pitch += yoff;

	if (constrain) {
		if (camera_pitch > 89.f) camera_pitch = 89.f;
		if (camera_pitch < -89.f) camera_pitch = -89.f;
	}
	x_updateCameraVectors();
}
void Camera::onEvent(IEvent& event)
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
		auto windowResizeEvent = static_cast<WindowResizeEvent&>(event);
		auto aspect_ratio = (float)windowResizeEvent.getWidth() / (float)windowResizeEvent.getHeight();

		x_updateProjectionMatrix(aspect_ratio);
		break;
	}
	default:break;
	}
}
void Camera::x_updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
	front.y = sin(glm::radians(camera_pitch));
	front.z = sin(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
	camera_front = glm::normalize(front);
}
void Camera::x_updateProjectionMatrix(float aspect_ratio)
{
	projection_matrix = glm::mat4(1.0f);
	projection_matrix = glm::perspective(glm::radians(this->zoom), aspect_ratio, 0.1f, 100.0f);
}
glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(camera_position, camera_position + camera_front, camera_up);
}



