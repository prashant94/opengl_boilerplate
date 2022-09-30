#pragma once

#include "test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "texture.h"
#include "data_structures.h"

#include <memory>
#include <array>

namespace test
{
	class TestBatchRendering : public Test
	{
	public:
		TestBatchRendering();
		~TestBatchRendering();

		void on_update(float delta_time) override;
		void on_render() override;
		void on_imgui_render() override;
	private:
		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<VertexBuffer> m_vertex_buffer;
		std::unique_ptr<IndexBuffer> m_index_buffer;
		std::unique_ptr<Shader> m_shader;
		std::array<Vertex, 1000> m_vertices;
		std::array<std::unique_ptr<Texture>, 2> m_textures;

		glm::mat4 m_proj, m_view;
		glm::vec3 m_translation_batch;

		std::array<glm::vec2, 2> m_quadpos;
	};
}