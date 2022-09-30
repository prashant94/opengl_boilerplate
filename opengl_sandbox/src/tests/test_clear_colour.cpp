#include "test_clear_colour.h"

#include "imgui/imgui.h"
#include "renderer.h"

namespace test
{
	TestClearColour::TestClearColour()
		: m_clear_colour { 0.2f, 0.3f, 0.8f, 1.0f }
	{
	}

	TestClearColour::~TestClearColour()
	{
		glcall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		glcall(glClear(GL_COLOR_BUFFER_BIT));
		glcall(glDisable(GL_BLEND));
	}

	void TestClearColour::on_update(float delta_time)
	{
	}

	void TestClearColour::on_render()
	{
		glcall(glClearColor(m_clear_colour[0], m_clear_colour[1], m_clear_colour[2], m_clear_colour[3]));
		glcall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColour::on_imgui_render()
	{
		ImGui::ColorEdit4("Clear Colour", m_clear_colour);
	}
}