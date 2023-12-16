#include "../wolf/wolf.h"
#include <time.h>
#include "./blueprints/CityChunk.h"
#include "City.h"
#include "Camera.h"
#include "CameraInputHandler.h"
#include "BlockManager.h"
#include "BlockAtlas.h"
#include "Sky.h"
#include "LoadingBar.h"

#define DAY_CYCLE 5.0f // (2PI * cycle) seconds per full sun cycle
#define CITY_WIDTH 20
#define CITY_DEPTH 20
#define BLOCK_WIDTH 6
#define BLOCK_DEPTH 3
#define BLOCK_DIMENSION_VARIENCE 5
#define CITY_HEIGHT_MAX 160
#define CITY_HEIGHT_MIN 10
#define CITY_HEIGHT_VARIENCE 10

class Cityscape : public wolf::App
{
public:
    Cityscape() : App("Cityscape")
    {
        // OpenGL configuration
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // Enable when transparency works
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glfwSetInputMode(this->m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetWindowSize(this->m_pWindow, 1920, 1080);

        program = wolf::ProgramManager::CreateProgram("resources/shaders/main.vert", "resources/shaders/main.frag");

        // Initalize Sky/Sun
        float cycle = DAY_CYCLE; // (2PI * cycle) seconds per full sun cycle
        sky = new Sky(cycle);

        // Setup block atlas
        atlas = new BlockAtlas("resources/x64/blocks.png",
                               "resources/x64/normals.png",
                               "resources/x64/specular.png",
                               {256, 256}, {64, 64});
        BlockManager::init(atlas);

        float aspect = this->getScreenSize().x / this->getScreenSize().y;
        camera = new Camera(aspect, {0.0f, 0.0f, 0.0f});
        cameraHandler = new CameraInputHandler(this, camera);

        progressBar = new LoadingBar(this, glm::vec3(0, 255, 0), glm::vec3(128, 128, 128), glm::vec3(0, 0, 0));

        generateCity();
    }

    ~Cityscape()
    {
        wolf::ProgramManager::DestroyProgram(program);
        delete atlas;
        delete sky;
        delete camera;
        delete cameraHandler;
        delete city;
        delete progressBar;
    }

    void update(float dt) override
    {
        if (isKeyDown(GLFW_KEY_R))
        {
            // Note -- next dt will be how long the city took to generate (fix by setting sky to minus duration)
            sky->reset();
            delete city;
            generateCity();
        }
        else
        {
            sky->update(dt);
            cameraHandler->update(dt);
        }
    }

    void render() override
    {
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glm::vec3 skyColor = sky->getSkyColor();
        glClearColor(skyColor.r, skyColor.g, skyColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use Shader
        program->Bind();

        // Bind Textures
        atlas->Bind(program);

        // Bind Uniforms
        program->SetUniform("projection", camera->getProjectionMatrix());
        program->SetUniform("view", camera->getViewMatrix());
        program->SetUniform("world", world);
        program->SetUniform("worldIT", worldIT);

        // Textures
        program->SetUniform("u_tex", 0);
        program->SetUniform("u_normalMap", 1);
        program->SetUniform("u_specularMap", 2);

        // Scene
        program->SetUniform("u_lightDir", sky->getSunDirection());
        program->SetUniform("u_lightColor", glm::vec3(0.8f, 0.8f, 0.8f));
        program->SetUniform("u_ambienceLevel", sky->getAmbienceLevel());
        program->SetUniform("u_viewPos", camera->m_position);

        // Render
        city->render(program);
    }

    void generateCity()
    {
        city = new City(CITY_WIDTH, CITY_DEPTH,
                        BLOCK_WIDTH, BLOCK_DEPTH,
                        BLOCK_DIMENSION_VARIENCE,
                        CITY_HEIGHT_MAX, CITY_HEIGHT_MIN, CITY_HEIGHT_VARIENCE,
                        progressBar);

        // Set Camera in center of city
        unsigned int camera_x = (BLOCK_WIDTH * CITY_WIDTH + (CITY_WIDTH + 1)) / 2 * BLOCK_SIZE + (BLOCK_SIZE / 2);
        unsigned int camera_z = (BLOCK_DEPTH * CITY_DEPTH + (CITY_DEPTH + 1)) / 2 * BLOCK_SIZE + (BLOCK_SIZE / 2);

        // Offset towards closest intersection (-x,-z) corner if odd number of city blocks since the center will be a city block
        if (CITY_WIDTH % 2 == 1)
        {
            camera_x -= (BLOCK_WIDTH / 2 + 1) * BLOCK_SIZE;
        }
        if (CITY_DEPTH % 2 == 1)
        {
            camera_z -= (BLOCK_DEPTH / 2 + 1) * BLOCK_SIZE;
        }
        camera->m_position = {camera_x, 5.0f, camera_z};
    }

private:
    const glm::mat4 world = glm::mat4(1.0f);
    const glm::mat4 worldIT = glm::transpose(glm::inverse(glm::mat4(1.0f)));

    wolf::Program *program = nullptr;
    BlockAtlas *atlas = nullptr;
    Sky *sky = nullptr;
    Camera *camera = nullptr;
    CameraInputHandler *cameraHandler = nullptr;

    City *city = nullptr;
    LoadingBar *progressBar = nullptr;
};

int main(int, char **)
{
    srand((unsigned)time(NULL));
    Cityscape cityscape;
    cityscape.run();
}
