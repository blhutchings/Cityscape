#include "CubeBuilding.h"

Chunk *CubeBuilding::create(const BlockId wall, const BlockId roof, const BuildingFront front,
                            const WindowConfig windows,
                            const unsigned int width, const unsigned int height, const unsigned int depth)
{
    Chunk *building = new Chunk(width, height, depth);
    // Set Roof
    for (unsigned int x = 0; x < width; ++x)
    {
        for (unsigned int z = 0; z < depth; ++z)
        {
            building->set(roof, x, height - 1, z);
        }
    }
    // Set Z Walls
    for (unsigned int x = 0; x < width; ++x)
    {
        for (unsigned int y = 0; y < height; ++y)
        {
            building->set(wall, x, y, 0);
            building->set(wall, x, y, depth - 1);
        }
    }
    // Set X Walls
    for (unsigned int z = 0; z < depth; ++z)
    {
        for (unsigned int y = 0; y < height; ++y)
        {
            building->set(wall, 0, y, z);
            building->set(wall, width - 1, y, z);
        }
    }

    // Set Z Windows
    for (unsigned int x = windows.horizontalPadding;
         x < width - windows.horizontalPadding;
         x += windows.horizontalSpacing)
    {
        for (unsigned int y = windows.verticalPadding;
             y < height - windows.verticalPadding;
             y += windows.veritcalSpacing)
        {
            for (unsigned int win_x = 0; win_x < windows.width; ++win_x)
            {
                for (unsigned int win_y = 0; win_y < windows.height; ++win_y)
                {
                    building->set(BlockId::GLASS, x + win_x, y + win_y, 0);
                    building->set(BlockId::GLASS, x + win_x, y + win_y, depth - 1);
                }
            }
        }
    }

    // Set X Windows
    for (unsigned int z = windows.horizontalPadding;
         z < depth - windows.horizontalPadding;
         z += windows.horizontalSpacing)
    {
        for (unsigned int y = windows.verticalPadding;
             y < height - windows.verticalPadding;
             y += windows.veritcalSpacing)
        {
            for (unsigned int win_x = 0; win_x < windows.width; ++win_x)
            {
                for (unsigned int win_y = 0; win_y < windows.height; ++win_y)
                {
                    building->set(BlockId::GLASS, 0, y + win_y, z + win_x);
                    building->set(BlockId::GLASS, width - 1, y + win_y, z + win_x);
                }
            }
        }
    }
    // Set Door
    switch (front)
    {
    case BuildingFront::NORTH:
        building->set(BlockId::DARK_OAK_DOOR_TOP, width / 2, 1, 0);
        building->set(BlockId::DARK_OAK_DOOR_BOTTOM, width / 2, 0, 0);
        break;
    case BuildingFront::SOUTH:
        building->set(BlockId::DARK_OAK_DOOR_TOP, width / 2, 1, depth - 1);
        building->set(BlockId::DARK_OAK_DOOR_BOTTOM, width / 2, 0, depth - 1);
        break;
    case BuildingFront::EAST:
        building->set(BlockId::DARK_OAK_DOOR_TOP, width - 1, 1, depth / 2);
        building->set(BlockId::DARK_OAK_DOOR_BOTTOM, width - 1, 0, depth / 2);
        break;
    case BuildingFront::WEST:
        building->set(BlockId::DARK_OAK_DOOR_TOP, 0, 1, depth / 2);
        building->set(BlockId::DARK_OAK_DOOR_BOTTOM, 0, 0, depth / 2);
        break;
    }

    return building;
}
