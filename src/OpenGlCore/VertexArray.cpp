#include "VertexArray.h"

#include <glad/glad.h>

namespace OpenGLCore {
static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
  switch (type) {
  case ShaderDataType::Float:
    return GL_FLOAT;
  case ShaderDataType::Float2:
    return GL_FLOAT;
  case ShaderDataType::Float3:
    return GL_FLOAT;
  case ShaderDataType::Float4:
    return GL_FLOAT;
  case ShaderDataType::Mat3:
    return GL_FLOAT;
  case ShaderDataType::Mat4:
    return GL_FLOAT;
  case ShaderDataType::Int:
    return GL_INT;
  case ShaderDataType::Int2:
    return GL_INT;
  case ShaderDataType::Int3:
    return GL_INT;
  case ShaderDataType::Int4:
    return GL_INT;
  case ShaderDataType::Bool:
    return GL_BOOL;
  case ShaderDataType::None:
    return 0;
  }

  return 0;
}
VertexArray::VertexArray() { glGenVertexArrays(1, &m_RendererID); }

void VertexArray::Bind() { glBindVertexArray(m_RendererID); }

void VertexArray::AddVertexBuffer(const VertexBuffer &vertexBuffer) {
  glBindVertexArray(m_RendererID);

  vertexBuffer.Bind();

  uint32_t index = 0;
  const auto &layout = vertexBuffer.GetLayout();
  for (const auto &element : layout) {
    switch (element.Type) {
    case ShaderDataType::None:
      break;
    case ShaderDataType::Int:
    case ShaderDataType::Int2:
    case ShaderDataType::Int3:
    case ShaderDataType::Int4:
    case ShaderDataType::Bool:
      glEnableVertexAttribArray(index);
      glVertexAttribIPointer(index, element.GetComponentCount(),
                             ShaderDataTypeToOpenGLBaseType(element.Type),
                             layout.GetStride(),
                             (const void *)(uintptr_t)element.Offset);
      index++;
      break;
    case ShaderDataType::Float:
    case ShaderDataType::Float2:
    case ShaderDataType::Float3:
    case ShaderDataType::Float4:
      glEnableVertexAttribArray(index);
      glVertexAttribPointer(index, element.GetComponentCount(),
                            ShaderDataTypeToOpenGLBaseType(element.Type),
                            element.Normalized ? GL_TRUE : GL_FALSE,
                            layout.GetStride(),
                            (const void *)(uintptr_t)element.Offset);
      index++;
      break;
    case ShaderDataType::Mat3:
    case ShaderDataType::Mat4:
      uint8_t count = element.GetComponentCount();
      for (uint8_t i = 0; i < count; i++) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index, count, ShaderDataTypeToOpenGLBaseType(element.Type),
            element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(),
            (const void *)(uintptr_t)(element.Offset +
                                      sizeof(float) * count * i));
        glVertexAttribDivisor(index, 1);
        index++;
      }
      break;
    }
  }

  m_VertexBuffers.push_back(vertexBuffer);
}

void VertexArray::SetIndexBuffer(const IndexBuffer &indexBuffer) {
  glBindVertexArray(m_RendererID);
  indexBuffer.Bind();

  m_IndexBuffer = indexBuffer;
}

} // namespace OpenGLCore
