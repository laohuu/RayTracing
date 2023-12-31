#include "GUILayer.h"

#include "Core/Timer.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

using namespace Base;

namespace RayTracing
{
    GUILayer::GUILayer() : Layer("GUILayer"), m_Camera(45.0f, 0.1f, 100.0f)
    {
        Material& pinkSphere = m_Scene.Materials.emplace_back();
        pinkSphere.Albedo    = {1.0f, 0.0f, 1.0f};
        pinkSphere.Roughness = 0.0f;

        Material& blueSphere = m_Scene.Materials.emplace_back();
        blueSphere.Albedo    = {0.2f, 0.3f, 1.0f};
        blueSphere.Roughness = 0.1f;

        Material& orangeSphere     = m_Scene.Materials.emplace_back();
        orangeSphere.Albedo        = {0.8f, 0.5f, 0.2f};
        orangeSphere.Roughness     = 0.1f;
        orangeSphere.EmissionColor = orangeSphere.Albedo;
        orangeSphere.EmissionPower = 2.0f;

        {
            Sphere sphere;
            sphere.Position      = {0.0f, 0.0f, 0.0f};
            sphere.Radius        = 1.0f;
            sphere.MaterialIndex = 0;
            m_Scene.Spheres.emplace_back(sphere);
        }

        {
            Sphere sphere;
            sphere.Position      = {2.0f, 0.0f, 0.0f};
            sphere.Radius        = 1.0f;
            sphere.MaterialIndex = 2;
            m_Scene.Spheres.emplace_back(sphere);
        }

        {
            Sphere sphere;
            sphere.Position      = {0.0f, -101.0f, 0.0f};
            sphere.Radius        = 100.0f;
            sphere.MaterialIndex = 1;
            m_Scene.Spheres.emplace_back(sphere);
        }
    }

    void GUILayer::OnUpdate(float ts)
    {
        if (m_Camera.OnUpdate(ts))
            m_Renderer.ResetFrameIndex();
    }

    void GUILayer::OnImGuiRender()
    {
        ImGui::Begin("Settings");
        ImGui::Text("Last render: %.3fms", m_LastRenderTime);
        if (ImGui::Button("Render"))
        {
            Render();
        }

        ImGui::Checkbox("Accumulate", &m_Renderer.GetSettings().Accumulate);

        if (ImGui::Button("Reset"))
            m_Renderer.ResetFrameIndex();

        ImGui::End();

        ImGui::Begin("Scene");
        for (int i = 0; i < m_Scene.Spheres.size(); i++)
        {
            ImGui::PushID(i);

            Sphere& sphere = m_Scene.Spheres[i];
            ImGui::DragFloat3("Position", glm::value_ptr(sphere.Position), 0.1f);
            ImGui::DragFloat("Radius", &sphere.Radius, 0.1f);
            ImGui::DragInt("Material", &sphere.MaterialIndex, 1.0f, 0, (int)m_Scene.Materials.size() - 1);

            ImGui::Separator();

            ImGui::PopID();
        }

        for (int i = 0; i < m_Scene.Materials.size(); i++)
        {
            ImGui::PushID(i);

            Material& material = m_Scene.Materials[i];
            ImGui::ColorEdit3("Albedo", glm::value_ptr(material.Albedo));
            ImGui::DragFloat("Roughness", &material.Roughness, 0.05f, 0.0f, 1.0f);
            ImGui::DragFloat("Metallic", &material.Metallic, 0.05f, 0.0f, 1.0f);
            ImGui::ColorEdit3("Emission Color", glm::value_ptr(material.EmissionColor));
            ImGui::DragFloat("Emission Power", &material.EmissionPower, 0.05f, 0.0f, FLT_MAX);

            ImGui::Separator();

            ImGui::PopID();
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
        m_Renderer.Render(m_Scene, m_Camera);

        m_LastRenderTime = timer.ElapsedMillis();
    }
} // namespace RayTracing