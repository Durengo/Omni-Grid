#include <ogrid.h>
#include <durlib.h>

int main()
{
    DURLIB::Log::Init();

    CLI_INFO("Welcome to Omni Grid Sandbox!");

    OGRID::Grid grid(10, 10);

    CLI_TRACE("Grid new grid: {0}", grid.GetGridInfo());

    return 0;
}