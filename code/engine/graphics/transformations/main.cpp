#include <window_instance.hpp>
#include <platform_module.hpp>

#include <opengl/pipeline.hpp>
#include <opengl/commands.hpp>
#include <opengl/vertex_array.hpp>
#include <opengl/buffer.hpp>
#include <opengl/functions.hpp>
#include <opengl/macros.hpp>
#include <opengl/shader.hpp>

#include <geometry.hpp>
#include <file.hpp>
#include <time.hpp>

#include <vec3.hpp>
#include <rgb.hpp>

int32_t main()
{
    auto& window = core::WindowInstance::instance();
     window.create(core::PlatformModule::create_factory(), { "transformations", 1024, 768 });

    core::gl::Functions::load();

    const auto vert_stage_data = core::File::read("diffuse_vert.spv", std::ios::binary);
    const auto frag_stage_data = core::File::read("diffuse_frag.spv", std::ios::binary);

    core::gl::ShaderStage vert_stage { core::gl::vertex_shader };
    vert_stage.create();
    vert_stage.source(vert_stage_data);

    core::gl::ShaderStage frag_stage { core::gl::fragment_shader };
    frag_stage.create();
    frag_stage.source(frag_stage_data);

    core::gl::Shader shader;
    shader.create();
    shader.attach(vert_stage);
    shader.attach(frag_stage);
    shader.link();

    vert_stage.destroy();
    frag_stage.destroy();

    auto [vertices, indices] = core::Geometry::create_plane();

    core::gl::VertexArray vertex_array;
    vertex_array.create();
    vertex_array.bind();

    core::gl::Buffer vertices_buffer;
    vertices_buffer.create();
    vertices_buffer.bind(core::gl::array_buffer);
    vertices_buffer.data(core::base::buffer_data::create_from_buffer(vertices), core::gl::static_draw);

    core::gl::Buffer indices_buffer;
    indices_buffer.create();
    indices_buffer.bind(core::gl::element_array_buffer);
    indices_buffer.data(core::base::buffer_data::create_from_buffer(indices), core::gl::static_draw);

    vertex_array.attribute({ 0, 3, core::gl::type_float, 0 }, sizeof(core::vec3));

    core::gl::Pipeline::enable(core::gl::depth_test);
    core::gl::Pipeline::enable(core::gl::multisample);

    const std::vector camera_matrices
    {
        glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, -3.0f }),
        glm::perspective(glm::radians(45.0f), static_cast<float>(window.width()) /
                                                               static_cast<float>(window.height()), 0.1f, 100.0f)
    };

    core::gl::Buffer camera_ubo;
    camera_ubo.create();
    camera_ubo.bind(core::base::buffer_location::camera);
    camera_ubo.data(core::base::buffer_data::create_from_buffer(camera_matrices), core::gl::static_draw);

    constexpr core::rgb color { 0.2, 0.2, 0.9 };

    core::gl::Buffer material_ubo;
    material_ubo.create();
    material_ubo.bind(core::base::buffer_location::material);
    material_ubo.data(core::base::buffer_data::create_from_data(&color), core::gl::static_draw);

    core::Time time;
    time.init();

    while (window.is_active())
    {
        core::gl::Commands::clear(0.5f, 0.5f, 0.5f);
        core::gl::Commands::clear(core::gl::color_buffer_bit | core::gl::depth_buffer_bit);

        shader.bind();

        glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(core::Time::total_time() * 50.0f), { 0.0f, 0.0f, 1.0f });
                  model = glm::scale(model, { 0.5f, 0.5f, 0.5f });

        shader.push(0, glm::value_ptr(model));

        vertex_array.bind();
        core::gl::Commands::draw_elements(core::gl::triangles, indices.size());

        time.update();
        window.update();
    }

    indices_buffer.destroy();
    vertices_buffer.destroy();
    vertex_array.destroy();

    camera_ubo.destroy();
    material_ubo.destroy();

    shader.destroy();

    window.destroy();
    return 0;
}