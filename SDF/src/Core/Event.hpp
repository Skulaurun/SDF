#pragma once

#include <cstdint>
#include <functional>

namespace sdf {

    class Event {

    public:
        virtual ~Event() = default;

        virtual const std::type_info& getType() const = 0;

        template<typename T> void dispatch(const std::function<void(const T&)>& callback) const {
            static_assert(std::is_base_of<Event, T>::value);
            if (this->is<T>()) {
                callback(static_cast<const T&>(*this));
            }
        }

        template<typename T> bool is() const {
            return getType() == typeid(T);
        }

        virtual void defaultDispatch() const {}

    };

}
