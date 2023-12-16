#pragma once
#include "../wolf/wolf.h"

enum BlockId
{
    AIR,

    GRASS,
    GRAVEL,
    COBBLESTONE,
    STONE,

    BRICK,
    STONE_BRICK,
    END_BRICK,
    RED_NETHERBRICK,
    
    GLASS,
    GRAY_CONCRETE,
    BLACK_CONCRETE,
    YELLOW_CONCRETE,

    GOLD_BLOCK,
    IRON_BLOCK,
    DARK_OAK_DOOR_TOP,
    DARK_OAK_DOOR_BOTTOM
};

struct Block
{
    BlockId id;
    bool transparent;
    glm::ivec2 textureOffset;
};