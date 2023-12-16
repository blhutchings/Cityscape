#pragma once
#include "../wolf/wolf.h"

struct LoadingBarVertex
{
    glm::vec2 position;
    glm::vec3 color;
};

class LoadingBar
{
public:
    LoadingBar(wolf::App * const app, glm::vec3 barColor, glm::vec3 barBackgroundColor, glm::vec3 clearColor);
    ~LoadingBar();
    void render(const float progress);
    void swapBuffers() const;

private:
    wolf::App * const m_app;
    wolf::Program *m_program;
    wolf::VertexBuffer *m_vbo;
    wolf::VertexDeclaration *m_declaration;
    const glm::vec3 m_barColor;
    const glm::vec3 m_barBackgroundColor;
    const glm::vec3 m_clearColor;
};