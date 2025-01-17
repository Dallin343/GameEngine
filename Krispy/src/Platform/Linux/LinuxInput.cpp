//
// Created by dallin on 8/19/20.
//

#include "Krispy/Core/Input.h"
#include "Krispy/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Krispy {
    bool Input::IsKeyPressed(KeyCode keycode) {
        GLFWwindow* window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        int state = glfwGetKey(window, static_cast<int32_t>(keycode));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(MouseCode button) {
        GLFWwindow* window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        int state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    std::pair<float,float> Input::GetMousePosition() {
        GLFWwindow* window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        return { (float) xPos, (float) yPos };
    }

    float Input::GetMouseX() {
        auto [x, y] = GetMousePosition();
        return x;
    }

    float Input::GetMouseY() {
        auto [x, y] = GetMousePosition();
        return y;
    }
}