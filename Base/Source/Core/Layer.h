#ifndef BASE_LAYER_H
#define BASE_LAYER_H

#include "BasePCH.h"

namespace Base
{
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(float ts) {}

        virtual void OnImGuiRender() {}

        const std::string& GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };
} // namespace Base

#endif // BASE_LAYER_H
