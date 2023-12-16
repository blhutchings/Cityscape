#include "City.h"

City::City(unsigned int city_width, unsigned int city_depth,
           unsigned int block_width, unsigned int block_depth,
           unsigned int block_dimension_varience,
           unsigned int height_max, unsigned int height_min, unsigned int height_varience,
           LoadingBar *const progressBar)
{
    if (city_width == 0)
        throw std::exception("City Width must be >= 1");
    if (city_depth == 0)
        throw std::exception("City Depth must be >= 1");
    if (block_width == 0)
        throw std::exception("Block Width must be >= 1");
    if (block_depth == 0)
        throw std::exception("Block Depth must be >= 1");
    if (block_dimension_varience == 0)
        throw std::exception("Block Depth must be >= 1");
    if (height_varience < 0)
        throw std::exception("Height Varience must be >= 0");
    if (height_varience > height_min)
        throw std::exception("Height Varience must be <= Height Max");
    if (height_max < height_min)
        throw std::exception("Height Max must be >= Height Min");

    unsigned int end_x = block_width * city_width + (city_width + 1);
    unsigned int end_z = block_depth * city_depth + (city_depth + 1);

    unsigned int offset_depth = block_depth + 1;
    unsigned int offset_width = block_width + 1;

    unsigned int blocks_created = 0;
    unsigned int total_blocks = city_depth * city_width;
    for (unsigned int x = 0; x < end_x; ++x)
    {
        for (unsigned int z = 0; z < end_z; ++z)
        {
            // Intersection
            if (z % offset_depth == 0 && x % offset_width == 0)
            {
                meshes.push_back(Intersection::create({x * BLOCK_SIZE, 0, z * BLOCK_SIZE}));
            }
            else if (x % offset_width == 0)
            {
                meshes.push_back(Street::create(StreetDirection::NORTH_SOUTH, {x * BLOCK_SIZE, 0, z * BLOCK_SIZE}));
            }
            else if (z % offset_depth == 0)
            {
                meshes.push_back(Street::create(StreetDirection::EAST_WEST, {x * BLOCK_SIZE, 0, z * BLOCK_SIZE}));
            }
            else if (z % offset_depth == 1 && x % offset_width == 1)
            {
                // Translate block cordinates to function cordinates around (0,0)
                float x_offset = (x / offset_width) - (city_width - 1) * 0.5f;
                float z_offset = (z / offset_depth) - (city_depth - 1) * 0.5f;

                float a = powf(x_offset / (float)city_width, 2); // Controls x = y min + 1 intersection
                float b = powf(z_offset / (float)city_depth, 2); // Controls z = y min + 1 intersection
                float c = (1.0f / (height_max - height_min));    // Controls max height and min height

                const unsigned int base_height = (unsigned int)floor((1.0f / (a + b + c) + height_min));
                // printf("(%f %f)(%f %f)=%d\n", xOffset, zOffset, xOffset, zOffset, baseHeight);
                meshes.push_back(CityBlock::create(block_width * BLOCK_SIZE, block_depth * BLOCK_SIZE,
                                                   block_dimension_varience,
                                                   base_height, height_varience, {x * BLOCK_SIZE, 0, z * BLOCK_SIZE}));

                float progress = blocks_created++ / (float)total_blocks;
                if (progressBar != nullptr)
                {
                    printf("Loading: %f\n", progress);
                    progressBar->render(progress);
                }
            }
        }
    }
    printf("Generated [%d] buildings\n", CityBlock::building_count);
    CityBlock::building_count = 0;
}

City::~City()
{
    for (const BlockMesh *mesh : meshes)
    {
        delete mesh;
    }
}

void City::render(const wolf::Program *const program) const
{
    for (const BlockMesh *mesh : meshes)
    {
        mesh->render(program);
    }
}
