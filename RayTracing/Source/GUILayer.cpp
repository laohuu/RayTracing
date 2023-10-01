#include "GUILayer.h"

#include "Core/Timer.h"

#include <imgui.h>

using namespace Base;

namespace RayTracing
{
    GUILayer::GUILayer() : Layer("GUILayer"), m_Camera(45.0f, 0.1f, 100.0f) {}

    void GUILayer::OnAttach() {}

    void GUILayer::OnDetach() {}

    void GUILayer::OnUpdate(float ts) { m_Camera.OnUpdate(ts); }

    void GUILayer::OnImGuiRender()
    {
        ImGui::Begin("Settings");
        ImGui::Text("Last render: %.3fms", m_LastRenderTime);
        if (ImGui::Button("Render"))
        {
            Render();
        }

        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Viewport");

        m_ViewportWidth  = ImGui::GetContentRegionAvail().x;
        m_ViewportHeight = ImGui::GetContentRegionAvail().y;

        auto image = m_Renderer.GetFinalImage();
        if (image)
            ImGui::Image(image->GetDescriptorSet(),
                         {(float)image->GetWidth(), (float)image->GetHeight()},
                         ImVec2(0, 1),
                         ImVec2(1, 0));

        ImGui::End();
        ImGui::PopStyleVar();

        Render();
    }

    void GUILayer::Render()
    {
        Timer timer;

        // Render
        m_Renderer.OnResize(m_ViewportWidth, m_ViewportHeight);
        m_Camera.OnResize(m_ViewportWidth, m_ViewportHeight);
        m_Renderer.Render(m_Camera);

        m_LastRenderTime = timer.ElapsedMillis();
    }
} // namespace RayTracing