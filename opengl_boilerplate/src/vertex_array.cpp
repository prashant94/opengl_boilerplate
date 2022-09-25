#include "vertex_array.h"

#include "vertex_buffer_layout.h"
#include "renderer.h"

VertexArray::VertexArray()
{
	glcall(glGenVertexArrays(1, &m_renderer_id));
	
}

VertexArray::~VertexArray()
{
	glcall(glDeleteVertexArrays(1, &m_renderer_id));
}

void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	const auto& elements = layout.get_elements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glcall(glEnableVertexAttribArray(i));
		glcall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), (const void*)offset));
		offset += element.count * VertexBufferElement::get_size_of_type(element.type);
	}
}

void VertexArray::bind() const
{
	glcall(glBindVertexArray(m_renderer_id));
}

void VertexArray::unbind() const
{
	glcall(glBindVertexArray(0));
}
