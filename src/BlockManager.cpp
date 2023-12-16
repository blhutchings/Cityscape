#include "BlockManager.h"

bool BlockManager::initalized = false;
BlockAtlas *BlockManager::atlas = nullptr;
Block BlockManager::blocks[MAX_BLOCK_COUNT];

const BlockAtlas *const BlockManager::getAtlas()
{
    return BlockManager::atlas;
}

glm::vec2 BlockManager::getUVOffset(BlockId id)
{
    return BlockManager::atlas->getTextureCoords(BlockManager::blocks[id].textureOffset);
}

bool BlockManager::isTransparent(BlockId id)
{
    return BlockManager::blocks[id].transparent;
}

void BlockManager::init(BlockAtlas *atlas)
{
    if (BlockManager::initalized)
        return;
    BlockManager::atlas = atlas;
    BlockManager::initalized = true;

    BlockManager::initBlock(BlockId::AIR, true);

    BlockManager::initBlock(BlockId::GRASS, false, glm::vec2(0, 0));
    BlockManager::initBlock(BlockId::GRAVEL, false, glm::vec2(1, 0));
    BlockManager::initBlock(BlockId::COBBLESTONE, false, glm::vec2(2, 0));
    BlockManager::initBlock(BlockId::STONE, false, glm::vec2(3, 0));

    BlockManager::initBlock(BlockId::BRICK, false, glm::vec2(0, 1));
    BlockManager::initBlock(BlockId::STONE_BRICK, false, glm::vec2(1, 1));
    BlockManager::initBlock(BlockId::END_BRICK, false, glm::vec2(2, 1));
    BlockManager::initBlock(BlockId::RED_NETHERBRICK, false, glm::vec2(3, 1));

    BlockManager::initBlock(BlockId::GLASS, false, glm::vec2(0, 2)); // TODO enable true when face sorting fixed
    BlockManager::initBlock(BlockId::GRAY_CONCRETE, false, glm::vec2(1, 2));
    BlockManager::initBlock(BlockId::BLACK_CONCRETE, false, glm::vec2(2, 2));
    BlockManager::initBlock(BlockId::YELLOW_CONCRETE, false, glm::vec2(3, 2));

    BlockManager::initBlock(BlockId::GOLD_BLOCK, false, glm::vec2(0, 3));
    BlockManager::initBlock(BlockId::IRON_BLOCK, false, glm::vec2(1, 3));
    BlockManager::initBlock(BlockId::DARK_OAK_DOOR_TOP, false, glm::vec2(2, 3));
    BlockManager::initBlock(BlockId::DARK_OAK_DOOR_BOTTOM, false, glm::vec2(3, 3));
}

void BlockManager::initBlock(const BlockId id, const bool transparent, glm::vec2 textureOffset)
{
    if (id > MAX_BLOCK_COUNT)
    {
        throw std::exception("Max Block Count Exceeded");
    }
    BlockManager::blocks[id] = {id, transparent, textureOffset};
}