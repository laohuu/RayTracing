#ifndef RAYTRACING_GUILAYER_H
#define RAYTRACING_GUILAYER_H

#include <Base.h>

#include "Core/Image.h"

namespace RayTracing
{
    class GUILayer : public Base::Layer
    {
    public:
        GUILayer();
        ~GUILayer() override = default;

        void OnAttach() override;
        void OnDetach() override;

        void OnUpdate(float ts) override;
        void OnImGuiRender() override;

    private:
        std::shared_ptr<Base::Image> m_Image;
    };
} // namespace RayTracing

#endif // RAYTRACING_GUILAYER_H
