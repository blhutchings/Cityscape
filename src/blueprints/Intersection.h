#pragma once
#include "../../wolf/wolf.h"
#include "../BlockMesh.h"

class Intersection
{
public:
    static const BlockMesh *const create(glm::vec3 position = {0, 0, 0});
    static const unsigned int width;
    static const unsigned int height;
    static const unsigned int depth;
};