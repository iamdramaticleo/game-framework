#include "window_instance.hpp"
#include "platform_instance.hpp"

#include "opengl/context.hpp"
#include "opengl/commands.hpp"
#include "opengl/pipeline.hpp"
#include "opengl/macros.hpp"

int main()
{
    auto& platform = core::PlatformInstance::instance();
    auto& window   = core::WindowInstance::instance();

    const base::window_config config { "vertex buffer", { 1024, 768 } };
    const auto factory = core::PlatformFactory::create_factory();

    platform.init(factory);
    window.create(factory, config);

    gl::Context::load();

    gl::Pipeline::enable(gl::DEPTH_TEST);

    while (window.is_active())
    {
        gl::Commands::clear(0.5f, 0.5f, 0.5f);
        gl::Commands::clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

        window.update();
        platform.update();
    }

    window.destroy();
    platform.release();

    return EXIT_SUCCESS;
}
