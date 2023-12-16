#pragma once
#include "../wolf/wolf.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 64.0f;
const float SENSITIVITY = 0.075f;

const float ZOOM = 75.0f; // FOV
const float ZNEAR = 0.01f;
const float ZFAR = 2000.0f; // Need 2000 to see 20x20

class Camera
{

public:
    // camera Attributesww
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;
    // euler Angles
    float m_yaw;
    float m_pitch;
    // camera options
    float m_movementSpeed;
    float m_mouseSensitivity;
    float m_zoom;

    // projection
    const float m_znear;
    const float m_zfar;
    float m_aspect;

    // constructor with scalar values
    Camera(float aspect,
           glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW, float pitch = PITCH);

    const glm::mat4 getViewMatrix();
    const glm::mat4 getProjectionMatrix();
    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void processMouseScroll(float yoffset);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};