#pragma once

#pragma mark --Debug Macros--
#ifdef KRISPY_DEBUG
    #if defined(KRISPY_SYS_LINUX)
        #include <signal.h>
        #define KRISPY_DEBUGBREAK() raise(SIGTRAP)
    #elif defined(KRISPY_SYS_UNKNOWN)
    #endif
    #define KRISPY_ENABLE_ASSERTS
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