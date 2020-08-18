//
// Created by dallin on 8/12/20.
//

#include <imgui.h>
#include "Krispy/Events/ApplicationEvent.h"
#include "Krispy/Events/MouseEvent.h"
#include "Krispy/Events/KeyEvent.h"
#include "LinuxWindow.h"

namespace Krispy {
    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char* description) {
        KRISPY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Window* Window::Create(const WindowProps &props) {
        return new LinuxWindow(props);
    }

    LinuxWindow::LinuxWindow(const WindowProps &props) {
        Init(props);
    }

    LinuxWindow::~LinuxWindow() noexcept {
        Shutdown();
    }

    void LinuxWindow::Init(const WindowProps &props) {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        KRISPY_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (!s_GLFWInitialized) {

            int success = glfwInit();
            KRISPY_CORE_ASSERT(success, "Could not initialize GLFW!");

            glfwSetErrorCallback(GLFWErrorCallback);

            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)props.Width, (int) props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);

        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        KRISPY_CORE_ASSERT(status, "Could not initialize GLAD!");

        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        // Set GLFW Callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
           WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

           WindowResizeEvent event(width, height);
           data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
           WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
           WindowCloseEvent event;
           data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
           WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

           switch (action) {
               case GLFW_PRESS: {
                   KeyPressedEvent event(key, false);
                   data.EventCallback(event);
                   break;
               }
               case GLFW_RELEASE: {
                   KeyReleasedEvent event(key);
                   data.EventCallback(event);
                   break;
               }
               case GLFW_REPEAT: {
                   KeyPressedEvent event(key, true);
                   data.EventCallback(event);
                   break;
               }
           }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double offsetX, double offsetY) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float) offsetX, (float) offsetY);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double posX, double posY) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float) posX, (float) posY);
            data.EventCallback(event);
        });

    }

    void LinuxWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void LinuxWindow::SetVSync(bool enable) {
        if (enable) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }

        m_Data.VSync = enable;
    }

    bool LinuxWindow::IsVSync() const {
        return m_Data.VSync;
    }

    void LinuxWindow::Shutdown() {
        glfwDestroyWindow(m_Window);
    }
}

