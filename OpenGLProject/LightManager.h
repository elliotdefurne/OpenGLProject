#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "constants.h"

class Shader;
class LightSource;
class Spotlight;
class Renderer;
class Player;

struct DirLight {
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

class LightManager {
public:
    LightManager(Renderer* renderer, Player* player);
    ~LightManager();

    void addPointLight(LightSource* light);
    void applyToShader(Shader* shader);
    void update();
    void draw();

private:
    static constexpr int MAX_POINT_LIGHTS = Constants::MAX_LIGHTS_SOURCES;
    std::vector<LightSource*> m_lightSources;
    Spotlight* m_flashlight;
    Player* m_player;
    struct DirLight m_dirLight;
};