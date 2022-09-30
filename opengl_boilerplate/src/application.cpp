#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "renderer.h"

#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "vertex_buffer_layout.h"
#include "shader.h"
#include "texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/test_clear_colour.h"
#include "tests/test_texture2D.h"
#include "tests/test_batch_rendering.h"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, 1);


    window = glfwCreateWindow(1280, 720, "OpenGL Sandbox", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW Init Error" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
     
        Renderer renderer;


        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

        test::Test* current_test = nullptr;
        test::TestMenu* test_menu = new test::TestMenu(current_test);
        current_test = test_menu;

        test_menu->register_test<test::TestClearColour>("Clear Colour");
        test_menu->register_test<test::TestTexture2D>("Texture 2D");
        test_menu->register_test<test::TestBatchRendering>("Batch Rendering");

        while (!glfwWindowShouldClose(window))
        {
            renderer.clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (current_test)
            {
                current_test->on_update(0.0f);
                current_test->on_render();
                ImGui::Begin("Menu");
                if (current_test != test_menu && ImGui::Button("<-"))
                {
                    delete current_test;
                    current_test = test_menu;
                }
                current_test->on_imgui_render();
                ImGui::End();
            }


            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);

            glfwPollEvents();
        }

        if (current_test != test_menu)
            delete test_menu;
        delete current_test;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}