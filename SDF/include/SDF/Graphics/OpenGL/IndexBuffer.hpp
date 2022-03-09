/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include "Buffer.hpp"

#include <cstdint>

namespace sdf {

	using IndexBufferTemplate = Buffer<uint32_t, BufferType::IndexBuffer>;

	class IndexBuffer : public IndexBufferTemplate {

	public:
		using IndexBufferTemplate::Buffer;

	};

}
