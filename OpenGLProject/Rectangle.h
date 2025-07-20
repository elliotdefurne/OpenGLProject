#pragma once
class Rectangle {
public:
    Rectangle(float x, float y, float width, float height);

    void move(float dx, float dy);
    void draw() const;

private:
    float m_x, m_y;
    float m_width, m_height;
};

