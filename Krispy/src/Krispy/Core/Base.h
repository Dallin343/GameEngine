#pragma once
#include <memory>

#pragma mark --Debug--

#ifdef KRISPY_DEBUG
    #if defined(KRISPY_PLATFORM_LINUX)
        #include <signal.h>
        #define KRISPY_DEBUGBREAK() raise(SIGTRAP)
    #elif defined(KRISPY_PLATFORM_UNKNOWN)
    #endif
    #define KRISPY_ENABLE_ASSERTS 1
#else
    #define KRISPY_DEBUGBREAK()
#endif

#pragma mark --Platform Specific--
#ifdef KRISPY_ENABLE_ASSERTS
    #define KRISPY_ASSERT(x, ...) { if(!(x)) { KRISPY_ERROR("Assertion Failed: {0}", __VA_ARGS__); KRISPY_DEBUGBREAK(); } }
    #define KRISPY_CORE_ASSERT(x, ...) { if(!(x)) { KRISPY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); KRISPY_DEBUGBREAK(); } }
#else
    #define KRISPY_ASSERT(x, ...)
    #define KRISPY_CORE_ASSERT(x, ...)
#endif


#pragma mark --Macros--
#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) {return this->fn(std::forward<decltype(args)>(args)...); }

#pragma mark --Value Defines--

//Used to make it clear whether an event handler reports that the event was handled or not.
#define KRISPY_EVENT_HANDLED true
#define KRISPY_EVENT_NOT_HANDLED false

#pragma mark --Scope and Ref--

namespace Krispy {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;
}