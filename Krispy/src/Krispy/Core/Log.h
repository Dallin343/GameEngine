//
// Created by dallin on 8/12/20.
//

#pragma once

#include <spdlog/spdlog.h>

namespace Krispy {
    class Log {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}


#pragma mark --Logging Functions--
#define KRISPY_CORE_TRACE(...) ::Krispy::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KRISPY_CORE_INFO(...) ::Krispy::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KRISPY_CORE_WARN(...) ::Krispy::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KRISPY_CORE_ERROR(...) ::Krispy::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KRISPY_CORE_FATAL(...) ::Krispy::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define KRISPY_TRACE(...) ::Krispy::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KRISPY_INFO(...) ::Krispy::Log::GetClientLogger()->info(__VA_ARGS__)
#define KRISPY_WARN(...) ::Krispy::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KRISPY_ERROR(...) ::Krispy::Log::GetClientLogger()->error(__VA_ARGS__)
#define KRISPY_FATAL(...) ::Krispy::Log::GetClientLogger()->fatal(__VA_ARGS__)


