#pragma once

#include <cstdint>

#include "VertexBuffer.h"

namespace OpenGLCore {
class VertexArray {
public:
  VertexArray();
  ~VertexArray() {}

  void Bind();

  void AddVertexBuffer(const VertexBuffer &vertexBuffer);
  void SetIndexBuffer(const IndexBuffer &indexBuffer);

  const IndexBuffer &GetIndexBuffer() const { return m_IndexBuffer; }

private:
  uint32_t m_RendererID;
  std::vector<VertexBuffer> m_VertexBuffers;
  IndexBuffer m_IndexBuffer;
};
} // namespace OpenGLCore
