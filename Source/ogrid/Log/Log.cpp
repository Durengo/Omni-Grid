#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace OGRID
{
    REF<spdlog::logger> Log::ClientLogger;
    REF<spdlog::logger> Log::DebugLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        ClientLogger = spdlog::stdout_color_mt("CLI");
        ClientLogger->set_level(spdlog::level::trace);

        DebugLogger = spdlog::stdout_color_mt("DEBUG");
        DebugLogger->set_level(spdlog::level::trace);

        CLI_WARN("CLIENT LOG INITIALIZED.");
        DEBUG_WARN("DEBUG LOG INITIALIZED.");
    }
}