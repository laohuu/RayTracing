#include "Ray.h"

namespace RayTracing
{
    glm::vec3 Ray::At(float tm) const
    {
        {
            return m_Origin + m_Direction * tm;
        }
    }
} // namespace RayTracing
