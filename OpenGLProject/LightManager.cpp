#include "LightManager.h"

#include "Shader.h"
#include "LightSource.h"
#include "Spotlight.h"
#include "Player.h"
#include "Renderer.h"

LightManager::LightManager(Renderer* renderer, Player* player) {
    m_flashlight = new Spotlight(renderer);
    m_player = player;

    // DirLight

    m_dirLight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    m_dirLight.ambient = glm::vec3(0.2f, 0.2f, 0.05f);
    m_dirLight.diffuse = glm::vec3(0.2f, 0.2f, 0.2f);
    m_dirLight.specular = glm::vec3(0.5f, 0.5f, 0.5f);
}

LightManager::~LightManager() {
    for (auto& light : m_lightSources) {
        delete light;
    }

	delete m_flashlight;
}
void LightManager::addPointLight(LightSource* light) {
    if (m_lightSources.size() < MAX_POINT_LIGHTS) {
        m_lightSources.push_back(light);
    }
    else {
        throw std::invalid_argument("Light limite reached, please increase it in LightManager.");
    }
}

void LightManager::applyToShader(Shader* shader) {
    // Lightsources

    shader->setInt("numberLightSources", static_cast<int>(m_lightSources.size()));

    for (size_t i = 0; i < m_lightSources.size(); ++i) {
        std::string base = "lightSources[" + std::to_string(i) + "]";
        shader->setVec3(base + ".position", m_lightSources[i]->getPosition());

        shader->setVec3(base + ".ambient", m_lightSources[i]->getAmbient());
        shader->setVec3(base + ".diffuse", m_lightSources[i]->getDiffuse());
        shader->setVec3(base + ".specular", m_lightSources[i]->getSpecular());

        shader->setFloat(base + ".constant", m_lightSources[i]->getConstant());
        shader->setFloat(base + ".linear", m_lightSources[i]->getLinear());
        shader->setFloat(base + ".quadratic", m_lightSources[i]->getQuadratic());
    }

    // Flashlight

    m_flashlight->applyToShader(shader, m_player->getFlashlightIsEnabled());

    // DirLight

    shader->setVec3("dirLight.direction", m_dirLight.direction);
    shader->setVec3("dirLight.ambient", m_dirLight.ambient);
    shader->setVec3("dirLight.diffuse", m_dirLight.diffuse);
    shader->setVec3("dirLight.specular", m_dirLight.specular);
}

void LightManager::update() {
    for (auto& light : m_lightSources) {
        light->update();
    }
    m_flashlight->update(m_player);
}
void LightManager::draw(){
    for (auto& light : m_lightSources) {
        light->draw();
    }
}