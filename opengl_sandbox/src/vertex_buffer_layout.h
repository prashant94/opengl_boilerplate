#pragma once

#include <GL/glew.h>

#include <vector>
#include <stdexcept>

#include "renderer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	char normalized;

	static unsigned int get_size_of_type(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_UNSIGNED_INT: return sizeof(GLuint);
		case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;
public:
	VertexBufferLayout()
		: m_stride(0) {}

	template<typename T>
	void push(unsigned int count)
	{
		std::runtime_error(false);
	}

	template<>
	void push<float>(unsigned int count)
	{
		m_elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_stride += count * VertexBufferElement::get_size_of_type(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_INT);
	}

	template<>
	void push<char>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
		m_stride += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> get_elements() const { return m_elements; }
	inline unsigned int get_stride() const { return m_stride; }
};