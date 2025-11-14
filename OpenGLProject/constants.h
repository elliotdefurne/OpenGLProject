#pragma once

namespace Constants {
    // Window
    constexpr int WINDOW_WIDTH = 1920;
    constexpr int WINDOW_HEIGHT = 1080;
    constexpr const char* WINDOW_TITLE = "Mon jeu OpenGL";
    constexpr bool IS_WINDOW_FULLSCREEN = true;

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
}