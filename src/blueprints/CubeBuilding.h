#pragma once
#include "../Block.h"
#include "../Chunk.h"

enum class BuildingFront
{
    NORTH,
    SOUTH,
    EAST,
    WEST
};

struct WindowConfig
{
    unsigned int veritcalSpacing;
    unsigned int horizontalSpacing;
    unsigned int verticalPadding; // Vertical padding from the side of building
    unsigned int horizontalPadding;
    unsigned int width;  // Width of the window
    unsigned int height; // height of the window
};

class CubeBuilding
{
public:
    static Chunk *create(const BlockId wall, const BlockId roof, const BuildingFront front,
                         const WindowConfig windows,
                         const unsigned width, const unsigned height, const unsigned depth);
};
