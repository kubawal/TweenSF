#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <vector>
#include <string>

namespace tsf
{

template<typename T>
struct Properties
{
    using ItemType = T;
    using SelfType = Properties<T>;
};

#ifdef SFML_GRAPHICS_HPP

template<>
struct Properties<sf::Transformable>
{
    using ItemType = sf::Transformable;
    using SelfType = Properties<sf::Transformable>;

    sf::Vector2f position, scale, origin;
    float rotation;

    Properties(const sf::Transformable& obj) { importFrom(obj); }
    Properties() { }

    void importFrom(const sf::Transformable& obj);
    void exportTo(sf::Transformable& obj);

    template<typename Functor>
    void forEachProperty(Functor& f) { f(position, "sf::Transformable|position"); f(scale, "sf::Transformable|scale"); f(origin, "sf::Transformable|origin"); f(rotation, "sf::Transformable|rotation"); }
};

template<>
struct Properties<sf::Sprite>
        : Properties<sf::Transformable>
{
    using ItemType = sf::Sprite;
    using SelfType = Properties<sf::Sprite>;
    using ParentType = Properties<sf::Transformable>;

    sf::Color color;
    sf::IntRect textureRect;

    Properties(const sf::Sprite& obj) : ParentType(obj) { importFrom(obj); }
    Properties() { }

    void importFrom(const sf::Sprite& obj);
    void exportTo(sf::Sprite& obj);

    template<typename Functor>
    void forEachProperty(Functor& f) { ParentType::forEachProperty(f); f(color, "sf::Sprite|color"); f(textureRect, "sf::Sprite|textureRect"); }
};

template<>
struct Properties<sf::VertexArray>
{
    using ItemType = sf::VertexArray;
    using SelfType = Properties<sf::VertexArray>;

    std::vector<sf::Vertex> points;

    Properties(const ItemType& obj) : points(obj.getVertexCount(), sf::Vector2f()){ importFrom(obj); }
    Properties() { }

    void importFrom(const ItemType& obj);
    void exportTo(ItemType& obj);

    template<typename F>
    void forEachProperty(F& f) { for(int i = 0; i < points.size(); i++) f(points[i], "sf::VertexArray|point" + std::to_string(i)); }
};

template<>
struct Properties<sf::Shape>
        : Properties<sf::Transformable>
{
    using ItemType = sf::Shape;
    using SelfType = Properties<sf::Shape>;
    using ParentType = Properties<sf::Transformable>;

    sf::Color fillColor, outlineColor;
    unsigned outlineThickness;

    Properties(const ItemType& obj) : ParentType(obj) { importFrom(obj); }
    Properties() { }

    void importFrom(const ItemType& obj);
    void exportTo(ItemType& obj);

    template<typename F>
    void forEachProperty(F& f) { ParentType::forEachProperty(f); f(fillColor, "sf::Shape|fillColor"); f(outlineColor, "sf::Shape|outlineColor"); f(outlineThickness, "sf::Shape|outlineThickness"); }
};

template<>
struct Properties<sf::CircleShape>
        : Properties<sf::Shape>
{
    using ItemType = sf::CircleShape;
    using SelfType = Properties<sf::CircleShape>;
    using ParentType = Properties<sf::Shape>;

    float radius;
    unsigned pointCount;

    Properties(const ItemType& obj) : ParentType(obj) { importFrom(obj); }
    Properties() { }

    void importFrom(const ItemType& obj) { ParentType::importFrom(obj); pointCount = obj.getPointCount(); radius = obj.getRadius(); }
    void exportTo(ItemType& obj) { ParentType::exportTo(obj); obj.setRadius(radius); obj.setPointCount(pointCount); }

    template<typename F>
    void forEachProperty(F& f) { ParentType::forEachProperty(f); f(radius, "sf::CircleShape|radius"); f(pointCount, "sf::CircleShape|pointCount"); }
};

template<>
struct Properties<sf::ConvexShape>
        : Properties<sf::Shape>
{
    using ItemType = sf::ConvexShape;
    using SelfType = Properties<sf::ConvexShape>;
    using ParentType = Properties<sf::Shape>;

    Properties(const ItemType& obj) : ParentType(obj), points(obj.getPointCount(), sf::Vector2f()) { importFrom(obj); }
    Properties() { }

    std::vector<sf::Vector2f> points;

    void importFrom(const ItemType& obj);
    void exportTo(ItemType& obj);

    template<typename F>
    void forEachProperty(F& f) { ParentType::forEachProperty(f); for(int i = 0; i < points.size(); i++) f(points[i], "sf::ConvexShape|point" + std::to_string(i)); }
};

template<>
struct Properties<sf::RectangleShape>
        : Properties<sf::Shape>
{
    using ItemType = sf::RectangleShape;
    using SelfType = Properties<sf::RectangleShape>;
    using ParentType = Properties<sf::Shape>;

    sf::Vector2f size;

    Properties(const ItemType& obj) : ParentType(obj) { importFrom(obj); }
    Properties() { }

    void importFrom(const ItemType& obj) { ParentType::importFrom(obj); size = obj.getSize(); }
    void exportTo(ItemType& obj) { ParentType::exportTo(obj); obj.setSize(size); }

    template<typename F>
    void forEachProperty(F& f) { ParentType::forEachProperty(f); f(size, "sf::RectangleShape|size"); }
};

template<>
struct Properties<sf::Text>
        : Properties<sf::Transformable>
{
    using ItemType = sf::Text;
    using SelfType = Properties<sf::Text>;
    using ParentType = Properties<sf::Transformable>;

    unsigned characterSize;
    sf::Color color;

    Properties(const ItemType& obj) : ParentType(obj) { importFrom(obj); }
    Properties() { }

    void importFrom(const ItemType& obj) { ParentType::importFrom(obj); characterSize = obj.getCharacterSize(); color = obj.getColor(); }
    void exportTo(ItemType& obj) { ParentType::exportTo(obj); obj.setCharacterSize(characterSize); obj.setColor(color); }

    template<typename F>
    void forEachProperty(F& f) { ParentType::forEachProperty(f); f(characterSize, "sf::Text|characterSize"); f(color, "sf::Text|color"); }
};

#endif

#ifdef SFML_SOUND_HPP
template<>
struct Properties<sf::Sound>
{
    using ItemType = sf::Sound;
    using SelfType = Properties<sf::Sound>;

    float volume, pitch, minDistance, attenuation;
    sf::Vector3f position;

    Properties(const ItemType& obj) { importFrom(obj); }
    Properties() { }

    void importFrom(const ItemType& obj);
    void exportTo(ItemType& obj);

    template<typename F>
    void forEachProperty(F& f) { f(volume, "sf::Sound|volume"); f(pitch, "sf::Sound|pitch"); f(minDistance, "sf::Sound|minDistance"); f(attenuation, "sf::Sound|attenuation"); f(position, "sf::Sound|position"); }
};

#endif

}

#endif // PROPERTIES_H
