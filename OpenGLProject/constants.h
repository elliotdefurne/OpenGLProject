#pragma once

namespace Constants {
    // Window
    constexpr int WINDOW_WIDTH = 1280;
    constexpr int WINDOW_HEIGHT = 720;
    constexpr const char* WINDOW_TITLE = "Mon jeu OpenGL";
    constexpr bool IS_WINDOW_FULLSCREEN = false;

    // Renderer
    constexpr int DEFAULT_FPS_CAPPING = 60;
    constexpr bool DEFAULT_IS_FPS_CAPPING = false;

    // Player

	constexpr float PLAYER_SPEED = 2.5f; // pixels per second

    // Texture

	constexpr const char* TEXTURES_FOLDER_PATH = "./res/textures/";

    // Shader

    constexpr const char* SHADERS_FOLDER_PATH = "./res/shaders/";
    
    // Files
    
    constexpr const char PREFERED_SEPARATOR_PATH = '/';

    // Lights Shadering

    constexpr const int MAX_LIGHTS_SOURCES = 10;

    // Networking

    constexpr const int MAX_PACKET_SIZE = 1024;
    constexpr const char* SERVER_IP = "127.0.0.1";
    constexpr const int SERVER_PORT = 3333;
}

namespace Materials {
    // Shininess values for different materials in OpenGL
    // Range: 0.0 (matte) to 128.0 (very shiny)

    // Matte materials
    constexpr const float RUBBER = 10.0f;
    constexpr const float CLAY = 8.0f;
    constexpr const float CONCRETE = 5.0f;

    // Semi-matte materials
    constexpr const float WOOD = 15.0f;
    constexpr const float PLASTIC_MATTE = 20.0f;
    constexpr const float STONE = 12.0f;

    // Semi-glossy materials
    constexpr const float PLASTIC_GLOSSY = 32.0f;
    constexpr const float CERAMIC = 40.0f;
    constexpr const float MARBLE = 45.0f;

    // Glossy materials
    constexpr const float GLASS = 64.0f;
    constexpr const float POLISHED_WOOD = 50.0f;
    constexpr const float PAINTED_METAL = 55.0f;

    // Very shiny materials
    constexpr const float BRONZE = 76.8f;
    constexpr const float COPPER = 76.8f;
    constexpr const float BRASS = 83.2f;
    constexpr const float SILVER = 89.6f;
    constexpr const float GOLD = 83.2f;
    constexpr const float CHROME = 128.0f;
    constexpr const float POLISHED_METAL = 128.0f;
    constexpr const float MIRROR = 128.0f;

    // Special materials
    constexpr const float PEARL = 11.264f;
    constexpr const float JADE = 12.8f;
    constexpr const float OBSIDIAN = 38.4f;
    constexpr const float EMERALD = 76.8f;
    constexpr const float RUBY = 76.8f;
}