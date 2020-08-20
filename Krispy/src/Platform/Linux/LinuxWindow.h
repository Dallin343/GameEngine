//
// Created by dallin on 8/12/20.
//

#pragma once

#include "Krispy/Core/Window.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Krispy/Renderer/GraphicsContext.h"

namespace Krispy {
    class LinuxWindow: public Window {
    public:
        LinuxWindow(const WindowProps& props);
        virtual ~LinuxWindow();

        void OnUpdate() override;

        unsigned int GetWidth() const override { return m_Data.Width; }
        unsigned int GetHeight() const override { return m_Data.Height; }

        void* GetNativeWindow() const override { return m_Window; };

        // Attributes
        inline void SetEventCallback(const EventCallbackFn &callback) override {m_Data.EventCallback = callback; };
        void SetVSync(bool enable) override;
        bool IsVSync() const override;

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

    private:
        GLFWwindow* m_Window;
        struct WindowData {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;

        GraphicsContext* m_Context;
    };
}