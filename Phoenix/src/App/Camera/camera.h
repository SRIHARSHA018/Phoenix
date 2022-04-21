
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "global.h"
#include "Scene/SceneObject.h"
#include "InputControls.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvents.h"
#include "Shaders/UniformManager.h"



//TODO: refine camera class
class Camera :public ISceneObject
{
public:
	glm::vec3 camera_position;
	glm::vec3 camera_front;
	glm::vec3 camera_up;

	float camera_movement_speed;
	float zoom;
	float last_cursor_x_pos;
	float last_cursor_y_pos;
	float camera_yaw;
	float camera_pitch;
	float camera_rotation_sensitivity;
	bool first_mouse_movement;


	glm::mat4 model_matrix;
	glm::mat4 projection_matrix;

	const glm::vec3 world_up = glm::vec3(0.f, 1.f, 0.f);


public:
	Camera(unsigned int shader_program_id, glm::vec3 position = glm::vec3(0.f),
		glm::vec3 up = glm::vec3(0.f, 1.0f, 0.f),
		glm::vec3 front = glm::vec3(0.f, 0.f, -1.0f),
		float movement_speed = 2.5f, float zoom_val = 45.f,
		float sensitivity = 0.2f, float yaw = -90.f, float pitch = 0.f);
	~Camera() {}

public:
	void moveForward();
	void moveBackward();
	void moveRight();
	void moveLeft();
	glm::mat4 getViewMatrix();
	glm::mat4 getModelMatrix() { return model_matrix; }
	glm::mat4 getProjectionMatrix() { return projection_matrix; }
	void processScrollWheel(float val);
	void processCursorMovement(float xPos, float yPos);
	virtual void update() override;
	virtual void onEvent(IEvent& event) override;

private:
	void x_updateCameraVectors();
	void x_processCursorMovement(float xoff, float yoff, bool constrain = true);
	void x_updateProjectionMatrix(float aspect_ratio);
	void x_updateUniforms();
private:
	unsigned int x_shader_program_id;
};

