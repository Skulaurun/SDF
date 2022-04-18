#include <PCH.hpp>
#include <SDF/Graphics/WindowCamera.hpp>
#include <SDF/Graphics/Renderer.hpp>

namespace sdf {

    WindowCamera::WindowCamera(const Window& window)
        : Camera(0, (float)window.getWidth(), (float)window.getHeight(), 0) {}

    void WindowCamera::onResizeFit(const WindowResizeEvent& e) {

        const Window& window = e.getWindow();

        float width = (float)window.getWidth();
        float height = (float)window.getHeight();

        sdf::Renderer::setViewport(0, { (uint32_t)width, (uint32_t)height });
            
        float newWidth = 0.0f;
        float newHeight = 0.0f;

        if (width - ((fitSize.x - fitSize.y) * width / fitSize.x) >= height) {
            newHeight = fitSize.y;
            newWidth = width * (fitSize.y / height);
        } else {
            newWidth = fitSize.x;
            newHeight = height * (fitSize.x / width);
        }

        setProjection(
            0.0f,
            newWidth,
            newHeight,
            0.0f
        );

        setPosition({
            (newWidth / 2.0f) - (fitSize.x / 2.0f),
            (newHeight / 2.0f) - (fitSize.y / 2.0f)
        });

    }

    void WindowCamera::onResizeExpand(const WindowResizeEvent& e) {

        const Window& window = e.getWindow();

        sdf::Renderer::setViewport(0, { window.getWidth(), window.getHeight() });
        setProjection(0, (float)window.getWidth(), (float)window.getHeight(), 0);

    }

}
