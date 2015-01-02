#ifndef MISC_H
#define MISC_H

#include <SFML/System.hpp>

#ifndef M_PI
    #define M_PI 3.14159265359
#endif

#ifndef M_PI_2
    #define M_PI_2 6.28318530718
#endif

#ifdef SFML_GRAPHICS_HPP
inline sf::Color operator*(const sf::Color& l, double r)
{
    return sf::Color(l.r * r, l.g * r, l.b * r, l.a * r);
}

template<typename T>
inline sf::Rect<T> operator+(const sf::Rect<T>& l, const sf::Rect<T>& r)
{
    return sf::Rect<T>(l.left + r.left, l.top + r.top, l.width + r.width, l.height + r.height);
}

template<typename T>
inline sf::Rect<T> operator-(const sf::Rect<T>& l, const sf::Rect<T>& r)
{
    return sf::Rect<T>(l.left - r.left, l.top - r.top, l.width - r.width, l.height - r.height);
}

template<typename T>
inline sf::Rect<T> operator*(const sf::Rect<T>& l, double r)
{
    return sf::Rect<T>(l.left * r, l.top * r, l.width * r, l.height * r);
}
#endif

template<typename T>
inline sf::Vector2<T> operator*(const sf::Vector2<T>& l, double r)
{
    return sf::Vector2<T>(l.x * r, l.y * r);
}

#endif // MISC_H
