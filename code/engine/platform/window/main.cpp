#include "window_instance.hpp"
#include "platform_instance.hpp"

int main()
{
    auto& platform = core::PlatformInstance::instance();
    auto& window   = core::WindowInstance::instance();

    const base::window_config config { "window", { 1024, 768 } };
    const auto factory = core::PlatformFactory::create_factory();

    platform.init(factory);
    window.create(factory, config);

    while (window.is_active())
    {
        window.update();
        platform.update();
    }

    window.destroy();
    platform.release();

    return EXIT_SUCCESS;
}