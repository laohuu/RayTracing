#ifndef RAYTRACING_RENDERER_H
#define RAYTRACING_RENDERER_H

#include "Camera.h"
#include "Core/Image.h"
#include "Ray.h"
#include "Scene.h"

#include <glm/glm.hpp>
#include <memory>

namespace RayTracing
{
    class Renderer
    {
    public:
        Renderer() = default;
        void OnResize(uint32_t width, uint32_t height);
        void Render(const Scene& scene, const Camera& camera);

        std::shared_ptr<Base::Image> GetFinalImage() const { return m_FinalImage; }

    private:
        glm::vec4 TraceRay(const Ray& ray);

    private:
        std::shared_ptr<Base::Image> m_FinalImage;
        uint32_t*                    m_ImageData = nullptr;

        const Scene*  m_ActiveScene  = nullptr;
        const Camera* m_ActiveCamera = nullptr;
    };
} // namespace RayTracing

#endif // RAYTRACING_RENDERER_H
