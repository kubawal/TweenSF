#ifndef TSF_TIMELINE_H
#define TSF_TIMELINE_H

#include "tween.h"
#include <list>
#include <iterator>
#include <SFML/System.hpp>

namespace tsf
{

class Timeline
{
    struct Command
    {
        sf::Time curr;
        void update(sf::Time elapsed);
        sf::Time getElapsedTime() { return curr; }

        std::vector<Command*> conc;

        void add(Command* cmd) { conc.push_back(cmd); }

        bool isCompleted();
        virtual bool isCompletedChild() = 0;
        virtual void onStart() { }
        virtual void updateChild(sf::Time) = 0;
        sf::Time getDuration();
        virtual sf::Time getDurationChild() { return sf::Time::Zero; }
        virtual void destroy() noexcept { }
        virtual ~Command() { destroy(); for(Command* cmd : conc) delete cmd; }
    };
    struct WaitCommand
            : Command
    {
        sf::Time duration;

        WaitCommand(sf::Time duration) : duration(duration) { }

        virtual void updateChild(sf::Time elapsed) override { curr += elapsed; }
        virtual bool isCompletedChild() override { return curr >= duration; }
        virtual sf::Time getDurationChild() override { return duration; }
    };
    struct CallCommand
            : Command
    {
        using Callback = std::function<void(void)>;
        Callback callback;
        bool called;

        CallCommand(Callback callback) : callback(callback), called(false) { }

        virtual void updateChild(sf::Time) override { if(!called) { callback(); called = true; } }
        virtual bool isCompletedChild() override { return called; }
    };
    template<typename ObjType>
    struct TweenCommand
            : Command
    {
        Tween<ObjType>* tween;
        bool acq;

        TweenCommand(ObjType& obj, const Properties<ObjType> to, const sf::Time& duration, Easing& ease) : tween(new Tween<ObjType>(obj, to, duration, ease)), acq(true) { }
        TweenCommand(Tween<ObjType>& t) : acq(false), tween(&t) { }

        virtual void destroy() noexcept override { if(acq) delete tween; }

        virtual void onStart() { tween->updateTarget(); }
        virtual void updateChild(sf::Time elapsed) override { tween->update(elapsed); }
        virtual bool isCompletedChild() override { return tween->isCompleted(); }
        virtual sf::Time getDurationChild() override { return tween->getDuration(); }
    };


    std::list<Command*> cmds;
    bool nextWith;

    void add(Command* cmd);

public:
    Timeline() : nextWith(false) { }

    // zadania
    Timeline& wait(sf::Time duration) { add(new WaitCommand(duration)); return *this; }
    Timeline& call(const CallCommand::Callback& callback) { add(new CallCommand(callback)); return *this; }
    template<typename ObjType>
    Timeline& tween(Tween<ObjType>& t) { add(new TweenCommand<ObjType>(t)); return *this; }
    template<typename ObjType>
    Timeline& tween(ObjType& obj, const Properties<ObjType> to, const sf::Time& duration, Easing& ease = easing::linear) { add(new TweenCommand<ObjType>(obj, to, duration, ease)); return *this; }

    // sterowanie przepływem
    Timeline& removeLastCommand() { delete cmds.back(); cmds.pop_back(); return *this; }
    Timeline& removeLastCommands(int n) { auto it = cmds.end(); std::advance(it, -n); for(auto i = it; i != cmds.end(); i++) delete *i; cmds.erase(it, cmds.end()); return *this; }
    Timeline& removeAllCommands() { for(Command* cmd : cmds) delete cmd; cmds.clear(); return *this; }
    Timeline& with() { nextWith = true; return *this; }

    void update(sf::Time elapsed);
};

} // namespace tsf

#endif // TSF_TIMELINE_H
