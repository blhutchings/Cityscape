#include "Sky.h"

Sky::Sky(float cycle)
{
    this->m_skyColor = glm::normalize(glm::vec3(121.0f, 166.0f, 255.0f));
    this->m_cycle = cycle; // Default Cycle is 2PI * 1 seconds
}


glm::vec3 Sky::getSkyColor() const
{
    return sin(m_time * (1 / m_cycle)) * m_skyColor;
}

glm::vec3 Sky::getSunDirection() const
{
    float x = -cos(m_time * (1 / m_cycle));
    float y = -sin(m_time * (1 / m_cycle));
    if (y > 0.0f) {
     return glm::vec3(0, 0, 0);
    }
    return glm::vec3(0, y, 0);
}

float Sky::getAmbienceLevel() const
{
    float ambience = sin(m_time * (1 / m_cycle));
    if (ambience > 0.9f) {
        return 0.9f;
    }
    if (ambience < 0.10f) {
       return 0.1f;
    }
    return ambience;
}

void Sky::update(float dt)
{
    m_time += dt;
}

void Sky::reset() {
    m_time = 0.0f;
}