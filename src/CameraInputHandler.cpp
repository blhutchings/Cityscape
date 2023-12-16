#include "CameraInputHandler.h"

CameraInputHandler::CameraInputHandler(const wolf::App *const app, Camera *const camera) : app(app), camera(camera) {
    lastX = app->getScreenSize().x / 2.0f;
    lastY = app->getScreenSize().y / 2.0f;
    firstMouse = true;
}

void CameraInputHandler::update(const float deltaTime)
{
    process_keyboard(deltaTime);
    process_mouse();
    process_scroll();
}

void CameraInputHandler::process_keyboard(const float deltaTime)
{
    if (app->isKeyDown(GLFW_KEY_W))
        camera->processKeyboard(CameraMovement::FORWARD, deltaTime);
    if (app->isKeyDown(GLFW_KEY_S))
        camera->processKeyboard(CameraMovement::BACKWARD, deltaTime);
    if (app->isKeyDown(GLFW_KEY_A))
        camera->processKeyboard(CameraMovement::LEFT, deltaTime);
    if (app->isKeyDown(GLFW_KEY_D))
        camera->processKeyboard(CameraMovement::RIGHT, deltaTime);
    if (app->isKeyDown(GLFW_KEY_SPACE))
        camera->processKeyboard(CameraMovement::UP, deltaTime);
    if (app->isKeyDown(GLFW_KEY_LEFT_CONTROL))
        camera->processKeyboard(CameraMovement::DOWN, deltaTime);
}

void CameraInputHandler::process_mouse()
{
    glm::vec2 pos = app->getMousePos();
    float xpos = pos.x;
    float ypos = pos.y;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->processMouseMovement(xoffset, yoffset);
}

void CameraInputHandler::process_scroll()
{
    glm::vec2 mousePos = app->getMouseScroll();
    //float xoffset = mousePos.x;
    float yoffset = mousePos.y;
    camera->processMouseScroll(static_cast<float>(yoffset));
}
