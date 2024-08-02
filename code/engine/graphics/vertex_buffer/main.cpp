#include <window_instance.hpp>
#include <platform_module.hpp>

#include <opengl/pipeline.hpp>
#include <opengl/commands.hpp>
#include <opengl/vertex_array.hpp>
#include <opengl/buffer.hpp>
#include <opengl/functions.hpp>
#include <opengl/macros.hpp>

#include <math/vec3.hpp>

int32_t main()
{
    auto& window = core::WindowInstance::instance();
    window.create(core::PlatformModule::create_factory(), { "vertex buffer", 1024, 768 });

    core::gl::Functions::load();

    core::gl::Pipeline::enable(core::gl::depth_test);
    core::gl::Pipeline::enable(core::gl::multisample);

    const std::vector<core::math::vec3> vertices
    {
        { -0.5f, -0.5f, 0.0f },
        {  0.5f, -0.5f, 0.0f },
        {  0.0f,  0.5f, 0.0f }
    };

    core::gl::VertexArray vertex_array;
    vertex_array.create();
    vertex_array.bind();

    core::gl::Buffer vertices_buffer;
    vertices_buffer.create();
    vertices_buffer.bind(core::gl::array_buffer);
    vertices_buffer.data(core::base::buffer_data::create_from(vertices), core::gl::static_draw);

    vertex_array.attribute({ 0, 3, core::gl::type_float, 0 }, sizeof(core::math::vec3));

    while (window.is_active())
    {
        core::gl::Commands::clear(0.5f, 0.5f, 0.5f);
        core::gl::Commands::clear(core::gl::color_buffer_bit | core::gl::depth_buffer_bit);

        vertex_array.bind();
        core::gl::Commands::draw_arrays(core::gl::triangles, vertices.size());

        window.update();
    }

    vertices_buffer.destroy();
    vertex_array.destroy();

    window.destroy();
    return 0;
}