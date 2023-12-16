#pragma once
#include "../wolf/wolf.h"
#include <vector>
#include "BlockMesh.h"
#include "./blueprints/CityChunk.h"
#include "./blueprints/Street.h"
#include "./blueprints/Intersection.h"
#include "./blueprints/CityBlock.h"
#include "LoadingBar.h"

class City
{

public:
    City(unsigned int city_width, unsigned int city_depth,
         unsigned int block_width, unsigned int block_depth,
         unsigned int block_dimension_varience,
         unsigned int height_max, unsigned int height_min, unsigned int height_varience,
         LoadingBar *const progress = nullptr);
    ~City();
    void render(const wolf::Program *const program) const;

private:
    std::vector<const BlockMesh *> meshes;
};