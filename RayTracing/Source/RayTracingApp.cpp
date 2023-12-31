#include "GUILayer.h"

#include <Base.h>
#include <Core/EntryPoint.h>

namespace RayTracing
{
    class RayTracingApp : public Base::Application
    {
    public:
        RayTracingApp(const Base::ApplicationSpecification& spec) : Application(spec) { PushLayer(new GUILayer()); }
        ~RayTracingApp() override = default;
    };
} // namespace RayTracing

Base::Application* Base::CreateApplication(int argc, char** argv)
{
    Base::ApplicationSpecification spec;
    spec.Name = "RayTracing";

    return new RayTracing::RayTracingApp(spec);
}