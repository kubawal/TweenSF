#include "../include/timeline.h"

namespace tsf
{

void Timeline::update(sf::Time delta)
{
    if(cmds.empty())
        return;

    Command* active = cmds.front();
    active->update(delta);

    if(active->isCompleted())
    {
        sf::Time deltaLeft = active->getElapsedTime() - active->getDuration();
        delete active;
        cmds.pop_front();

        update(deltaLeft);
    }
}

void Timeline::Command::update(sf::Time elapsed)
{
    if(curr == sf::Time::Zero)
    {
        onStart();
        for(Command* cmd : conc)
            cmd->onStart();
    }

    curr += elapsed;
    updateChild(elapsed);

    for(Command* cmd : conc)
        cmd->update(elapsed);
}

sf::Time Timeline::Command::getDuration()
{
    sf::Time mx = sf::Time::Zero;

    mx = std::max(mx, getDurationChild());

    for(Command* cmd : conc)
        mx = std::max(mx, cmd->getDuration());

    return mx;
}

bool Timeline::Command::isCompleted()
{
    if(!isCompletedChild())
        return false;
    for(Command* cmd : conc)
        if(!cmd->isCompleted())
            return false;
    return true;
}

void Timeline::add(Command* cmd)
{
    if(nextWith)
    {
        cmds.back()->add(cmd);
        nextWith = false;
    }
    else
        cmds.push_back(cmd);
}

} // namespace tsf

