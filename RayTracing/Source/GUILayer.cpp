#include "GUILayer.h"

#include "Core/Image.h"
#include "Core/Random.h"
#include "Core/Timer.h"

#include <imgui.h>

using namespace Base;

namespace RayTracing
{
    GUILayer::GUILayer() : Layer("GUILayer") {}

    void GUILayer::OnAttach() {}

    void GUILayer::OnDetach() {}

    void GUILayer::OnUpdate(float ts) {}

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

        if (m_Image)
            ImGui::Image(m_Image->GetDescriptorSet(), {(float)m_Image->GetWidth(), (float)m_Image->GetHeight()});

        ImGui::End();
        ImGui::PopStyleVar();
    }

    void GUILayer::Render()
    {
        Timer timer;
        // Render
        if (!m_Image || m_ViewportWidth != m_Image->GetWidth() || m_ViewportHeight != m_Image->GetHeight())
        {
            delete[] m_ImageData;
            m_ImageData = new uint32_t[m_ViewportWidth * m_ViewportHeight];
            m_Image     = std::make_shared<Image>(m_ViewportWidth, m_ViewportHeight, ImageFormat::RGBA);
        }

        for (uint32_t i = 0; i < m_ViewportWidth * m_ViewportHeight; i++)
        {
            m_ImageData[i] = Random::UInt();
            m_ImageData[i] |= 0xff000000;
        }

        m_Image->SetData(m_ImageData);

        m_LastRenderTime = timer.ElapsedMillis();
    }

} // namespace RayTracing