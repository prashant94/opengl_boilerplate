#pragma once

#include <GL/glew.h>

#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define glcall(x) GL_clear_error(); x; ASSERT(GL_log_call(#x, __FILE__, __LINE__));

void GL_clear_error();
bool GL_log_call(const char* function, const char* file, int line);


class Renderer
{
public:
	void clear() const;
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};