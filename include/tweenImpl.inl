#include "tween.h"
#include <string>

namespace tsf
{

namespace priv
{

template<typename T>
struct GetProperty
{
    std::string sig;
    T val;
    bool found;

    GetProperty(std::string sig) : sig(sig), found(false) { }

    void operator()(T& t, std::string sign) { if(sign == sig) { val = t; found = true; } }
    template<typename AnyType>
    void operator()(AnyType&, std::string) { }
};

template<typename PropType, typename ObjType>
inline PropType getProperty(Properties<ObjType>& props, std::string sign)
{
    GetProperty<PropType> gp(sign);
    props.forEachProperty(gp);
    return gp.val;
}

template<typename T>
struct SetProperty
{
    std::string sig;
    T val;
    bool found;

    SetProperty(std::string sig, const T& val) : sig(sig), val(val), found(false) { }

    void operator()(T& t, std::string sign) { if(sign == sig) { t = val; found = true; } }
    template<typename AnyType>
    void operator()(AnyType&, std::string) { }
};

template<typename PropType, typename ObjType>
inline void setProperty(Properties<ObjType>& props, std::string sign, PropType val)
{
    SetProperty<PropType> gp(sign, val);
    props.forEachProperty(gp);
}

////

template<typename ObjType>
struct CalcDiff
{
    Properties<ObjType> from, to, diff;

    template<typename PropType>
    void operator()(PropType& toProp, std::string sig)
    {
        PropType diffProp = toProp - getProperty<PropType>(from, sig);
        setProperty(diff, sig, diffProp);
    }
};

template<typename ObjType>
inline Properties<ObjType> calcDiff(Properties<ObjType>& o1, Properties<ObjType>& o2)
{
    CalcDiff<ObjType> obj;
    obj.diff = obj.from = o2;
    obj.to = o1;
    o1.forEachProperty(obj);
    return obj.diff;
}

template<typename ObjType>
struct CalcSum
{
    Properties<ObjType> o1, o2, sum;

    template<typename PropType>
    void operator()(PropType& o1Prop, std::string sig)
    {
        PropType sumProp = o1Prop + getProperty<PropType>(o2, sig);
        setProperty(sum, sig, sumProp);
    }
};

template<typename ObjType>
inline Properties<ObjType> calcSum(Properties<ObjType>& o1, Properties<ObjType>& o2)
{
    CalcSum<ObjType> obj;
    obj.sum = obj.o1 = o1;
    obj.o2 = o2;
    o1.forEachProperty(obj);
    return obj.sum;
}

template<typename ObjType>
struct CalcProd
{
    Properties<ObjType> o, prod;
    double m;

    template<typename PropType>
    void operator()(PropType& o1Prop, std::string sig)
    {
        PropType prodProp = o1Prop * m;
        setProperty(prod, sig, prodProp);
    }
};

template<typename ObjType>
inline Properties<ObjType> calcProd(Properties<ObjType>& o, double m)
{
    CalcProd<ObjType> obj;
    obj.prod = obj.o = o;
    obj.m = m;
    o.forEachProperty(obj);
    return obj.prod;
}

}

////

template<typename T>
Tween<T>::Tween(T& obj, const Properties<T>& to, sf::Time duration, Easing ease)
    : obj(obj), to(to), duration(duration), progress(0.0), ease(ease)
{
    updateTarget();
}

template<typename T>
void Tween<T>::updateTarget()
{
    from.importFrom(obj);
    curr = from;

    diff = priv::calcDiff(to, from);
}

template<typename T>
void Tween<T>::updateVal()
{
    progress = currTime / duration;

    if(progress >= 1.0)
        progress = 1.0;

    double ev = ease(progress);
    Properties<T> prod = priv::calcProd(diff, ev);
    curr = priv::calcSum(from, prod);

    curr.exportTo(obj);
}
}
