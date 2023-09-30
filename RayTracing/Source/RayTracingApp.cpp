#include <Base.h>
#include <Core/EntryPoint.h>

#include "GUILayer.h"

namespace Base
{
    class RayTracingApp : public Application
    {
    public:
        RayTracingApp(const ApplicationSpecification& spec) : Application(spec) { PushLayer(new GUILayer()); }

        ~RayTracingApp() override = default;

    private:
    };

    Application* CreateApplication(int argc, char** argv)
    {
        ApplicationSpecification spec;
        spec.Name = "RayTracing";

        return new RayTracingApp(spec);
    }
} // namespace Base