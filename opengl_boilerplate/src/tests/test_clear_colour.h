#pragma once

#include "test.h"

namespace test
{
	class TestClearColour : public Test
	{
	public:
		TestClearColour();
		~TestClearColour();

		void on_update(float delta_time) override;
		void on_render() override;
		void on_imgui_render() override;
	private:
		float m_clear_colour[4];
	};
}