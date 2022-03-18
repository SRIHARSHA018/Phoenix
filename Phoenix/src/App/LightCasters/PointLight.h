#pragma once
#include "ILight.h"
#include "UniformManager.h"

class PointLight :
    public ILight
{
public:
    PointLight(const glm::vec3& ambient,
        const glm::vec3& diffuse,
        const glm::vec3& specular,
        const glm::vec3& position,
        unsigned int shaderProgramId);
    ~PointLight();
public:
    virtual void Update() override;
    virtual void onEvent(IEvent& event) override;
public:
    void setPostion(const glm::vec3& position) { this->x_position = position; }
private:
    glm::vec3 x_position;
    unsigned int x_shaderProgramId;
private:
    void x_updateUniforms();
};

