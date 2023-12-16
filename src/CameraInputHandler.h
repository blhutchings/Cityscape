#pragma once
#include "Camera.h"
#include "../wolf/wolf.h"

class CameraInputHandler
{

public:
    CameraInputHandler(const wolf::App *const app, Camera *const camera);
    void update(const float deltaTime);

private:
    const wolf::App *const app;
    Camera *const camera;

    float lastX;
    float lastY;
    bool firstMouse = true;

    void process_keyboard(const float deltaTime);
    void process_mouse();
    void process_scroll();
};