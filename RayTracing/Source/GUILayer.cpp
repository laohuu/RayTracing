#include "GUILayer.h"

#include "Core/Image.h"

#include <imgui.h>

namespace RayTracing
{
    GUILayer::GUILayer() : Layer("GUILayer")
    {
        m_Image = std::make_shared<Base::Image>("Assets/Textures/Checkerboard.png");
    }

    void GUILayer::OnAttach() {}

    void GUILayer::OnDetach() {}

    void GUILayer::OnUpdate(float ts) {}

    void GUILayer::OnImGuiRender()
    {
        ImGui::Begin("Hello");
        ImGui::Button("Button");
        ImGui::End();
        ImGui::Image(m_Image->GetDescriptorSet(),
                     {static_cast<float>(m_Image->GetWidth()), static_cast<float>(m_Image->GetHeight())});

        ImGui::ShowDemoWindow();
    }
} // namespace RayTracing