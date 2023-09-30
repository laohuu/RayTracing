#ifndef RAYTRACING_GUILAYER_H
#define RAYTRACING_GUILAYER_H

#include <Base.h>

namespace Base
{
    class GUILayer : public Layer
    {
    public:
        GUILayer();
        ~GUILayer() override = default;

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(float ts) override;

        void OnImGuiRender() override;
    };
} // namespace Base

#endif // RAYTRACING_GUILAYER_H
