/*
*   SDF - Simple Dedicated Framework
*   Version: 2.0.0
*   <https://github.com/Skulaurun/SDF>
*   
*   Licensed under the MIT License <https://opensource.org/licenses/MIT>.
*   SPDX-License-Identifier: MIT
*   Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>.
*   
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*   
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*   
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*/

#pragma once

#define SDF_VERSION_MAJOR 2
#define SDF_VERSION_MINOR 0
#define SDF_VERSION_PATCH 0

/* Core Module */

#include "Core/Exception.hpp"

#include "Core/Clock.hpp"
#include "Core/Input.hpp"
#include "Core/Window.hpp"

/* Graphics Module */

#include "Graphics/Vector.hpp"
#include "Graphics/Matrix.hpp"
#include "Graphics/Math.hpp"
#include "Graphics/Color.hpp"

#include "Graphics/OpenGL/Buffer.hpp"
#include "Graphics/OpenGL/VertexBuffer.hpp"
#include "Graphics/OpenGL/IndexBuffer.hpp"

#include "Graphics/OpenGL/VertexArray.hpp"

#include "Graphics/OpenGL/Shader.hpp"
#include "Graphics/OpenGL/Texture.hpp"

#include "Graphics/Sprite.hpp"
#include "Graphics/AnimatedSprite.hpp"
#include "Graphics/Text.hpp"

#include "Graphics/Camera.hpp"
#include "Graphics/WindowCamera.hpp"
#include "Graphics/Transform.hpp"
#include "Graphics/Renderer.hpp"

/* Network Module */

#include "Network/Network.hpp"

#include "Network/AddressInfo.hpp"
#include "Network/Socket.hpp"

#include "Network/ByteStream.hpp"
