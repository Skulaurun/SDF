#pragma once

#include "../Core/Window.hpp"
#include "Camera.hpp"

namespace sdf {

    class WindowCamera : public Camera {

    public:
        WindowCamera(const Window& window);

        void onResizeFit(const WindowResizeEvent& e);
        void onResizeExpand(const WindowResizeEvent& e);

        void setFitSize(const sdf::Vec2f& size) { fitSize = size; }

    private:
        Vec2f fitSize;

    };

}
