//
// Created by dallin on 8/12/20.
//

#pragma once

#include "Krispy/Events/Event.h"

namespace Krispy {

#pragma mark --Window Events--
    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() {}
        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(float width, float height): m_Width(width), m_Height(height) {}

        inline float GetWidth() const { return m_Width; }
        inline float GetHeight() const { return m_Height; }
        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    private:
        float m_Width, m_Height;
    };

    class WindowMoveEvent : public Event {
    public:
        WindowMoveEvent(float posX, float posY): m_PosX(posX), m_PosY(posY) {}

        inline float GetPositionX() const { return m_PosX; }
        inline float GetPositionY() const { return m_PosY; }
        EVENT_CLASS_TYPE(WindowMove)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    private:
        float m_PosX, m_PosY;
    };

    class WindowFocusEvent : public Event {
    public:
        WindowFocusEvent() {}
        EVENT_CLASS_TYPE(WindowFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class WindowBlurEvent : public Event {
    public:
        WindowBlurEvent() {}
        EVENT_CLASS_TYPE(WindowBlur)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

#pragma mark ~
#pragma mark --App Cycle Events--
    class AppTickEvent : public Event {
    public:
        AppTickEvent() {}
        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() {}
        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppRenderEvent : public Event {
    public:
        AppRenderEvent() {}
        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
#pragma mark ~
}


