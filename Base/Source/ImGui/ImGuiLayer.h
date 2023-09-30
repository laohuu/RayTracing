#ifndef BASE_IMGUILAYER_H
#define BASE_IMGUILAYER_H

#include "Core/Layer.h"
#include <imgui.h>

namespace Base
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override = default;

        void OnAttach() override;
        void OnDetach() override;

        void Begin();
        void End();

        void BlockEvents(bool block) { m_BlockEvents = block; }

        void SetDarkThemeColors();

        static uint32_t GetActiveWidgetID();

    private:
        bool m_BlockEvents = true;
    };
} // namespace Base

#endif // BASE_IMGUILAYER_H
