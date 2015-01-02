#ifndef TWEEN_H
#define TWEEN_H

#include "easing.h"
#include "misc.h"
#include "properties.h"

namespace tsf
{

template<typename T>
class Tween
{
    T& obj;
    Properties<T> from, to, diff, curr;
    sf::Time duration, currTime;
    double progress;
    Easing ease;

    void updateVal();

public:
    Tween(T& obj, const Properties<T>& to, sf::Time duration, Easing ease = easing::linear);

    void updateTarget();

    Properties<T> getFrom() const { return from; }
    Properties<T> getTo() const { return to; }
    sf::Time getDuration() const { return duration; }
    Easing& getEasing() const { return ease; }
    double getProgress() const { return progress; }
    Properties<T> getCurr() const { return curr; }
    bool isCompleted() const { return progress >= 1.0; }
    sf::Time getTimePosition() const { return sf::microseconds(duration.asMicroseconds() * progress); }

    void update(sf::Time delta) { currTime += delta; updateVal(); }
    void setTimePosition(sf::Time timePos) { currTime = timePos; updateVal(); }
    void setProgress(double prog) { currTime = sf::microseconds(duration.asMicroseconds() * prog); updateVal(); }
};

}

#include "tweenImpl.inl"

#endif // TWEEN_H
