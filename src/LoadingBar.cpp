#include "LoadingBar.h"

LoadingBar::LoadingBar(wolf::App *const app, glm::vec3 barColor, glm::vec3 barBackgroundColor, glm::vec3 clearColor)
    : m_app(app), m_barColor(barColor), m_barBackgroundColor(barBackgroundColor), m_clearColor(clearColor)
{
    m_program = wolf::ProgramManager::CreateProgram("resources/shaders/progress_bar.vert", "resources/shaders/progress_bar.frag");
    m_vbo = wolf::BufferManager::CreateVertexBuffer(sizeof(LoadingBarVertex) * 12);

    m_declaration = new wolf::VertexDeclaration();
    m_declaration->Begin();
    m_declaration->AppendAttribute(wolf::AT_Position, 2, wolf::CT_Float);
    m_declaration->AppendAttribute(wolf::AT_Color, 3, wolf::CT_Float);
    m_declaration->SetVertexBuffer(m_vbo);
    m_declaration->End();
};
LoadingBar::~LoadingBar()
{
    wolf::ProgramManager::DestroyProgram(m_program);
    wolf::BufferManager::DestroyBuffer(m_vbo);
    delete m_declaration;
}

void LoadingBar::render(const float progress)
{
    // Needed to access app life cycle due to the city generation blocking the render loop
    this->m_app->scuffedLoadingBarStart();

    const float width = m_app->getScreenSize().x;
    const float height = m_app->getScreenSize().y;

    const LoadingBarVertex progress_bar[] = {
        {{0, height - 200}, m_barColor},
        {{0, height}, m_barColor},
        {{width * progress, height}, m_barColor},

        {{width * progress, height}, m_barColor},
        {{width * progress, height - 200}, m_barColor},
        {{0, height - 200}, m_barColor},

        {{0, height - 200}, m_barBackgroundColor},
        {{0, height}, m_barBackgroundColor},
        {{width, height}, m_barBackgroundColor},

        {{width, height}, m_barBackgroundColor},
        {{width, height - 200}, m_barBackgroundColor},
        {{0, height - 200}, m_barBackgroundColor}

    };

    this->m_vbo->Write(progress_bar);

    glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f);
    m_program->Bind();
    m_program->SetUniform("projection", proj);
    m_declaration->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 12);
    this->m_app->scuffedLoadingBarEnd();
}
