#pragma once

class Shader;
class LightSource;

#include <vector>

#include "constants.h"

class LightManager {
public:
    LightManager();
    ~LightManager();

    void addPointLight(LightSource* light);
    void applyToShader(Shader* shader);
    void update();
    void draw();

private:
    static constexpr int MAX_POINT_LIGHTS = Constants::MAX_LIGHTS_SOURCES;
    std::vector<LightSource*> m_lightSources;
};