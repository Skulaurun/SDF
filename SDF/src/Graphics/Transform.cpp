#include <PCH.hpp>
#include <SDF/Graphics/Transform.hpp>
#include <SDF/Graphics/Math.hpp>

namespace sdf {

    Transform::Transform(const sdf::Vec2f& position, const sdf::Vec2f& size, const float rotation)
        : position(position), size(size), rotation(rotation), matrix(1.0f) {
        updateMatrix();
    }

    Transform::Transform() : Transform({ 0.0f }, { 0.0f }) {}

    Transform& Transform::translate(const sdf::Vec2f& offset) {
        setPosition(position + offset);
        updateMatrix();
        return *this;
    }

    Transform& Transform::scale(const sdf::Vec2f& scale) {
        setSize(size + scale);
        updateMatrix();
        return *this;
    }

    Transform& Transform::rotate(const float angle) {
        setRotation(rotation + angle);
        updateMatrix();
        return *this;
    }

    void Transform::updateMatrix() {
        matrix = sdf::Mat4f(1.0f)
            * sdf::translate(sdf::Vec3f(position.x, position.y, 0.0f))
            * sdf::scale(sdf::Vec3f(size.x, size.y, 0.0f))
            * sdf::rotate(rotation, sdf::Vec3f(0.0f, 0.0f, 1.0f));
    }

}
