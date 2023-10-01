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
        struct Settings
        {
            bool Accumulate = true;
        };

    public:
        Renderer() = default;
        void OnResize(uint32_t width, uint32_t height);
        void Render(const Scene& scene, const Camera& camera);

        std::shared_ptr<Base::Image> GetFinalImage() const { return m_FinalImage; }

        void      ResetFrameIndex() { m_FrameIndex = 1; }
        Settings& GetSettings() { return m_Settings; }

    private:
        struct HitPayload
        {
            float     HitDistance;
            glm::vec3 WorldPosition;
            glm::vec3 WorldNormal;

            int ObjectIndex;
        };

        glm::vec4 PerPixel(uint32_t x, uint32_t y); // RayGen

        HitPayload TraceRay(const Ray& ray);
        HitPayload ClosestHit(const Ray& ray, float hitDistance, int objectIndex);
        HitPayload Miss(const Ray& ray);

    private:
        std::shared_ptr<Base::Image> m_FinalImage;
        uint32_t*                    m_ImageData        = nullptr;
        glm::vec4*                   m_AccumulationData = nullptr;

        Settings m_Settings;

        const Scene*  m_ActiveScene  = nullptr;
        const Camera* m_ActiveCamera = nullptr;

        std::vector<uint32_t> m_ImageHorizontalIter, m_ImageVerticalIter;

        uint32_t m_FrameIndex = 1;
    };
} // namespace RayTracing

#endif // RAYTRACING_RENDERER_H
