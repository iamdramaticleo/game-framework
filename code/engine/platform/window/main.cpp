#include <window_instance.hpp>
#include <platform_module.hpp>

#include <opengl/pipeline.hpp>
#include <opengl/commands.hpp>
#include <opengl/functions.hpp>
#include <opengl/macros.hpp>

int32_t main()
{
    auto& window =      core::WindowInstance::instance();
          window.create(core::PlatformModule::create_factory(), { "window", 1024, 768 });

    gl::Functions::load();

    gl::Pipeline::enable(gl::depth_test);
    gl::Pipeline::enable(gl::multisample);

    while (window.is_active())
    {
        gl::Commands::clear(0.5f, 0.5f, 0.5f);
        gl::Commands::clear(gl::color_buffer_bit | gl::depth_buffer_bit);

        window.update();
    }

    window.destroy();
    return 0;
}
