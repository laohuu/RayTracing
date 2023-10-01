#ifndef BASE_INPUT_H
#define BASE_INPUT_H

#include "KeyCodes.h"
#include "MouseCodes.h"

#include <glm/glm.hpp>

namespace Base
{
    enum class CursorMode
    {
        Normal = 0,
        Hidden = 1,
        Locked = 2
    };

    class Input
    {
    protected:
        Input() = default;

    public:
        Input(const Input&) = delete;
        virtual ~Input()    = default;

        Input& operator=(const Input&) = delete;

        static bool IsKeyPressed(KeyCode key);
        static bool IsMouseButtonPressed(MouseCode button);

        static glm::vec2 GetMousePosition();
        static float     GetMouseX();
        static float     GetMouseY();

        static void SetCursorMode(CursorMode mode);
    };
} // namespace Base

#endif // BASE_INPUT_H
