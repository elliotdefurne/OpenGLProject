#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transformation {
public:
    Transformation() : m_trans(glm::mat4(1.0f)) {}

    Transformation& rotate(glm::vec3 axes, float degrees) {
        m_trans = glm::rotate(m_trans, glm::radians(degrees), axes);
        return *this;
    }

    Transformation& scale(glm::vec3 scale) {
        m_trans = glm::scale(m_trans, scale);
        return *this;
    }

    Transformation& translate(glm::vec3 translation) {
        m_trans = glm::translate(m_trans, translation);
        return *this;
    }

    glm::mat4 getMatrix() const { return m_trans; }

private:
    glm::mat4 m_trans;
};
