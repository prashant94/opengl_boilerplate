#pragma once

#include "test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "texture.h"

#include <memory>

namespace test
{
	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void on_update(float delta_time) override;
		void on_render() override;
		void on_imgui_render() override;
	private:
		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<VertexBuffer> m_vertex_buffer;
		std::unique_ptr<IndexBuffer> m_index_buffer;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Texture> m_texture;

		glm::mat4 m_proj, m_view;
		glm::vec3 m_translationA, m_translationB;
	};
}