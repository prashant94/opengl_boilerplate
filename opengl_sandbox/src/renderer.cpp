#include "renderer.h"

#include <iostream>

void GL_clear_error()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GL_log_call(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] " << "(" << error << ") " << function << " " << file << ": " << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.bind();
    va.bind();
    ib.bind();
    glcall(glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const
{
    glcall(glClear(GL_COLOR_BUFFER_BIT));
}