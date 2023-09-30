#include "GUILayer.h"

#include <imgui.h>

namespace RayTracing
{
    GUILayer::GUILayer() : Layer("GUILayer") {}

    void GUILayer::OnAttach() {}

    void GUILayer::OnDetach() {}

    void GUILayer::OnUpdate(float ts) {}

    void GUILayer::OnImGuiRender()
    {
        ImGui::Begin("Hello");
        ImGui::Button("Button");
        ImGui::End();

        ImGui::ShowDemoWindow();
    }
} // namespace RayTracing