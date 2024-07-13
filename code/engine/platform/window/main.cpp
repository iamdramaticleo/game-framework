#include <window_instance.hpp>
#include <platform_module.hpp>

#include <opengl/pipeline.hpp>
#include <opengl/commands.hpp>
#include <opengl/functions.hpp>
#include <opengl/macros.hpp>

int32_t main()
{
    auto& window = WindowInstance::instance();
          window.create(PlatformModule::create_factory(), { "window", 1024, 768 });

    gl::Functions::load();

    gl::Pipeline::enable(gl::DEPTH_TEST);
    gl::Pipeline::enable(gl::MULTISAMPLE);

    while (window.is_active())
    {
        gl::Commands::clear(0.5f, 0.5f, 0.5f);
        gl::Commands::clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

        window.update();
    }

    window.destroy();
    return 0;
}
