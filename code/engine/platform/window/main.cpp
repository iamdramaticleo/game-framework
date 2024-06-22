#include "glfw/platform.hpp"

int32_t main()
{
    glfw::Platform platform;

    platform.init();
    platform.update();
    platform.release();

    return 0;
}