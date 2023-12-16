#pragma once
#include "../wolf/wolf.h"

class Sky
{

public:
    Sky(float cycle = 1);
    glm::vec3 getSkyColor() const;
    glm::vec3 getSunDirection() const;
    float getAmbienceLevel() const;
    void update(const float time);
    void reset();

private:
    float m_time = 0;
    float m_cycle = 1;
    glm::vec3 m_skyColor;
};