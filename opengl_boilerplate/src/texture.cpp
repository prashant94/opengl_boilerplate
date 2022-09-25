#include "texture.h"

#include "stb_image/stb_image.h"

Texture::Texture(const std::string& filepath)
	: m_renderer_id(0), m_filepath(filepath), m_local_buffer(nullptr), m_width(0), m_height(0), m_bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_local_buffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_bpp, 4);
	glcall(glGenTextures(1, &m_renderer_id));
	glcall(glBindTexture(GL_TEXTURE_2D, m_renderer_id));

	glcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	glcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	glcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	glcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	glcall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer));
	glcall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_local_buffer)
		stbi_image_free(m_local_buffer);
}

Texture::~Texture()
{
	glcall(glDeleteTextures(1, &m_renderer_id));
}

void Texture::bind(unsigned int slot) const
{
	glcall(glActiveTexture(GL_TEXTURE0 + slot));
	glcall(glBindTexture(GL_TEXTURE_2D, m_renderer_id));
}

void Texture::unbind() const
{
	glcall(glBindTexture(GL_TEXTURE_2D, 0));
}