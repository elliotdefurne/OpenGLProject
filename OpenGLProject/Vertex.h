#pragma once

/**
 * @class Vertex
 * @brief Repr�sente un sommet 3D avec position, couleur et coordonn�es de texture.
 *
 * Chaque vertex contient :
 * - m_x, m_y, m_z : position dans l'espace 3D
 * - m_r, m_g, m_b : couleur (RGB)
 * - m_s, m_t : coordonn�es de texture (UV)
 */
class Vertex
{
public:
    /**
     * @brief Constructeur avec uniquement la position.
     * Les couleurs par d�faut sont blanches et les coordonn�es de texture sont � 0.
     */
    Vertex(float x, float y, float z)
        : m_x(x), m_y(y), m_z(z), m_r(1.0f), m_g(1.0f), m_b(1.0f), m_s(0.0f), m_t(0.0f) {
    }

    /**
     * @brief Constructeur avec position et couleur.
     * Les coordonn�es de texture sont initialis�es � 0.
     */
    Vertex(float x, float y, float z, float r, float g, float b)
        : m_x(x), m_y(y), m_z(z), m_r(r), m_g(g), m_b(b), m_s(0.0f), m_t(0.0f) {
    }

    /**
     * @brief Constructeur complet avec position, couleur et coordonn�es de texture.
     */
    Vertex(float x, float y, float z, float r, float g, float b, float s, float t)
        : m_x(x), m_y(y), m_z(z), m_r(r), m_g(g), m_b(b), m_s(s), m_t(t) {
    }

    /**
     * @brief Destructeur par d�faut.
     */
    ~Vertex() = default;

    // Getters
    float getX() const { return m_x; }
    float getY() const { return m_y; }
    float getZ() const { return m_z; }
    float getR() const { return m_r; }
    float getG() const { return m_g; }
    float getB() const { return m_b; }
    float getS() const { return m_s; }
    float getT() const { return m_t; }

private:
    float m_x, m_y, m_z;   ///< Coordonn�es du sommet
    float m_r, m_g, m_b;   ///< Couleur RGB
    float m_s, m_t;        ///< Coordonn�es de texture UV
};
