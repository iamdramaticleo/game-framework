#include "window_instance.hpp"
#include "platform_instance.hpp"

#include "opengl/context.hpp"
#include "opengl/commands.hpp"
#include "opengl/pipeline.hpp"
#include "opengl/vertex_array.hpp"
#include "opengl/buffer.hpp"
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

    const std::vector vertices
    {
        -0.5f, -0.5f, 0.0f, // TODO change with vec3
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    gl::VertexArray vertex_array;
    vertex_array.create();
    vertex_array.bind();

    gl::Buffer vertices_buffer;
    vertices_buffer.create();
    vertices_buffer.bind(gl::ARRAY_BUFFER);
    vertices_buffer.data(base::buffer_data::create_from_buffer(vertices), gl::STATIC_DRAW);

    vertex_array.attribute({ 0, 3, gl::FLOAT, 0 }, 0);

    gl::Pipeline::enable(gl::DEPTH_TEST);

    while (window.is_active())
    {
        gl::Commands::clear(0.5f, 0.5f, 0.5f);
        gl::Commands::clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

        vertex_array.bind();
        gl::Commands::draw_arrays(gl::TRIANGLES, 3); // TODO use vertices size

        window.update();
        platform.update();
    }

    vertices_buffer.destroy();
    vertex_array.destroy();

    window.destroy();
    platform.release();

    return EXIT_SUCCESS;
}
