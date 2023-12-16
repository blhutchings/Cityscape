#include "Street.h"

const unsigned int Street::width = 15;
const unsigned int Street::height = 1;
const unsigned int Street::depth = 15;

const int north_south_street_data[Street::width][Street::height][Street::depth] = {
    {{3, 4, 4, 11, 11, 11, 11, 11, 11, 11, 11, 11, 4, 4, 3}},
    {{4, 4, 4, 11, 11, 11, 11, 12, 11, 11, 11, 11, 4, 4, 4}},
    {{4, 4, 4, 11, 11, 11, 11, 12, 11, 11, 11, 11, 4, 4, 4}},
    {{4, 4, 4, 11, 11, 11, 11, 12, 11, 11, 11, 11, 4, 4, 4}},
    {{4, 4, 4, 11, 11, 11, 11, 11, 11, 11, 11, 11, 4, 4, 4}},

    {{4, 4, 4, 11, 11, 11, 11, 11, 11, 11, 11, 11, 4, 4, 4}},
    {{4, 4, 4, 11, 11, 11, 11, 12, 11, 11, 11, 11, 4, 4, 4}},
    {{4, 4, 4, 11, 11, 11, 11, 12, 11, 11, 11, 11, 4, 4, 4}},
    {{4, 4, 4, 11, 11, 11, 11, 12, 11, 11, 11, 11, 4, 4, 4}},
    {{4, 4, 4, 11, 11, 11, 11, 11, 11, 11, 11, 11, 4, 4, 4}},

    {{4, 4, 4, 11, 11, 11, 11, 11, 11, 11, 11, 11, 4, 4, 4}},
    {{4, 4, 4, 11, 11, 11, 11, 12, 11, 11, 11, 11, 4, 4, 4}},
    {{4, 4, 4, 11, 11, 11, 11, 12, 11, 11, 11, 11, 4, 4, 4}},
    {{4, 4, 4, 11, 11, 11, 11, 12, 11, 11, 11, 11, 4, 4, 4}},
    {{3, 4, 4, 11, 11, 11, 11, 11, 11, 11, 11, 11, 4, 4, 3}},
};

const int east_west_street_data[Street::width][Street::height][Street::depth] = {
    {{3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3}},
    {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}},
    {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}},
    {{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}},
    {{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}},

    {{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}},
    {{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}},
    {{11, 12, 12, 12, 11, 11, 12, 12, 12, 11, 11, 12, 12, 12, 11}},
    {{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}},
    {{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}},

    {{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}},
    {{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}},
    {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}},
    {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}},
    {{3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3}},
};


Chunk *north_south_street_chunk = Chunk::copyFromData((BlockId *)north_south_street_data, Street::width, Street::height, Street::depth);
Chunk *east_west_street_chunk = Chunk::copyFromData((BlockId *)east_west_street_data, Street::width, Street::height, Street::depth);

const BlockMesh *const Street::create(StreetDirection direction, glm::vec3 position)
{
    return direction == StreetDirection::NORTH_SOUTH ? new BlockMesh(north_south_street_chunk, position) : new BlockMesh(east_west_street_chunk, position);
}
