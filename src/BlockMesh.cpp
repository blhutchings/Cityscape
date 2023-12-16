#include "BlockMesh.h"
#include "BlockManager.h"

const glm::vec3 DIRECTION_IVEC3[6] = {
    {0, 0, -1}, // North (-z)
    {0, 0, 1},  // South (+z)
    {1, 0, 0},  // East (+x)
    {-1, 0, 0}, // West (-x)
    {0, 1, 0},  // Top (+y)
    {0, -1, 0}, // Bottom (-y)
};

const glm::vec3 NORMAL_IVEC3[6] = {
    {0, 0, 1},
    {0, 0, -1},
    {-1, 0, 0},
    {1, 0, 0},
    {0, -1, 0},
    {0, 1, 0},
};

const glm::vec3 TANGENT_IVEC3[6] = {
    {1, 0, 0},  // North (-z)
    {-1, 0, 0}, // South (+z)
    {0, 0, -1}, // East (+x)
    {0, 0, 1},  // West (-x)
    {0, 0, -1}, // Top (+y)
    {0, 0, 1},  // Bottom (-y)
};

const unsigned int FACE_INDICES[] = {1, 0, 3, 1, 3, 2}; // The two triangles to create the face of a block
const unsigned int UNIQUE_INDICES[] = {1, 0, 5, 2};
const unsigned int CUBE_INDICES[] = {
    1, 0, 3, 1, 3, 2, // North (-z)
    4, 5, 6, 4, 6, 7, // South (+z)
    5, 1, 2, 5, 2, 6, // East (+x)
    0, 4, 7, 0, 7, 3, // West (-x)
    2, 3, 7, 2, 7, 6, // Top (+y)
    5, 4, 0, 5, 0, 1, // Bottom (-y)
};

const float CUBE_VERTICES[] = {
    0, 0, 0,
    1, 0, 0,
    1, 1, 0,
    0, 1, 0,

    0, 0, 1,
    1, 0, 1,
    1, 1, 1,
    0, 1, 1};

const float CUBE_UVS[] = {
    1, 1,
    0, 1,
    0, 0,
    1, 0};

BlockMesh::BlockMesh(Chunk *const chunk, glm::vec3 worldPosition)
{
    vertexBufferData = new Vertex[chunk->m_width * chunk->m_height * chunk->m_depth * 8 * 5];
    indexBufferData = new unsigned int[chunk->m_width * chunk->m_height * chunk->m_depth * 36];

    for (unsigned int x = 0; x < chunk->m_width; ++x)
    {
        for (unsigned int y = 0; y < chunk->m_height; ++y)
        {
            for (unsigned int z = 0; z < chunk->m_depth; ++z)
            {
                BlockId currentBlock = chunk->get(x, y, z);

                bool currentTransparent = BlockManager::isTransparent(currentBlock);

                if (currentBlock != 0) // Skip Air
                {

                    glm::vec3 position = {worldPosition.x + x, worldPosition.y + y, worldPosition.z + z};

                    for (int d = 0; d < 6; ++d)
                    {
                        // Draw face if on edge of mesh
                        switch (d)
                        {
                        case FaceDirection::NORTH:
                            if (z == 0)
                            {
                                createBlockFace((BlockId)currentBlock, position, static_cast<FaceDirection>(d));
                                continue;
                            }
                            break;
                        case FaceDirection::SOUTH:
                            if (z == chunk->m_depth - 1)
                            {
                                createBlockFace((BlockId)currentBlock, position, static_cast<FaceDirection>(d));
                                continue;
                            }
                            break;
                        case FaceDirection::EAST:
                            if (x == chunk->m_width - 1)
                            {
                                createBlockFace((BlockId)currentBlock, position, static_cast<FaceDirection>(d));
                                continue;
                            }
                            break;
                        case FaceDirection::WEST:
                            if (x == 0)
                            {
                                createBlockFace((BlockId)currentBlock, position, static_cast<FaceDirection>(d));
                                continue;
                            }
                            break;
                        case FaceDirection::UP:
                            if (y == chunk->m_height - 1)
                            {
                                createBlockFace((BlockId)currentBlock, position, static_cast<FaceDirection>(d));
                                continue;
                            }
                            break;
                        case FaceDirection::DOWN:
                            if (y == 0)
                            {
                                createBlockFace((BlockId)currentBlock, position, static_cast<FaceDirection>(d));
                                continue;
                            }
                            break;
                        };

                        // Check neighbor block if transparent
                        const glm::ivec3 neighborPos = glm::ivec3(x, y, z) + glm::ivec3(DIRECTION_IVEC3[d]);
                        BlockId neightborBlock = chunk->get(neighborPos.x, neighborPos.y, neighborPos.z);
                        bool neighbor_transparent = BlockManager::isTransparent(neightborBlock);

                        // if nieghbor is transparent create face;
                        if (neighbor_transparent && (!currentTransparent || (currentTransparent && neightborBlock != currentBlock)))
                        {
                            createBlockFace((BlockId)currentBlock, position, static_cast<FaceDirection>(d));
                        }
                    }
                }
            }
        }
    }

    vbo = wolf::BufferManager::CreateVertexBuffer(vertexBufferData, vertexCount * sizeof(Vertex));
    ibo = wolf::BufferManager::CreateIndexBuffer(indexBufferData, indexCount);

    m_vertexDeclaration = new wolf::VertexDeclaration();
    m_vertexDeclaration->Begin();
    m_vertexDeclaration->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float); // Position
    m_vertexDeclaration->AppendAttribute(wolf::AT_Color, 2, wolf::CT_Float);    // UV
    m_vertexDeclaration->AppendAttribute(wolf::AT_Normal, 3, wolf::CT_Float);   // Normal
    m_vertexDeclaration->AppendAttribute(wolf::AT_Tangent, 3, wolf::CT_Float);  // Tangent
    m_vertexDeclaration->SetVertexBuffer(vbo);
    m_vertexDeclaration->SetIndexBuffer(ibo);
    m_vertexDeclaration->End();

    delete[] vertexBufferData;
    delete[] indexBufferData;
}

BlockMesh::~BlockMesh()
{
    wolf::BufferManager::DestroyBuffer(vbo);
    wolf::BufferManager::DestroyBuffer(ibo);
    delete m_vertexDeclaration;
}

void BlockMesh::createBlockFace(
    const BlockId id,
    const glm::vec3 position,
    const FaceDirection direction)
{
    glm::vec2 uv_unit = BlockManager::getAtlas()->spriteUnit;
    glm::vec2 uv_offset = BlockManager::getUVOffset(id);
    bool transparent = BlockManager::isTransparent(id);

    // Create Vertices
    for (size_t i = 0; i < 4; ++i)
    {
        const float *vertex = &CUBE_VERTICES[CUBE_INDICES[(direction * 6) + UNIQUE_INDICES[i]] * 3];

        vertexBufferData[vertexCount + i].x = position.x + vertex[0];
        vertexBufferData[vertexCount + i].y = position.y + vertex[1];
        vertexBufferData[vertexCount + i].z = position.z + vertex[2];
        vertexBufferData[vertexCount + i].u = uv_offset.x + (uv_unit.x * CUBE_UVS[(i * 2) + 0]);
        vertexBufferData[vertexCount + i].v = uv_offset.y + (uv_unit.y * CUBE_UVS[(i * 2) + 1]);
        vertexBufferData[vertexCount + i].normal = NORMAL_IVEC3[direction];
        vertexBufferData[vertexCount + i].tangent = TANGENT_IVEC3[direction];
    }

    // Create Indices
    for (size_t i = 0; i < 6; ++i)
    {
        indexBufferData[indexCount++] = vertexCount + FACE_INDICES[i];
    }
    vertexCount += 4;
}

void BlockMesh::render(const wolf::Program *const program) const
{
    m_vertexDeclaration->Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}