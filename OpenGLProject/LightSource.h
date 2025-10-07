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
    glm::vec3 getAmbient();
    glm::vec3 getDiffuse();
    glm::vec3 getSpecular();
    glm::vec3 getPos();

    // Accès au Cube (version smart pointer)
    std::unique_ptr<Cube>& getCube();

private:
    std::unique_ptr<Cube> m_cube;  // Propriété du cube
    glm::vec3 m_lightColor, m_ambient, m_diffuse, m_specular;
};
