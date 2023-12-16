#pragma once
#include "../wolf/wolf.h"
#include "Chunk.h"
#include "BlockAtlas.h"
#include "BlockManager.h"

// Used to specify what face of a block is being created
enum FaceDirection
{
   NORTH = 0,
   SOUTH = 1,
   EAST = 2,
   WEST = 3,
   UP = 4,
   DOWN = 5
};

struct Vertex
{
   GLfloat x, y, z;
   GLfloat u, v;
   glm::vec3 normal;
   glm::vec3 tangent;
};

class BlockMesh
{
public:
   BlockMesh(Chunk *const chunk, glm::vec3 worldPosition = {0.0f, 0.0f, 0.0f});
   ~BlockMesh();

   void createBlockFace(const BlockId id, const glm::vec3 position, const FaceDirection direction);

   void render(const wolf::Program *const program) const;

private:
   wolf::VertexBuffer *vbo = nullptr;
   wolf::IndexBuffer *ibo = nullptr;
   wolf::VertexDeclaration *m_vertexDeclaration = nullptr;

   Vertex *vertexBufferData = nullptr;
   unsigned int vertexCount = 0;
   unsigned int *indexBufferData = nullptr;
   unsigned int indexCount = 0;
};