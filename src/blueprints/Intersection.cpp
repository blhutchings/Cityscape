#include "Intersection.h"

const unsigned int Intersection::width = 15;
const unsigned int Intersection::height = 1;
const unsigned int Intersection::depth = 15;

const int intersection_data[Intersection::width ][Intersection::height][Intersection::depth] = {
    {{4, 4, 4, 11, 11, 11, 11, 11, 11, 11, 11, 11, 4, 4, 4}},
    {{4, 4, 4, 11, 11, 11, 11, 12, 11, 11, 11, 11, 4, 4, 4}},
    {{4, 4, 4, 11, 11, 11, 11, 12, 11, 11, 11, 11, 4, 4, 4}},
    {{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}},
    {{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}},

    {{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}},
    {{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}},
    {{11, 12, 12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 11}},
    {{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}},
    {{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}},

    {{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}},
    {{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}},
    {{4, 4, 4, 11, 11, 11, 11, 12, 11, 11, 11, 11, 4, 4, 4}},
    {{4, 4, 4, 11, 11, 11, 11, 12, 11, 11, 11, 11, 4, 4, 4}},
    {{4, 4, 4, 11, 11, 11, 11, 11, 11, 11, 11, 11, 4, 4, 4}},
};


Chunk *intersection_chunk = Chunk::copyFromData((BlockId *)intersection_data, Intersection::width, Intersection::height, Intersection::depth);

const BlockMesh *const Intersection::create(glm::vec3 position)
{
    return new BlockMesh(intersection_chunk, position);
}
