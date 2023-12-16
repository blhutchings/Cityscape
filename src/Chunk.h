#pragma once
#include "Block.h"
#include "../wolf/wolf.h"

class Chunk
{

public:
    Chunk(unsigned width = 32, unsigned depth = 64, unsigned height = 32);
    ~Chunk();
    static Chunk *const copyFromData(const BlockId *const data,
                                     unsigned int width,
                                     unsigned int height,
                                     unsigned int depth);

    BlockId get(const unsigned int x,
                const unsigned int y,
                const unsigned int z) const;

    void set(BlockId block,
             const unsigned int x,
             const unsigned int y,
             const unsigned int z);

    const unsigned int m_width;
    const unsigned int m_depth;
    const unsigned int m_height;
    glm::vec3 m_worldPosition = {0, 0, 0};

private:
    Chunk(const BlockId *const data,
          const unsigned int width,
          const unsigned int depth,
          const unsigned int height);
    BlockId *data = nullptr;
};