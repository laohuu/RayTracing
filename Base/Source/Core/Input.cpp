#include "Input.h"

#include "Core/Application.h"

#include <GLFW/glfw3.h>

namespace Base
{
    bool Input::IsKeyPressed(KeyCode key)
    {
        auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow());
        auto  state  = glfwGetKey(window, static_cast<int32_t>(key));
        return state == GLFW_PRESS;
    }

    bool Input::IsMouseButtonPressed(MouseCode button)
    {
        auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow());
        auto  state  = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::GetMousePosition()
    {
        auto*  window = static_cast<GLFWwindow*>(Application::Get().GetWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return {(float)xpos, (float)ypos};
    }

    float Input::GetMouseX() { return GetMousePosition().x; }

    float Input::GetMouseY() { return GetMousePosition().y; }

    void Input::SetCursorMode(CursorMode mode)
    {
        GLFWwindow* windowHandle = Application::Get().GetWindow();
        glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int)mode);
    }
} // namespace Base