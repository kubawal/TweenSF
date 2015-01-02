#ifndef EASING_H
#define EASING_H

#include <cmath>
#include <functional>

namespace tsf
{

using Easing = std::function<double(double)>;

template<typename ValueType>
inline ValueType getEasedValue(Easing ease, ValueType from, ValueType to, double progress)
{
    if(progress <= 0.0)
        return from;
    if(progress >= 1.0)
        return to;
    else
        return from + (to - from) * ease(progress);
}

template<typename ValueType>
inline ValueType getEasedOffset(Easing ease, ValueType from, ValueType to, double progress)
{
    if(progress <= 0.0)
        return from;
    if(progress >= 1.0)
        return to;
    else
        return (to - from) * ease(progress);
}

namespace easing
{
// dostosowywalne
Easing powIn(int N);
Easing powOut(int N);
Easing powInOut(int N);
Easing backIn(double ratio);
Easing backOut(double ratio);
Easing backInOut(double ratio);
Easing elasticIn(double amplitude, double period);
Easing elasticOut(double amplitude, double period);
Easing elasticInOut(double amplitude, double period);

// predefiniowane
extern Easing
    linear,
    quadIn, quadOut, quadInOut,
    cubicIn, cubicOut, cubicInOut,
    quartIn, quartOut, quartInOut,
    quintIn, quintOut, quintInOut,
    sineIn, sineOut, sineInOut,
    backInDefault, backOutDefault, backInOutDefault,
    bounceIn, bounceOut, bounceInOut,
    elasticInDefault, elasticOutDefault, elasticInOutDefault;


}
}

#endif // EASING_H
