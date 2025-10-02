#pragma once

#include <memory>
#include <glm/glm.hpp>

class Cube;
class Shader;
class Texture;

class LightSource {
public:
    LightSource(glm::vec3 center, Shader* shader, Texture* texture, glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f));
    ~LightSource();

    void draw();
    void update();

    glm::vec3 getLightColor();
    glm::vec3 getPos();

    // Acc�s au Cube (version smart pointer)
    std::unique_ptr<Cube>& getCube();

private:
    std::unique_ptr<Cube> m_cube;  // Propri�t� du cube
    glm::vec3 m_lightColor;
};
