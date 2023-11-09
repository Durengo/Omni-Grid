#pragma once

#include "Core/_CORE.h"
#include "spdlog/spdlog.h"

namespace OGRID
{
    class Log
    {
    public:
        static void Init();

        inline static REF<spdlog::logger> &GetClientLogger() { return ClientLogger; }
        inline static REF<spdlog::logger> &GetDebugLogger() { return DebugLogger; }

    private:
        static REF<spdlog::logger> ClientLogger;
        static REF<spdlog::logger> DebugLogger;
    };
}

// CLIENT SIDE LOGS
#define CLI_ERROR(...) ::OGRID::Log::GetClientLogger()->error(__VA_ARGS__)
#define CLI_WARN(...) ::OGRID::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLI_INFO(...) ::OGRID::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLI_TRACE(...) ::OGRID::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CLI_FATAL(...) ::OGRID::Log::GetClientLogger()->critical(__VA_ARGS__)
#define CLI_BUG(...) ::OGRID::Log::GetClientLogger()->debug(__VA_ARGS__)
// DEBUG/COMPILATION LOGGER
#ifdef OGRID_ENABLE_DEBUG_LOG
    #define DEBUG_ERROR(...) ::OGRID::Log::GetDebugLogger()->error(__VA_ARGS__)
    #define DEBUG_WARN(...) ::OGRID::Log::GetDebugLogger()->warn(__VA_ARGS__)
    #define DEBUG_INFO(...) ::OGRID::Log::GetDebugLogger()->info(__VA_ARGS__)
    #define DEBUG_TRACE(...) ::OGRID::Log::GetDebugLogger()->trace(__VA_ARGS__)
    #define DEBUG_FATAL(...) ::OGRID::Log::GetDebugLogger()->critical(__VA_ARGS__)
    #define DEBUG_BUG(...) ::OGRID::Log::GetDebugLogger()->debug(__VA_ARGS__)
#else
    #define DEBUG_ERROR(...)
    #define DEBUG_WARN(...)
    #define DEBUG_INFO(...)
    #define DEBUG_TRACE(...)
    #define DEBUG_FATAL(...)
    #define DEBUG_BUG(...)
#endif