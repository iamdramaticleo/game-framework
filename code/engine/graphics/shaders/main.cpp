#include <window_instance.hpp>
#include <platform_module.hpp>

#include <opengl/pipeline.hpp>
#include <opengl/commands.hpp>
#include <opengl/vertex_array.hpp>
#include <opengl/buffer.hpp>
#include <opengl/functions.hpp>
#include <opengl/macros.hpp>
#include <opengl/shader.hpp>

#include <math/vec3.hpp>
#include <math/rgb.hpp>

#include <file.hpp>

#include <geometry.hpp>

int32_t main()
{
    auto& window = core::WindowInstance::instance();
    window.create(core::PlatformModule::create_factory(), { "shaders", 1024, 768 });

    core::gl::Functions::load();

    core::gl::Pipeline::enable(core::gl::depth_test);
    core::gl::Pipeline::enable(core::gl::multisample);

    const auto vert_stage_data = core::File::read("diffuse_vert.spv", std::ios::binary);
    const auto frag_stage_data = core::File::read("diffuse_frag.spv", std::ios::binary);

    core::gl::Stage vert_stage { core::gl::vertex_shader };
    vert_stage.create();
    vert_stage.source(vert_stage_data);

    core::gl::Stage frag_stage { core::gl::fragment_shader };
    frag_stage.create();
    frag_stage.source(frag_stage_data);

    core::gl::Shader shader;
    shader.create();
    shader.attach(vert_stage);
    shader.attach(frag_stage);
    shader.link();

    vert_stage.destroy();
    frag_stage.destroy();

    auto [vertices, indices] = core::tools::Geometry::create_plane();

    core::gl::VertexArray vertex_array;
    vertex_array.create();
    vertex_array.bind();

    core::gl::Buffer vertices_buffer;
    vertices_buffer.create();
    vertices_buffer.bind(core::gl::array_buffer);
    vertices_buffer.data(core::base::buffer_data::create_from(vertices), core::gl::static_draw);

    core::gl::Buffer indices_buffer;
    indices_buffer.create();
    indices_buffer.bind(core::gl::element_array_buffer);
    indices_buffer.data(core::base::buffer_data::create_from(indices), core::gl::static_draw);

    vertex_array.attribute({ 0, 3, core::gl::type_float, 0 }, sizeof(core::math::vec3));

    constexpr core::math::rgb color { 0.8, 0.4, 0.2 };

    while (window.is_active())
    {
        core::gl::Commands::clear(0.5f, 0.5f, 0.5f);
        core::gl::Commands::clear(core::gl::color_buffer_bit | core::gl::depth_buffer_bit);

        shader.bind();
        shader.push(0, color);

        vertex_array.bind();
        core::gl::Commands::draw_elements(core::gl::triangles, indices.size());

        window.update();
    }

    indices_buffer.destroy();
    vertices_buffer.destroy();
    vertex_array.destroy();

    shader.destroy();

    window.destroy();
    return 0;
}