#include "Renderer.h"
#include "Core/Random.h"

namespace RayTracing
{
    namespace Utils
    {
        static uint32_t ConvertToRGBA(const glm::vec4& color)
        {
            uint8_t r = (uint8_t)(color.r * 255.0f);
            uint8_t g = (uint8_t)(color.g * 255.0f);
            uint8_t b = (uint8_t)(color.b * 255.0f);
            uint8_t a = (uint8_t)(color.a * 255.0f);

            uint32_t result = (a << 24) | (b << 16) | (g << 8) | r;
            return result;
        }
    } // namespace Utils

    void Renderer::OnResize(uint32_t width, uint32_t height)
    {
        if (m_FinalImage)
        {
            // No resize necessary
            if (m_FinalImage->GetWidth() == width && m_FinalImage->GetHeight() == height)
                return;

            m_FinalImage->Resize(width, height);
        }
        else
        {
            m_FinalImage = std::make_shared<Base::Image>(width, height, Base::ImageFormat::RGBA);
        }

        delete[] m_ImageData;
        m_ImageData = new uint32_t[width * height];

        delete[] m_AccumulationData;
        m_AccumulationData = new glm::vec4[width * height];
    }

    void Renderer::Render(const Scene& scene, const Camera& camera)
    {
        m_ActiveScene  = &scene;
        m_ActiveCamera = &camera;

        if (m_FrameIndex == 1)
            memset(m_AccumulationData, 0, m_FinalImage->GetWidth() * m_FinalImage->GetHeight() * sizeof(glm::vec4));

        for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
        {
            for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
            {
                glm::vec4 color = PerPixel(x, y);
                m_AccumulationData[x + y * m_FinalImage->GetWidth()] += color;

                glm::vec4 accumulatedColor = m_AccumulationData[x + y * m_FinalImage->GetWidth()];
                accumulatedColor /= (float)m_FrameIndex;

                accumulatedColor = glm::clamp(accumulatedColor, glm::vec4(0.0f), glm::vec4(1.0f));
                m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(accumulatedColor);
            }
        }

        m_FinalImage->SetData(m_ImageData);

        if (m_Settings.Accumulate)
            m_FrameIndex++;
        else
            m_FrameIndex = 1;
    }

    glm::vec4 Renderer::PerPixel(uint32_t x, uint32_t y)
    {
        glm::vec3 rayOrigin    = m_ActiveCamera->GetPosition();
        glm::vec3 rayDirection = m_ActiveCamera->GetRayDirections()[x + y * m_FinalImage->GetWidth()];

        glm::vec3 light(0.0f);
        glm::vec3 contribution(1.0f);

        int bounces = 5;
        for (int i = 0; i < bounces; i++)
        {
            Ray                  ray(rayOrigin, rayDirection);
            Renderer::HitPayload payload = TraceRay(ray);
            if (payload.HitDistance < 0.0f)
            {
                glm::vec3 skyColor = glm::vec3(0.6f, 0.7f, 0.9f);
                light += skyColor * contribution;
                break;
            }

            const Sphere&   sphere   = m_ActiveScene->Spheres[payload.ObjectIndex];
            const Material& material = m_ActiveScene->Materials[sphere.MaterialIndex];

            glm::vec3 lightDir       = glm::normalize(glm::vec3(-1, -1, -1));
            float     lightIntensity = glm::max(glm::dot(payload.WorldNormal, -lightDir), 0.0f); // == cos(angle)

            light += material.Albedo * contribution * lightIntensity;
            contribution *= 0.5f;

            rayOrigin = payload.WorldPosition + payload.WorldNormal * 0.0001f;
            rayDirection =
                glm::reflect(rayDirection, payload.WorldNormal + material.Roughness * Base::Random::Vec3(-0.5f, 0.5f));
        }

        return {light, 1.0f};
    }

    Renderer::HitPayload Renderer::TraceRay(const Ray& ray)
    {
        // (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0
        // where
        // a = ray origin
        // b = ray direction
        // r = radius
        // t = hit distance

        int   closestSphere = -1;
        float hitDistance   = std::numeric_limits<float>::max();

        glm::vec3 rayOrigin    = ray.GetOrigin();
        glm::vec3 rayDirection = ray.GetDirection();

        for (size_t i = 0; i < m_ActiveScene->Spheres.size(); i++)
        {
            const Sphere& sphere = m_ActiveScene->Spheres[i];
            glm::vec3     origin = rayOrigin - sphere.Position;

            float a = glm::dot(rayDirection, rayDirection);
            float b = 2.0f * glm::dot(origin, rayDirection);

            // Quadratic forumula discriminant:
            // b^2 - 4ac
            float c = glm::dot(origin, origin) - sphere.Radius * sphere.Radius;

            float discriminant = b * b - 4.0f * a * c;
            if (discriminant < 0.0f)
                continue;

            // Quadratic formula:
            // (-b +- sqrt(discriminant)) / 2a

            // float t0 = (-b + glm::sqrt(discriminant)) / (2.0f * a); // Second hit distance (currently unused)
            float closestT = (-b - glm::sqrt(discriminant)) / (2.0f * a);
            if (closestT > 0.0f && closestT < hitDistance)
            {
                hitDistance   = closestT;
                closestSphere = (int)i;
            }
        }

        if (closestSphere < 0)
            return Miss(ray);

        return ClosestHit(ray, hitDistance, closestSphere);
    }

    Renderer::HitPayload Renderer::ClosestHit(const Ray& ray, float hitDistance, int objectIndex)
    {
        Renderer::HitPayload payload {};
        payload.HitDistance = hitDistance;
        payload.ObjectIndex = objectIndex;

        const Sphere& closestSphere = m_ActiveScene->Spheres[objectIndex];

        payload.WorldPosition = ray.At(hitDistance);
        payload.WorldNormal   = glm::normalize(payload.WorldPosition - closestSphere.Position);

        return payload;
    }

    Renderer::HitPayload Renderer::Miss(const Ray& ray)
    {
        Renderer::HitPayload payload {};
        payload.HitDistance = -1.0f;
        return payload;
    }
} // namespace RayTracing