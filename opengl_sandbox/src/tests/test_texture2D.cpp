#include "test_texture2D.h"

#include "imgui/imgui.h"
#include "renderer.h"


namespace test
{
	TestTexture2D::TestTexture2D()
        : m_proj(glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f)), m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))), 
        m_translationA(200.0f, 200.0f, 0.0f),
        m_translationB(400.0f, 200.0f, 0.0f)
	{
        float positions[] = {
           -50.0f, -50.0f, 0.0f, 0.0f,
            50.0f, -50.0f, 1.0f, 0.0f,
            50.0f,  50.0f, 1.0f, 1.0f,
           -50.0f,  50.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        glcall(glEnable(GL_BLEND));
        glcall(glBlendFunc(GL_ONE, GL_ONE));

        m_vao = std::make_unique<VertexArray>();
        m_vertex_buffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float), GL_STATIC_DRAW);
        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        m_vao->add_buffer(*m_vertex_buffer, layout);


        m_index_buffer = std::make_unique<IndexBuffer>(indices, 6);

        m_shader = std::make_unique<Shader>("res/shaders/basic.shader");
        m_shader->bind();
        m_shader->set_uniform4f("u_colour", 0.8f, 0.3f, 0.8f, 1.0f);


        m_texture = std::make_unique<Texture>("res/textures/tex0.png");
        m_texture->bind();
        m_shader->set_uniform1i("u_texture", 0);

	}

	TestTexture2D::~TestTexture2D()
	{
        glcall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        glcall(glClear(GL_COLOR_BUFFER_BIT));
        glcall(glDisable(GL_BLEND));
	}

	void TestTexture2D::on_update(float delta_time)
	{
	}

	void TestTexture2D::on_render()
	{
		glcall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		glcall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
            glm::mat4 mvp = m_proj * m_view * model;
            m_shader->bind();
            m_shader->set_uniformmat4f("u_mvp", mvp);
            renderer.draw(*m_vao, *m_index_buffer, *m_shader);
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
            glm::mat4 mvp = m_proj * m_view * model;
            m_shader->bind();
            m_shader->set_uniformmat4f("u_mvp", mvp);
            renderer.draw(*m_vao, *m_index_buffer, *m_shader);
        }

	}

	void TestTexture2D::on_imgui_render()
	{
        ImGui::SliderFloat3("Translation A", &m_translationA.x, 0.0f, 960.0f); 
        ImGui::SliderFloat3("Translation B", &m_translationB.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}