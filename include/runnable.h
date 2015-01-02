#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <utility>
#include <iostream>

/*
 * License:
Copyright (c) 2015 kubawal

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.

*/

// UWAGA: Wymaga kompilatora >= C++11

template<typename returnType, typename... args>
class Runnable
        // określa obiekt który można uruchomić
        // obiekt ten przyjmuje argumenty args... i zwraca returnType
        // może być utworzone z funkcji, metody lub obiektu funkcyjnego
        // można inicjować wyrażeniem lambda:
        // Runnable<void, int>([](int)->void { //... });
{
private:
    template<typename rreturnType, typename... aargs>
    struct FuncBase
    {
        virtual returnType run(aargs...) = 0;
        virtual FuncBase<rreturnType, aargs...>* clone() const = 0;
        virtual ~FuncBase() { }
    };

    template<typename rreturnType, typename... aargs>
    struct Func : FuncBase<rreturnType, aargs...>
    {
        rreturnType (*func) (aargs...);
        rreturnType run(aargs... arg) { return func(arg...); }

        FuncBase<rreturnType, aargs...>* clone() const { return new Func<rreturnType, args...>(func); }

        Func(rreturnType (*func) (aargs...)) : func(func) { }
    };

    template<typename memberType, typename rreturnType, typename... aargs>
    struct MemberFunc : public FuncBase<rreturnType, aargs...>
    {
        memberType& owner;
        rreturnType (memberType::*member) (args...);
        rreturnType run(aargs... arg) { return (owner.*member)(arg...); }

        FuncBase<rreturnType, aargs...>* clone() const { return new MemberFunc<memberType, rreturnType, aargs...>(owner, member); }

        MemberFunc(memberType& owner, rreturnType (memberType::*member) (aargs...)) : owner(owner), member(member) { }
    };

    template<typename functorType, typename rreturnType, typename... aargs>
    struct FunctorFunc : public FuncBase<rreturnType, aargs...>
    {
        functorType& owner;
        rreturnType run(aargs... arg) { return owner(arg...); }

        FuncBase<rreturnType, aargs...>* clone() const { return new FunctorFunc<functorType, rreturnType, aargs...>(owner); }

        FunctorFunc(functorType& owner) : owner(owner) { }
    };

//    template<typename functorType, typename rreturnType, typename... aargs>
//    struct LambdaFunc : public FuncBase<rreturnType, aargs...>
//    {
//        functorType owner;
//        rreturnType run(aargs... arg) { return owner(arg...); }

//        FuncBase<rreturnType, aargs...>* clone() const { return new LambdaFunc<functorType, rreturnType, aargs...>(functorType(owner)); }

//        LambdaFunc(functorType&& owner) : owner(std::move(owner)) { }
//    };

    FuncBase<returnType, args...>* f;

public:
    // konstruktory:

    // z funkcji
    Runnable(returnType (*func) (args...)) { f = new Func<returnType, args...>(func); }

    // z metody
    template<typename memberType>
    Runnable(memberType& owner, returnType (memberType::*member) (args...)) { f = new MemberFunc<memberType, returnType, args...>(owner, member); }

    // z obiektu funkcyjnego
    template<typename functorType>
    Runnable(functorType& owner) { f = new FunctorFunc<functorType, returnType, args...>(owner); }

//    template<typename lambdaType>
//    Runnable(lambdaType&& owner) { f = new LambdaFunc<lambdaType, returnType, args...>(std::move(owner)); }

    // konstruktory kopiujące
    Runnable(const Runnable<returnType, args...>& r) : f(r.f->clone()) { }

    Runnable<returnType, args...>& operator=(const Runnable<returnType, args...>& r) { delete f; f = r.f->clone(); }

    ~Runnable() { delete f; }

    returnType run(args... arg) { return f->run(arg...); }
    returnType operator() (args... arg) { return f->run(arg...); }
};

// funkcje pomocnicze - nie trzeba używać argumentów szablonów
template<typename returnType, typename... args>
inline Runnable<returnType, args...> makeRunnable(returnType (*func) (args...))
{
    return Runnable<returnType, args...>(func);
}

template<typename memberType, typename returnType, typename... args>
inline Runnable<returnType, args...> makeRunnable(memberType& owner, returnType (memberType::*member) (args...))
{
    return Runnable<returnType, args...>(owner, member);
}

template<typename functorType, typename returnType, typename... args>
inline Runnable<returnType, args...> makeRunnable(functorType& owner)
{
    return Runnable<returnType, args...>(owner);
}

#endif // RUNNABLE_H
