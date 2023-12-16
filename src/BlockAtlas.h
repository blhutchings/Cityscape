#pragma once
#include "../wolf/wolf.h"

class BlockAtlas
{
public:
    BlockAtlas(const std::string &texturePath, const std::string &normalPath, const std::string &specularPath,
               const glm::ivec2 size, const glm::ivec2 spriteSize);
    ~BlockAtlas();
    const void Bind(const wolf::Program *const program) const;
    const glm::vec2 getTextureCoords(glm::ivec2 offset) const;

    glm::vec2 spriteUnit;
    const glm::ivec2 size, spriteSize;

private:
    wolf::Texture *m_pTex = nullptr;
    wolf::Texture *m_pNormalMap = nullptr;
    wolf::Texture *m_pSpecularMap = nullptr;
};