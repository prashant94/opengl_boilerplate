#include "index_buffer.h"

#include "renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    glcall(glGenBuffers(1, &m_renderer_id));
    glcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
    glcall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    glcall(glDeleteBuffers(1, &m_renderer_id));
}

void IndexBuffer::bind() const
{
    glcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
}

void IndexBuffer::unbind() const
{
    glcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
