#include <window_instance.hpp>
#include <platform_module.hpp>

#include <opengl/pipeline.hpp>
#include <opengl/commands.hpp>
#include <opengl/vertex_array.hpp>
#include <opengl/buffer.hpp>
#include <opengl/functions.hpp>
#include <opengl/macros.hpp>

#include <vec3.hpp>

int32_t main()
{
    auto& window =      core::WindowInstance::instance();
          window.create(core::PlatformModule::create_factory(), { "vertex buffer", 1024, 768 });

    gl::Functions::load();

    const std::vector<core::vec3> vertices
    {
        { -0.5f, -0.5f, 0.0f },
        {  0.5f, -0.5f, 0.0f },
        {  0.0f,  0.5f, 0.0f }
    };

    gl::VertexArray vertex_array;
    vertex_array.create();
    vertex_array.bind();

    gl::Buffer vertices_buffer;
    vertices_buffer.create();
    vertices_buffer.bind(gl::array_buffer);
    vertices_buffer.data(base::buffer_data::create_from_buffer(vertices), gl::static_draw);

    vertex_array.attribute({ 0, 3, gl::type_float, 0 }, sizeof(core::vec3));

    gl::Pipeline::enable(gl::depth_test);
    gl::Pipeline::enable(gl::multisample);

    while (window.is_active())
    {
        gl::Commands::clear(0.5f, 0.5f, 0.5f);
        gl::Commands::clear(gl::color_buffer_bit | gl::depth_buffer_bit);

        vertex_array.bind();
        gl::Commands::draw_arrays(gl::triangles, vertices.size());

        window.update();
    }

    vertices_buffer.destroy();
    vertex_array.destroy();

    window.destroy();
    return 0;
}