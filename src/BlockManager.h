#pragma once
#include "../wolf/wolf.h"
#include "Block.h"
#include "BlockAtlas.h"

#define MAX_BLOCK_COUNT INT8_MAX

class BlockManager
{

public:
    static bool isTransparent(BlockId id);
    static glm::vec2 getUVOffset(BlockId id);
    static const BlockAtlas* const getAtlas();
    static void init(BlockAtlas* atlas);

private:
    BlockManager();
    static bool initalized;
    static void initBlock(const BlockId id, const bool transparent, const glm::vec2 textureOffset = glm::vec2(-1, -1));
    static Block blocks[MAX_BLOCK_COUNT];
    static BlockAtlas* atlas;
};
