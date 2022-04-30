#include "VertexBuffer.h"

#include <glad/glad.h>

namespace OpenGLCore {

VertexBuffer::VertexBuffer(float *values, size_t size) {
  glGenBuffers(1, &m_RendererID);
  glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
  glBufferData(GL_ARRAY_BUFFER, size, values, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }

IndexBuffer::IndexBuffer(uint32_t *indices, size_t count) {
  glGenBuffers(1, &m_RendererID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices,
               GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}
} // namespace OpenGLCore
