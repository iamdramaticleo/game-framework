#include <window_instance.hpp>
#include <platform_module.hpp>

#include <opengl/pipeline.hpp>
#include <opengl/commands.hpp>
#include <opengl/functions.hpp>
#include <opengl/macros.hpp>

#include <gainput/gainput.h>
#include <windows.h>

enum input_actions
{
    close
};

int32_t main()
{
    auto& window = core::WindowInstance::instance();
     window.create(core::PlatformModule::create_factory(), { "input", 1024, 768 });

    core::gl::Functions::load();

    core::gl::Pipeline::enable(core::gl::depth_test);
    core::gl::Pipeline::enable(core::gl::multisample);

    gainput::InputManager input_manager;
    input_manager.SetDisplaySize(window.width(), window.height());

    const gainput::DeviceId keyboard_id = input_manager.CreateDevice<gainput::InputDeviceKeyboard>();

    gainput::InputMap input_map(input_manager);
    input_map.MapBool(close, keyboard_id, gainput::KeyEscape);
    input_map.MapBool(close, keyboard_id, gainput::KeySpace);

    while (window.is_active())
    {
        core::gl::Commands::clear(0.5f, 0.5f, 0.5f);
        core::gl::Commands::clear(core::gl::color_buffer_bit | core::gl::depth_buffer_bit);

        input_manager.Update();

        MSG msg;
        const HWND hwnd = std::any_cast<HWND>(window.handle());

        while (PeekMessage(&msg, hwnd,  0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                window.close();
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                input_manager.HandleMessage(msg);
            }
        }

        if (input_map.GetBoolWasDown(close))
        {
            window.close();
        }

        window.update();
    }

    window.destroy();
    return 0;
}
