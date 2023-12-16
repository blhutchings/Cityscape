#pragma once
#include "../../wolf/wolf.h"
#include "../BlockMesh.h"
#include "../Chunk.h"
#include "CubeBuilding.h"
#include "CityChunk.h"

class CityBlock
{
public:
    static const BlockMesh *const create(unsigned int width, unsigned int depth, unsigned int dimension_varience, unsigned int baseHeight, unsigned int height_varience, glm::vec3 position);
    static unsigned int building_count;
private:
    static void generateBuilding(Chunk *const block,
                                 const unsigned int start_x, const unsigned int start_z,
                                 const unsigned int building_width, const unsigned int building_height, const unsigned int building_depth,
                                 const BuildingFront facing);
};