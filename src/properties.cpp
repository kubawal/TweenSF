#include "../include/SFML/Graphics.hpp"
#include "../include/SFML/Audio.hpp"
#include "../include/properties.h"
#include <stdexcept>

namespace tsf
{

void Properties<sf::Transformable>::importFrom(const ItemType& obj)
{
    position = obj.getPosition();
    scale = obj.getScale();
    origin = obj.getOrigin();
    rotation = obj.getRotation();
}
void Properties<sf::Transformable>::exportTo(ItemType& obj)
{
    obj.setOrigin(origin);
    obj.setScale(scale);
    obj.setPosition(position);
    obj.setRotation(rotation);
}

void Properties<sf::Sprite>::importFrom(const ItemType& obj)
{
    ParentType::importFrom(obj);

    color = obj.getColor();
    textureRect = obj.getTextureRect();
}

void Properties<sf::Sprite>::exportTo(ItemType& obj)
{
    ParentType::exportTo(obj);

    obj.setColor(color);
    obj.setTextureRect(textureRect);
}

void Properties<sf::Shape>::importFrom(const ItemType& obj)
{
    ParentType::importFrom(obj);

    fillColor = obj.getFillColor();
    outlineColor = obj.getOutlineColor();
    outlineThickness = obj.getOutlineThickness();
}

void Properties<sf::Shape>::exportTo(ItemType& obj)
{
    ParentType::exportTo(obj);

    obj.setFillColor(fillColor);
    obj.setOutlineColor(outlineColor);
    obj.setOutlineThickness(outlineThickness);
}

void Properties<sf::VertexArray>::importFrom(const ItemType& obj)
{
    if(obj.getVertexCount() != points.size())
        throw std::invalid_argument("Properties<sf::VertexArray> : cannot import from object with diffrent pointCount");


    for(int i = 0; i < points.size(); i++)
        points[i] = obj[i];
}

void Properties<sf::VertexArray>::exportTo(ItemType& obj)
{
    if(obj.getVertexCount() != points.size())
        throw std::invalid_argument("Properties<sf::VertexArray> : cannot export to object with diffrent pointCount");

    for(int i = 0; i < points.size(); i++)
        obj[i] = points[i];
}

void Properties<sf::ConvexShape>::importFrom(const ItemType& obj)
{
    //if(obj.getPointCount() != points.size())
    //   throw std::invalid_argument("Properties<sf::ConvexShape> : cannot import from object with diffrent pointCount");

    ParentType::importFrom(obj);

    points.clear();
    points.resize(obj.getPointCount(), sf::Vector2f());

    for(int i = 0; i < points.size(); i++)
        points[i] = obj.getPoint(i);
}

void Properties<sf::ConvexShape>::exportTo(ItemType& obj)
{
    //if(obj.getPointCount() != points.size())
    //    throw std::invalid_argument("Properties<sf::ConvexShape> : cannot export to object with diffrent pointCount");

    ParentType::exportTo(obj);

    obj.setPointCount(points.size());

    for(int i = 0; i < points.size(); i++)
        obj.setPoint(i, points[i]);
}

void Properties<sf::Sound>::importFrom(const ItemType& obj)
{
    volume = obj.getVolume();
    pitch = obj.getPitch();
    minDistance = obj.getMinDistance();
    attenuation = obj.getAttenuation();
    position = obj.getPosition();
}

void Properties<sf::Sound>::exportTo(ItemType& obj)
{
    obj.setVolume(volume);
    obj.setPitch(pitch);
    obj.setMinDistance(minDistance);
    obj.setAttenuation(attenuation);
    obj.setPosition(position);
}
}
