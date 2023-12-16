#include "CityBlock.h"
#define MATERIAL_COUNT 9
#define MIN_BUILDING_SIZE 5
const BlockId materials[MATERIAL_COUNT] = {BlockId::COBBLESTONE,
                                           BlockId::END_BRICK,
                                           BlockId::BRICK,
                                           BlockId::RED_NETHERBRICK,
                                           BlockId::STONE_BRICK,
                                           BlockId::BLACK_CONCRETE,
                                           BlockId::GRAY_CONCRETE,
                                           BlockId::IRON_BLOCK,
                                           BlockId::GOLD_BLOCK};

unsigned int CityBlock::building_count = 0;

const BlockMesh *const CityBlock::create(unsigned int width, unsigned int depth, unsigned int dimension_varience, unsigned int baseHeight, unsigned int height_varience, glm::vec3 position)
{
    // Initial offset for East Facing buildings
    unsigned int east_start_depth = 0; // Set by North
    unsigned int east_end_depth = 0;   // Set by South

    // Initial offsets for West Facing buildings
    unsigned int west_start_depth = 0; // Set by North
    unsigned int west_end_depth = 0;   // Set by South

    // Set chunk max height
    unsigned int height_ratio = baseHeight < 20 ? 2 : 3;
    height_varience = baseHeight > 100 ? height_varience * 2 : height_varience;
    unsigned int max_height = baseHeight + height_varience;

    // Create full city block
    Chunk *chunk = new Chunk(width, max_height, depth);
    // Set base
    for (unsigned int x = 0; x < width; ++x)
    {
        for (unsigned int z = 0; z < depth; ++z)
        {
            if ((x < BLOCK_SIZE || x > width - BLOCK_SIZE) || (z < BLOCK_SIZE || z > depth - BLOCK_SIZE))
            {
                chunk->set(BlockId::GRAY_CONCRETE, x, 0, z);
            }
            else
            {
                chunk->set(BlockId::GRASS, x, 0, z);
            }
        }
    }

    // North Side
    for (unsigned int east = 0; east < width;)
    {
        // Generate dimensions
        unsigned int building_height = baseHeight + (rand() % height_varience);
        unsigned int building_width = building_height / height_ratio + (rand() % dimension_varience);
        unsigned int building_depth = building_height / height_ratio + (rand() % dimension_varience);
        unsigned int inset = rand() % 2 ? 0 : rand() % 3;

        if (building_width + east > width) // Keep x inbounds
            building_width = width - east;

        if (building_depth > depth) // Keep z inbounds
            building_depth = depth;

        if (building_depth + inset > depth) // Check if current depth allows for a inset
            inset = 0;

        if (building_width < MIN_BUILDING_SIZE)
        {
            east_start_depth = building_depth;
            break; // Skips the end of a row if the building size is too small to make another
        }

        if (west_start_depth == 0)
            west_start_depth = building_depth;

        CityBlock::generateBuilding(chunk, east, inset, building_width, building_height, building_depth, BuildingFront::NORTH);
        east += building_width;
        if (east < width)
            east_start_depth = building_depth;
    }

    // South Side
    for (unsigned int east = 0; east < width;)
    {
        // Generate dimensions
        unsigned int building_height = baseHeight + (rand() % height_varience);
        unsigned int building_width = building_height / height_ratio + (rand() % dimension_varience);
        unsigned int building_depth = building_height / height_ratio + (rand() % dimension_varience);
        unsigned int inset = rand() % 2 ? 0 : rand() % 3;

        if (building_width + east > width) // Keep x inbounds
            building_width = width - east;

        if (building_depth > depth) // Keep z inbounds
            building_depth = depth;

        if (building_depth + inset > depth) // Check if current depth allows for a inset
            inset = 0;

        if (building_width < MIN_BUILDING_SIZE)
        {
            east_end_depth = building_depth;
            break;
        } // Skips the end of a row if the building size is too small to make another

        if (west_end_depth == 0)
            west_end_depth = building_depth;

        CityBlock::generateBuilding(chunk, east, depth - building_depth - 1 - inset, building_width, building_height, building_depth, BuildingFront::SOUTH);
        east += building_width;
        if (east < width)
            east_end_depth = building_depth;
    }

    // West Size
    for (unsigned int north = west_start_depth; north < depth - west_end_depth;)
    {
        // Generate dimensions
        unsigned int building_height = baseHeight + (rand() % height_varience);
        unsigned int building_width = building_height / height_ratio + (rand() % dimension_varience);
        unsigned int building_depth = building_height / height_ratio + (rand() % dimension_varience);
        unsigned int inset = rand() % 2 ? 0 : rand() % 3;
        if (building_width > width) // Keep x inbounds
            building_width = width;

        if (building_depth + north > depth - west_end_depth) // Keep z inbounds
            building_depth = depth - north - west_end_depth;

        if (building_width + inset > width) // Check if current depth allows for a inset
            inset = 0;

        if (building_depth < MIN_BUILDING_SIZE) // Skips the end of a row if the building size is too small to make another
            break;

        CityBlock::generateBuilding(chunk, inset, north, building_width, building_height, building_depth, BuildingFront::WEST);
        north += building_depth;
    }

    // East Size
    for (unsigned int north = east_start_depth; north < depth - east_end_depth;)
    {
        // Generate dimensions
        unsigned int building_height = baseHeight + (rand() % height_varience);
        unsigned int building_width = building_height / height_ratio + (rand() % dimension_varience);
        unsigned int building_depth = building_height / height_ratio + (rand() % dimension_varience);
        unsigned int inset = rand() % 2 ? 0 : rand() % 3;
        if (building_width > width) // Keep x inbounds
            building_width = width;

        if (building_depth + north > depth - east_end_depth) // Keep z inbounds
            building_depth = depth - north - east_end_depth;

        if (building_width + inset > width) // Check if current depth allows for a inset
            inset = 0;

        if (building_depth < MIN_BUILDING_SIZE) // Skips the end of a row if the building size is too small to make another
            break;

        CityBlock::generateBuilding(chunk, width - building_width - 1 - inset, north, building_width, building_height, building_depth, BuildingFront::EAST);
        north += building_depth;
    }

    BlockMesh *mesh = new BlockMesh(chunk, position);
    delete chunk; // Don't need chunk as it won't change
    return mesh;
}

void CityBlock::generateBuilding(Chunk *const block,
                                 const unsigned int start_x, const unsigned int start_z,
                                 const unsigned int building_width, const unsigned int building_height, const unsigned int building_depth,
                                 const BuildingFront facing)
{
    // Generate Building
    Chunk *building = CubeBuilding::create(materials[(BlockId)(rand() % MATERIAL_COUNT)],
                                           materials[(BlockId)(rand() % MATERIAL_COUNT)],
                                           facing,
                                           {4, 4, 4, 4, 2, 2},
                                           building_width, building_height, building_depth);

    // Copy into main block chunk
    for (unsigned int x = start_x; x < start_x + building_width; ++x)
    {
        for (unsigned int y = 0; y < building_height; ++y)
        {
            for (unsigned int z = start_z; z < start_z + building_depth; ++z)
            {
                // printf("(%d %d %d) -> (%d %d %d)\n", x - start_x, y, z - start_z, x, y + 1, z);
                block->set(building->get(x - start_x, y, z - start_z), x, y + 1, z);
            }
        }
    }
    delete building;

    ++CityBlock::building_count;
}