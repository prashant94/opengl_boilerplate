#include "vertex_buffer.h"

#include "renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int type)
{
    glcall(glGenBuffers(1, &m_renderer_id));
    glcall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
    glcall(glBufferData(GL_ARRAY_BUFFER, size, data, type));
}

VertexBuffer::~VertexBuffer()
{
    glcall(glDeleteBuffers(1, &m_renderer_id));
}

void VertexBuffer::bind() const
{
    glcall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
}

void VertexBuffer::unbind() const
{
    glcall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
