#include "window_instance.hpp"
#include "platform_instance.hpp"

#include "opengl/context.hpp"
#include "opengl/commands.hpp"
#include "opengl/pipeline.hpp"
#include "opengl/vertex_array.hpp"
#include "opengl/buffer.hpp"
#include "opengl/shader.hpp"
#include "opengl/macros.hpp"

#include "math/vec3.hpp"

#include "file.hpp"

int main()
{
    auto& platform = core::PlatformInstance::instance();
    auto& window   = core::WindowInstance::instance();

    const base::window_config config { "shaders", { 1024, 768 } };
    const auto factory = core::PlatformFactory::create_factory();

    platform.init(factory);
    window.create(factory, config);

    gl::Context::load();

    const auto vert_stage_data = core::File::read("diffuse_vert.spv", std::ios::binary);
    const auto frag_stage_data = core::File::read("diffuse_frag.spv", std::ios::binary);

    gl::ShaderStage vert_stage { gl::VERTEX_SHADER };
    vert_stage.create();
    vert_stage.source(vert_stage_data);

    gl::ShaderStage frag_stage { gl::FRAGMENT_SHADER };
    frag_stage.create();
    frag_stage.source(frag_stage_data);

    gl::Shader shader;
    shader.create();
    shader.attach(vert_stage);
    shader.attach(frag_stage);
    shader.link();

    vert_stage.destroy();
    frag_stage.destroy();

    const std::vector<math::vec3> vertices
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
    vertices_buffer.bind(gl::ARRAY_BUFFER);
    vertices_buffer.data(base::buffer_data::create_from_buffer(vertices), gl::STATIC_DRAW);

    vertex_array.attribute({ 0, 3, gl::FLOAT, 0 }, sizeof(math::vec3));

    gl::Pipeline::enable(gl::DEPTH_TEST);

    while (window.is_active())
    {
        gl::Commands::clear(0.5f, 0.5f, 0.5f);
        gl::Commands::clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

        shader.bind();

        vertex_array.bind();
        gl::Commands::draw_arrays(gl::TRIANGLES, vertices.size());

        window.update();
        platform.update();
    }

    vertices_buffer.destroy();
    vertex_array.destroy();

    shader.destroy();

    window.destroy();
    platform.release();

    return EXIT_SUCCESS;
}
