#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

#include <glm/glm.hpp>

namespace RayTracing
{
    class Ray
    {
    public:
        Ray(const glm::vec3& origin, const glm::vec3& direction) : m_Origin(origin), m_Direction(direction) {}

        glm::vec3 GetOrigin() const { return m_Origin; }
        glm::vec3 GetDirection() const { return m_Direction; }

        glm::vec3 At(float tm) const;

    private:
        glm::vec3 m_Origin;
        glm::vec3 m_Direction;
    };
} // namespace RayTracing

#endif // RAYTRACING_RAY_H
