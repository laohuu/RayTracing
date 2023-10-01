#ifndef RAYTRACING_GUILAYER_H
#define RAYTRACING_GUILAYER_H

#include <Base.h>

#include "Core/Image.h"

#include "Camera.h"
#include "Renderer.h"

namespace RayTracing
{
    class GUILayer : public Base::Layer
    {
    public:
        GUILayer();
        ~GUILayer() override = default;

        void OnUpdate(float ts) override;
        void OnImGuiRender() override;

        void Render();

    private:
        Renderer m_Renderer;
        Camera   m_Camera;
        Scene    m_Scene;

        float m_LastRenderTime = 0.0f;

        uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
    };
} // namespace RayTracing

#endif // RAYTRACING_GUILAYER_H
