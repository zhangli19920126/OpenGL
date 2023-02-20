#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

class ImguiHelper {
public:
    void bindGui(GLFWwindow* window, bool install_callbacks)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void guiRender(float* r, float* g, float* b, float* a)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("GUI");
            //if (ImGui::Button("Button"))
             //   counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            ImGui::SliderFloat("Red", r, 0.0f, 1.0f);
            ImGui::SliderFloat("Green", g, 0.0f, 1.0f);
            ImGui::SliderFloat("Blue", b, 0.0f, 1.0f);
            //ImGui::SliderFloat("Alpha", a, 0.0f, 1.0f);

            //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void guiRender1F(float* r, float min, float max, const char* name)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {

            ImGui::Begin("GUI");
            ImGui::SameLine();
            ImGui::SliderFloat(name, r, min, max);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void guiRenderTrans(float* rotation, float *scale)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {

            ImGui::Begin("GUI");
            ImGui::SameLine();
            ImGui::SliderFloat("rotation", rotation, 0.0f, 360.0f);
            ImGui::SliderFloat("scale", scale, 0.0f, 1.0f);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }


    void guiClear()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

private:
    const char* glsl_version = "#version 130";
};

