#pragma once
#include "../../wolf/wolf.h"
#include "../BlockMesh.h"

enum class StreetDirection
{
    NORTH_SOUTH,
    EAST_WEST
};

class Street
{
public:
    static const BlockMesh *const create(StreetDirection direction, glm::vec3 position = {0, 0, 0});
    static const unsigned int width;
    static const unsigned int height;
    static const unsigned int depth;
};