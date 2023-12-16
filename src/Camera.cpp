
#include "Camera.h"

// constructor with vectors
Camera::Camera(float aspect,
               glm::vec3 position,
               glm::vec3 up,
               float yaw,
               float pitch) : m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
                              m_movementSpeed(SPEED),
                              m_mouseSensitivity(SENSITIVITY),
                              m_zoom(ZOOM),
                              m_znear(ZNEAR),
                              m_zfar(ZFAR)
{
    m_aspect = aspect;
    m_position = position;
    m_worldUp = up;
    m_yaw = yaw;
    m_pitch = pitch;
    updateCameraVectors();
}

const glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(this->m_position, this->m_position + this->m_front, this->m_up);
}

const glm::mat4 Camera::getProjectionMatrix()
{
    return glm::perspective(glm::radians(this->m_zoom), this->m_aspect, this->m_znear, this->m_zfar);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = m_movementSpeed * deltaTime;
    if (direction == CameraMovement::FORWARD)
    {
        float y = m_position.y;
        m_position += glm::cross({m_front.x, 1.0f, m_front.z}, m_right) * velocity; // Stay on same plane
        m_position.y = y;
    }
    if (direction == CameraMovement::BACKWARD)
    {
        float y = m_position.y;
        m_position -= glm::cross({m_front.x, 1.0f, m_front.z}, m_right) * velocity;
        m_position.y = y;
    }
    if (direction == CameraMovement::LEFT)
    {
        m_position -= m_right * velocity;
    }
    if (direction == CameraMovement::RIGHT)
    {
        m_position += m_right * velocity;
    }
    if (direction == CameraMovement::UP)
    {
        m_position.y += velocity;
    }
    if (direction == CameraMovement::DOWN)
    {
        m_position.y -= velocity;
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
    m_zoom -= (float)yoffset;
    if (m_zoom < 1.0f)
        m_zoom = 1.0f;
    if (m_zoom > 45.0f)
        m_zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    m_right = glm::normalize(glm::cross(m_front, m_worldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_up = glm::normalize(glm::cross(m_right, m_front));
}