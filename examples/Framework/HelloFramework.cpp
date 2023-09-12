#include <ogrid.h>

int main()
{
    OGRID::Log::Init();

    CLI_TRACE("Hello Framework!");
    CLI_INFO("Hello Framework!");
    CLI_WARN("Hello Framework!");
    CLI_ERROR("Hello Framework!");
    CLI_FATAL("Hello Framework!");

    DEBUG_TRACE("Hello Framework!");
    DEBUG_INFO("Hello Framework!");
    DEBUG_WARN("Hello Framework!");
    DEBUG_ERROR("Hello Framework!");
    DEBUG_FATAL("Hello Framework!");

    return 0;
}