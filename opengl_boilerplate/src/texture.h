#pragma once

#include "renderer.h"
#include <string>

class Texture
{
private:
	unsigned int m_renderer_id;
	std::string m_filepath;
	unsigned char* m_local_buffer;
	int m_width, m_height, m_bpp;
public:
	Texture(const std::string& filepath);
	~Texture();

	void bind(int slot = 0) const;
	void unbind() const;

	inline int get_width() const { return m_width; }
	inline int get_height() const { return m_height; }
};