#ifndef RAYTRACING_RENDERER_H
#define RAYTRACING_RENDERER_H

#include "Core/Image.h"

#include <glm/glm.hpp>
#include <memory>

namespace RayTracing
{
    class Renderer
    {
    public:
        Renderer() = default;
        void OnResize(uint32_t width, uint32_t height);
        void Render();

        std::shared_ptr<Base::Image> GetFinalImage() const { return m_FinalImage; }

    private:
        uint32_t PerPixel(glm::vec2 coord);

    private:
        std::shared_ptr<Base::Image> m_FinalImage;
        uint32_t*                    m_ImageData = nullptr;
    };
} // namespace RayTracing

#endif // RAYTRACING_RENDERER_H
