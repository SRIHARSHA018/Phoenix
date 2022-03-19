
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "global.h"
#include "SceneObject.h"
#include "InputControls.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvents.h"
#include "UniformManager.h" 



//TODO: refine camera class
class camera:public ISceneObject
{
public:
	glm::vec3 cameraPosition;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float cameraMovementSpeed;
	float zoom;
	float lastCursorXPos;
	float lastCursorYPos;
	float cameraYaw;
	float cameraPitch;
	float cameraRotationSensitivity;
	bool firstMouseMovement;
	unsigned int shaderProgramId;

	glm::mat4 modelMatrix;
	glm::mat4 projectionMatrix;

	const glm::vec3 worldUp = glm::vec3(0.f,1.f,0.f);


public:
	camera(glm::vec3 position = glm::vec3(0.f),
		glm::vec3 up = glm::vec3(0.f, 1.0f, 0.f),
		glm::vec3 front = glm::vec3(0.f, 0.f, -1.0f),
		float movementSpeed = 2.5f,float zoomVal=45.f,
		float sensitivity=0.2f,float yaw=-90.f,float pitch=0.f);
	~camera() {}
public:
	void moveForward();
	void moveBackward();
	void moveRight();
	void moveLeft();
	glm::mat4 getViewMatrix();
	glm::mat4 getModelMatrix() { return modelMatrix; }
	glm::mat4 getProjectionMatrix() { return projectionMatrix; }
	void processScrollWheel(float val);
	void processCursorMovement(float xPos, float yPos);
	virtual void update() override;
	virtual void onEvent(IEvent& event) override;

private:
	void x_updateCameraVectors();
	void x_processCursorMovement(float xoff, float yoff, bool constrain = true);
	void x_updateProjectionMatrix(float aspectRatio);
	void x_updateUniforms();
};

