#include "LightManager.h"

#include "Shader.h"
#include "LightSource.h"

LightManager::LightManager() {

}

LightManager::~LightManager() {
    for (auto& light : m_lightSources) {
        delete light;
    }
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
}

void LightManager::update() {
    for (auto& light : m_lightSources) {
        light->update();
    }
}
void LightManager::draw(){
    for (auto& light : m_lightSources) {
        light->draw();
    }
}