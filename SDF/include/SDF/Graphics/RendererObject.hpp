/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include <cstdint>

namespace sdf {

	class RendererObject {

	public:
		RendererObject() : id(0) {}
		RendererObject(uint32_t id) : id(id) {}

		virtual ~RendererObject() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		bool operator==(const RendererObject& other) { return id == other.id; }

	protected:
		uint32_t id;

	};

}
