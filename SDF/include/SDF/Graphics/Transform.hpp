#pragma once

#include "Matrix.hpp"

namespace sdf {

    class Transform {

    public:
        Transform();
        Transform(const sdf::Vec2f& position, const sdf::Vec2f& size, const float rotation = 0.0f);

        void setPosition(const sdf::Vec2f& position) { this->position = position; updateMatrix(); }
        void setSize(const sdf::Vec2f& size) { this->size = size; updateMatrix(); }
        void setRotation(const float rotation) { this->rotation = rotation; updateMatrix(); }

        Transform& translate(const sdf::Vec2f& offset);
        Transform& scale(const sdf::Vec2f& scale);
        Transform& rotate(const float angle);

        void updateMatrix();

        sdf::Vec2f getPosition() const { return position; }
        sdf::Vec2f getSize() const { return size; }
        sdf::Vec2f getRotation() const { return rotation; }

        const sdf::Mat4f& getMatrix() const { return matrix; }

    private:
        sdf::Vec2f position;
        sdf::Vec2f size;
        float rotation;

        sdf::Mat4f matrix;

    };

}
