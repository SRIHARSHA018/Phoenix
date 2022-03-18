#pragma once
#include "ILight.h"
#include "UniformManager.h"

class SpotLight :
    public ILight
{
public:
    SpotLight(const glm::vec3& ambient,
        const glm::vec3& diffuse,
        const glm::vec3& specular,
        const glm::vec3& position,
        const glm::vec3& direction,
        unsigned int shaderProgramId);
    ~SpotLight();
    virtual void Update() override;
    virtual void onEvent(IEvent& event) override;
public:
    void setPostion(const glm::vec3& position) { this->x_position = position; }
    void setDirection(const glm::vec3& direction) { this->x_direction = direction; }
private:
    glm::vec3 x_position;
    glm::vec3 x_direction;
    unsigned int x_shaderProgramId;
private:
    void x_updateUniforms();
};

