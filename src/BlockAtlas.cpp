#include "BlockAtlas.h"

BlockAtlas::BlockAtlas(const std::string &texturePath, const std::string &normalPath, const std::string &specularPath,
                       const glm::ivec2 size, const glm::ivec2 spriteSize) : size(size), spriteSize(spriteSize)
{
    spriteUnit = glm::vec2((float)spriteSize.x / (float)size.x, (float)spriteSize.y / (float)size.y);

    m_pTex = wolf::TextureManager::CreateTexture(texturePath);
    m_pTex->SetFilterMode(wolf::Texture::FM_Nearest, wolf::Texture::FM_Nearest);
    m_pTex->SetWrapMode(wolf::Texture::WM_Repeat, wolf::Texture::WM_Repeat);

    // Load Block Normal Map
    m_pNormalMap = wolf::TextureManager::CreateTexture(normalPath);
    m_pNormalMap->SetFilterMode(wolf::Texture::FM_Nearest, wolf::Texture::FM_Nearest);
    m_pNormalMap->SetWrapMode(wolf::Texture::WM_Repeat, wolf::Texture::WM_Repeat);

    // Load Block Specular Map
    m_pSpecularMap = wolf::TextureManager::CreateTexture(specularPath);
    m_pSpecularMap->SetFilterMode(wolf::Texture::FM_Nearest, wolf::Texture::FM_Nearest);
    m_pSpecularMap->SetWrapMode(wolf::Texture::WM_Repeat, wolf::Texture::WM_Repeat);
}

BlockAtlas::~BlockAtlas()
{
    wolf::TextureManager::DestroyTexture(m_pTex);
    wolf::TextureManager::DestroyTexture(m_pNormalMap);
    wolf::TextureManager::DestroyTexture(m_pSpecularMap);
}

const glm::vec2 BlockAtlas::getTextureCoords(glm::ivec2 offset) const
{
    float uv_x = (float)(offset.x * spriteSize.x) / (float)size.x;
    float uv_y = (float)(offset.y * spriteSize.y) / (float)size.y;
    return {uv_x, uv_y};
};

const void BlockAtlas::Bind(const wolf::Program *const program) const
{
    m_pTex->Bind(0);
    m_pNormalMap->Bind(1);
    m_pSpecularMap->Bind(2);
}
