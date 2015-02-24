#include "color.h"

Color::Color() {
    m_R = 0;
    m_V = 0;
    m_B = 0;
}

Color::Color(double red, double green, double blue) {
    m_R = red;
    m_V = green;
    m_B = blue;
}

void Color::setColor(double red, double green, double blue) {
    m_R = red;
    m_V = green;
    m_B = blue;
}

double Color::getRed() {
    return m_R;
}

double Color::getGreen() {
    return m_V;
}

double Color::getBlue() {
    return m_B;
}
