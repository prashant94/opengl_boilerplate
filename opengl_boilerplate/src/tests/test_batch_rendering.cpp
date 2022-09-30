#include <format>
#include <array>

#include "test_batch_rendering.h"

#include "imgui/imgui.h"
#include "renderer.h"
#include "data_structures.h"

static Vertex* create_quad(Vertex* target, float x, float y, float texture_id, float size = 1.0f)
{
    target->positions = { x, y };
    target->tex_coords = { 0.0f, 0.0f };
    target->colour = { 0.2f, 0.3f, 0.8f, 1.0f };
    target->tex_index = texture_id;
    target++;

    target->positions = { x + size, y };
    target->tex_coords = { 1.0f, 0.0f };
    target->colour = { 0.2f, 0.3f, 0.8f, 1.0f };
    target->tex_index = texture_id;
    target++;

    target->positions = { x + size, y + size };
    target->tex_coords = { 1.0f, 1.0f };
    target->colour = { 0.2f, 0.3f, 0.8f, 1.0f };
    target->tex_index = texture_id;
    target++;

    target->positions = { x, y + size };
    target->tex_coords = { 0.0f, 1.0f };
    target->colour = { 0.2f, 0.3f, 0.8f, 1.0f };
    target->tex_index = texture_id;
    target++;

    return target;
}


namespace test
{
	TestBatchRendering::TestBatchRendering()
        : m_proj(glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f)), m_view(glm::translate(glm::mat4(1.0f), 
            glm::vec3(0.0f, 0.0f, 0.0f))), m_translation_batch(200.0f, 200.0f, 0.0f)
	{
        
        const size_t max_quad_count = 1000;
        const size_t max_vertex_count = max_quad_count * 4;
        const size_t max_index_count = max_quad_count * 6;

        m_quadpos[0] = { 300.0f, 100.0f };
        m_quadpos[1] = { 400.0f, 100.0f };

        m_vao = std::make_unique<VertexArray>();
        m_vertex_buffer = std::make_unique<VertexBuffer>(nullptr, max_quad_count * sizeof(Vertex), GL_DYNAMIC_DRAW);
        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        layout.push<float>(4);
        layout.push<float>(1);
        m_vao->add_buffer(*m_vertex_buffer, layout);

        uint32_t indices[max_index_count];
        uint32_t offset = 0;
        for (size_t i = 0; i < max_index_count; i += 6)
        {
            indices[i + 0] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;
                              
            indices[i + 3] = 2 + offset;
            indices[i + 4] = 3 + offset;
            indices[i + 5] = 0 + offset;
            offset += 4;
        }


        m_index_buffer = std::make_unique<IndexBuffer>(indices, max_index_count);

        m_shader = std::make_unique<Shader>("res/shaders/batch.shader");
        m_shader->bind();
        m_shader->set_uniform4f("u_colour", 0.8f, 0.3f, 0.8f, 1.0f);

        for (int i = 0; i < m_textures.size(); i++)
        {
            std::string path = std::format("res/textures/tex{}.png", std::to_string(i));
            m_textures[i] = std::make_unique<Texture>(path.c_str());
        }

        int samplers[2] = { 0, 1 };
        m_shader->set_uniform1iv("u_textures", 2, samplers);
	}

	TestBatchRendering::~TestBatchRendering()
	{
        glcall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        glcall(glClear(GL_COLOR_BUFFER_BIT));
        glcall(glDisable(GL_BLEND));
	}

	void TestBatchRendering::on_update(float delta_time)
	{
	}

	void TestBatchRendering::on_render()
	{
        
        Vertex* buffer = m_vertices.data();

        buffer = create_quad(buffer, m_quadpos[0].x, m_quadpos[0].y, 0.0f, 100.0f);
        buffer = create_quad(buffer, m_quadpos[1].x, m_quadpos[1].y, 1.0f, 100.0f);
        
        for (int x = 0; x < 5; x++)
        {
            for (int y = 0; y < 5; y++)
            {
                buffer = create_quad(buffer, x * 50, y * 50, (x + y) % 2, 50);
            }

        }

        m_vertex_buffer->bind();
        glcall(glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(Vertex), m_vertices.data()));

		glcall(glClearColor(0.0f, 0.0f, 0.5f, 1.0f));
		glcall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translation_batch);
        glm::mat4 mvp = m_proj * m_view * model;
        for (int i = 0; i < m_textures.size(); i++)
            m_textures[i]->bind(i);
        m_shader->bind();
        m_shader->set_uniformmat4f("u_mvp", mvp);
        renderer.draw(*m_vao, *m_index_buffer, *m_shader);
	}

	void TestBatchRendering::on_imgui_render()
	{
        ImGui::SliderFloat3("Translation Batch", &m_translation_batch.x, 0.0f, 960.0f);
        ImGui::SliderFloat2("Translation A", &m_quadpos[0].x, 0.0f, 960.0f);
        ImGui::SliderFloat2("Translation B", &m_quadpos[1].x, 0.0f, 960.0f);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}