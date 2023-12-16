#include "Chunk.h"

Chunk::Chunk(const unsigned int width,
             const unsigned int height,
             const unsigned int depth)
    : m_width(width), m_height(height), m_depth(depth)
{
    this->data = new BlockId[width * height * depth]();
}

Chunk::Chunk(const BlockId *const data,
             const unsigned int width,
             const unsigned int height,
             const unsigned int depth)
    : m_width(width), m_height(height), m_depth(depth)
{
    this->data = new BlockId[width * height * depth]();
    std::memcpy(this->data, data, width * height * depth * sizeof(unsigned int));
}

Chunk::~Chunk()
{
    delete[] this->data;
}

BlockId Chunk::get(const unsigned int x,
                   const unsigned int y,
                   const unsigned int z) const
{
    return this->data[x + m_width * (y + m_height * z)];
}

void Chunk::set(BlockId block,
                const unsigned int x,
                const unsigned int y,
                const unsigned int z)
{
    this->data[x + m_width * (y + m_height * z)] = block;
}
Chunk *const Chunk::copyFromData(const BlockId *const data,
                                 const unsigned int width,
                                 const unsigned int height,
                                 const unsigned int depth)
{
    return new Chunk(data, width, height, depth);
}
