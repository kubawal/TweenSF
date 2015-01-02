#include "../include/easing.h"
#include "../include/misc.h"

#define EL(d) [](double d)->double

namespace tsf
{
namespace easing
{

// funkcje pomocnicze
inline double getPowIn(double d, int N)
{
    return std::pow(d, N);
}

inline double getPowOut(double d, int N)
{
    return 1 - std::pow(1 - d, N);
}

inline double getPowInOut(double t, int N)
{
    if ((t *= 2) < 1)
        return 0.5*std::pow(t, N);
    else
        return 1 - 0.5*std::abs(std::pow(2 - t, N));
}

inline double getBackIn(double t, double a)
{
    return t*t*((a + 1)*t - a);
}

inline double getBackOut(double t, double a)
{
    --t;
    return (t*t*((a + 1)*t + a) + 1);
}

inline double getBackInOut(double t, double a)
{
    a *= 1.525;
    if ((t *= 2) < 1)
        return 0.5*(t*t*((a + 1)*t - a));
    else
    {
        t -= 2;
        return 0.5*(t*t*((a + 1)*t + a) + 2);
    }
}

inline double getElasticIn(double t, double amplitude, double period)
{
    if (t==0 || t==1) return t;
    double s = period/M_PI_2*std::asin(1/amplitude);
    t -= 1;
    return -(amplitude*std::pow(2,10*t)*std::sin((t-s)*M_PI_2/period));
}

inline double getElasticOut(double t, double amplitude, double period)
{
    if (t==0 || t==1) return t;
    double s = period/M_PI_2 * std::asin(1/amplitude);
    return (amplitude*std::pow(2,-10*t)*std::sin((t-s)*M_PI_2/period )+1);
}

inline double getElasticInOut(double t, double amplitude, double period)
{
    static double pi2 = M_PI * 2;
    double s = period/pi2*std::asin(1/amplitude);
    t *= 2;
    if (t < 1)
    {
        t -= 1;
        return -0.5*(amplitude*std::pow(2, 10*t)*std::sin((t - s)*pi2/period ));
    }
    t -= 1;
    return amplitude*std::pow(2, -10*(t))*std::sin((t - s)*pi2/period)*0.5+1;
}

inline double getBounceOut(double p)
{
    if(p < 4/11.0)
        {
            return (121 * p * p)/16.0;
        }
        else if(p < 8/11.0)
        {
            return (363/40.0 * p * p) - (99/10.0 * p) + 17/5.0;
        }
        else if(p < 9/10.0)
        {
            return (4356/361.0 * p * p) - (35442/1805.0 * p) + 16061/1805.0;
        }
        else
        {
            return (54/5.0 * p * p) - (513/25.0 * p) + 268/25.0;
        }
}

inline double getBounceIn(double t)
{
    return 1-getBounceOut(1-t);
}

inline double getBounceInOut(double p)
{
    if(p < 0.5)
    {
        return 0.5 * getBounceIn(p*2);
    }
    else
    {
        return 0.5 * getBounceOut(p * 2 - 1) + 0.5;
    }
}

// oparte na szablonach
template<int N>
double getPowIn(double d)
{
    return getPowIn(d, N);
}

template<int N>
double getPowOut(double d)
{
    return getPowOut(d, N);
}

template<int N>
double getPowInOut(double d)
{
    return getPowInOut(d, N);
}

template<int N, int D>
double getBackIn(double d)
{
    return getBackIn(d, N/D);
}

template<int N, int D>
double getBackOut(double d)
{
    return getBackOut(d, N/D);
}

template<int N, int D>
double getBackInOut(double d)
{
    return getBackInOut(d, N/D);
}

// METODY EASINGU
Easing

// po prostej
linear = Easing(EL(d) { return d; }),

// oparte na potęgach
quadIn = Easing(getPowIn<2>),
quadOut = Easing(getPowOut<2>),
quadInOut = Easing(getPowInOut<2>),

cubicIn = Easing(getPowIn<3>),
cubicOut = Easing(getPowOut<3>),
cubicInOut = Easing(getPowInOut<3>),

quartIn = Easing(getPowIn<4>),
quartOut = Easing(getPowOut<4>),
quartInOut = Easing(getPowInOut<4>),

quintIn = Easing(getPowIn<5>),
quintOut = Easing(getPowOut<5>),
quintInOut = Easing(getPowInOut<5>),

// sinusoidalne
sineIn = Easing(EL(d) { return 1-std::cos(d*M_PI/2); }),
sineOut = Easing(EL(d) { return std::sin(d*M_PI/2); }),
sineInOut = Easing(EL(d) { return -0.5*(std::cos(M_PI*d) - 1); }),

// z wyjściem
backInDefault = Easing(getBackIn<17, 10>),
backOutDefault = Easing(getBackOut<17, 10>),
backInOutDefault = Easing(getBackInOut<17, 10>),

bounceIn = Easing(getBounceIn),
bounceOut = Easing(getBounceOut),
bounceInOut = Easing(getBounceInOut),

elasticInDefault = Easing(elasticIn(1, 0.3)),
elasticOutDefault = Easing(elasticOut(1, 0.3)),
elasticInOutDefault = Easing(elasticInOut(1, 0.3*1.5));

////

// dostosowywalne
Easing powIn(int N)
{
    return Easing([=](double d) mutable -> double
        {
            return getPowIn(d, N);
        }
    );
}
Easing powOut(int N)
{
    return Easing([=](double d) mutable -> double
        {
            return getPowOut(d, N);
        }
    );
}
Easing powInOut(int N)
{
    return Easing([=](double d) mutable -> double
        {
            return getPowInOut(d, N);
        }
    );
}

Easing backIn(double ratio)
{
    return Easing([=](double d) mutable -> double
        {
            return getBackIn(d, ratio);
        }
    );
}
Easing backOut(double ratio)
{
    return Easing([=](double d) mutable -> double
        {
            return getBackOut(d, ratio);
        }
    );
}

Easing backInOut(double ratio)
{
    return Easing([=](double d) mutable -> double
        {
            return getBackInOut(d, ratio);
        }
    );
}

Easing elasticIn(double amplitude, double period)
{
    return Easing([=](double d) mutable -> double
        {
            return getElasticIn(d, amplitude, period);
        }
    );
}

Easing elasticOut(double amplitude, double period)
{
    return Easing([=](double d) mutable -> double
        {
            return getElasticOut(d, amplitude, period);
        }
    );
}

Easing elasticInOut(double amplitude, double period)
{
    return Easing([=](double d) mutable -> double
        {
            return getElasticInOut(d, amplitude, period);
        }
    );
}

}
}
