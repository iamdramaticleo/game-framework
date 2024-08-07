#include <window_instance.hpp>
#include <platform_module.hpp>

#include <opengl/pipeline.hpp>
#include <opengl/commands.hpp>
#include <opengl/functions.hpp>
#include <opengl/macros.hpp>

int32_t main()
{
    auto& window = core::WindowInstance::instance();
    window.create(core::PlatformModule::create_factory(), { "window", 1024, 768 });

    core::gl::Functions::load();

    core::gl::Pipeline::enable(core::gl::depth_test);
    core::gl::Pipeline::enable(core::gl::multisample);

    while (window.is_active())
    {
        core::gl::Commands::clear(0.5f, 0.5f, 0.5f);
        core::gl::Commands::clear(core::gl::color_buffer_bit | core::gl::depth_buffer_bit);

        window.update();
    }

    window.destroy();
    return 0;
}
