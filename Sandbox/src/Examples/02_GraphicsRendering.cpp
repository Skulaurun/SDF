/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <SDF/SDF.hpp>

std::unordered_map<std::string, std::shared_ptr<sdf::Texture>> textures = {};

int doExample02() {

    // Create the window
    sdf::Window window(L"Sandbox App", 800, 600);

    // Create camera with orthographic projection with the dimensions of the window
    std::shared_ptr<sdf::WindowCamera> camera = std::make_shared<sdf::WindowCamera>(window);

    // Set scene size that will try to fit into the window
    camera->setFitSize({ 800.0f, 600.0f });

    // Use custom callback for event handling
    window.setEventCallback([&](const sdf::WindowEvent& e) {

        // Subscribe camera to window resize event with "fit" resize mode
        // For expand mode use sdf::WindowCamera::onResizeExpand
        e.dispatch<sdf::WindowResizeEvent>(
            SDF_BIND_EVENT(sdf::WindowCamera::onResizeFit, camera.get())
        );

        // Invoke default behavior for certain events
        e.defaultDispatch();

    });

    // Load font texture from file
    textures["font"] = std::make_shared<sdf::Texture>(sdf::Image("res/font.png"));
    
    // Load animation texture from file
    textures["animation"] = std::make_shared<sdf::Texture>(sdf::Image("res/animation.png"));

    // Load sprite sheet from file
    textures["sprite-sheet"] = std::make_shared<sdf::Texture>(sdf::Image("res/sprite-sheet.png"));

    // Create font with character to sprite mapping
    // The characters are in the same order as in the texture
    std::shared_ptr<sdf::Font> font = std::make_shared<sdf::Font>(
        L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        L"1234567890!.,?:;'-\"[](){}+"
        L"_/\\# ",
        sdf::Vec2f(8.0f, 8.0f), // Character sprite size
        textures["font"]        // Bitmap font texture
    );

    // Create renderable text with font and set its properties (color, size, position)
    sdf::Text text1(L"SDF", font);
    text1.setFontColor(sdf::Color(255, 255, 255));
    text1.setFontSize(128.0f);
    text1.setPosition({ 208.0f, 128.0f });

    sdf::Text text2(L"SIMPLE DEDICATED FRAMEWORK", font);
    text2.setFontColor(sdf::Color(255, 255, 255));
    text2.setFontSize(16.0f);
    text2.setPosition({ 192.0f, 292.0f });

    // Create sprite from texture
    sdf::Sprite sprite1(textures["sprite-sheet"]);

    // Set region of the texture the sprite is in
    sprite1.setRegion({ 0.0f, 32.0f, 32.0f, 64.0f });

    // Set sprite position
    sprite1.getTransform().setPosition({ 368.0f, 32.0f });

    // Create animated sprite with frame size of 16.0f
    sdf::AnimatedSprite spriteAnimation(textures["animation"], { 16.0f });
    spriteAnimation.getTransform().setSize({ 128.0f });             // Set the sprite size
    spriteAnimation.getTransform().setPosition({ 336.0f, 324.0f }); // Set sprite position

    // Set-up the animation - [row index, animation name, fps, frame count]
    spriteAnimation.setAnimation(0, "main", 8.0f, 6);

    // Play the animation
    spriteAnimation.play("main");

    // Make the window visible
    window.show();

    // Initialize clock
    sdf::Clock clock;

    // Loop until the window is closed
    while (window.isOpen()) {

        // Calculate delta time, note that this is completely optional
        float deltaTime = (float)clock.collectElapsed().asMilliseconds();

        // Update sprite animation (calculate next frame)
        spriteAnimation.update(deltaTime);

        // Paint the background with gray color RGBA(52, 52, 52, 255)
        sdf::Renderer::clear(sdf::Color(0x343434ff));

        // Push the camera onto the renderer stack
        sdf::Renderer::beginCamera(camera);

        // Render black-white chess board
        for (std::size_t y = 0; y < 15; y++) {
            for (std::size_t x = 0; x < 20; x++) {
                float color = x % 2 == y % 2;
                sdf::Renderer::drawQuad(
                    sdf::Transform(
                        { x * 40.0f, y * 40.0f }, // Position [X;Y]
                        { 40.0f, 40.0f }          // Size [W;H]
                    ),
                    sdf::Color(color, color, color)
                );
            }
        }

        // Render black background for text2
        sdf::Renderer::drawQuad(
            sdf::Transform(
                { 208.0f, 128.0f },
                { 384.0f, 144.0f }
            ),
            sdf::Color(10, 10, 10)
        );

        // Render black background for text1
        sdf::Renderer::drawQuad(
            sdf::Transform(
                { 192.0f, 288.0f },
                { 416.0f, 24.0f }
            ),
            sdf::Color(10, 10, 10)
        );

        // Render black background for spriteAnimation
        sdf::Renderer::drawQuad(
            sdf::Transform(
                { 336.0f, 324.0f },
                { 128.0f, 128.0f }
            ),
            sdf::Color(10, 10, 10)
        );

        // Render text elements
        sdf::Renderer::drawText(text1);
        sdf::Renderer::drawText(text2);

        // Draw sprite
        sdf::Renderer::drawSprite(sprite1);

        // Draw sprite animation
        sdf::Renderer::drawSprite(spriteAnimation);

        // Send the data to GPU
        sdf::Renderer::flush();

        // Pop the camera from the stack
        sdf::Renderer::endCamera();

        // Swap window buffers
        window.display();

        // Process user input and call event callbacks
        window.pollEvents();

    }

    return 0;

}
