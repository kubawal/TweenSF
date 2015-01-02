#include <iostream>
#include "../include/SFML/Graphics.hpp"
#include "../include/tweensf.h"

using namespace std;
using namespace tsf;
using namespace sf;

VertexArray* getGraph(Easing* ease)
{
    unsigned pts = 100;
    Vector2f pos(100, 100);
    Vector2f size(500, 400);
    VertexArray* va = new VertexArray(LinesStrip, pts);

    for(unsigned j = 0; j < pts; j++)
    {
        Vector2f vx;
        double prog = (double) (pts - j)/(double) pts;
        vx.y = pos.y + size.y - size.y * (*ease)(prog);
        vx.x = prog*size.x + pos.x;

        (*va)[j] = Vertex(vx, Color::Black);
    }

    return va;
}

int main()
{
    RenderWindow win(VideoMode(800, 600), "TweenSF | EasingTest");

    std::map<Easing*, string> funcs;
    funcs[&easing::linear] = "linear";
    funcs[&easing::quadIn] = "quadIn";
    funcs[&easing::quadOut] = "quadOut";
    funcs[&easing::quadInOut] = "quadInOut";
    funcs[&easing::cubicIn] = "cubicIn";
    funcs[&easing::cubicOut] = "cubicOut";
    funcs[&easing::cubicInOut] = "cubicInOut";
    funcs[&easing::quartIn] = "quartIn";
    funcs[&easing::quartOut] = "quartOut";
    funcs[&easing::quartInOut] = "quartInOut";
    funcs[&easing::quintIn] = "quintIn";
    funcs[&easing::quintOut] = "quintOut";
    funcs[&easing::quintInOut] = "quintInOut";
    funcs[&easing::sineIn] = "sineIn";
    funcs[&easing::sineOut] = "sineOut";
    funcs[&easing::sineInOut] = "sineInOut";
    funcs[&easing::backInDefault] = "backIn";
    funcs[&easing::backOutDefault] = "backOut";
    funcs[&easing::backInOutDefault] = "backInOut";
    funcs[&easing::bounceIn] = "bounceIn";
    funcs[&easing::bounceOut] = "bounceOut";
    funcs[&easing::bounceInOut] = "bounceInOut";
    funcs[&easing::elasticInDefault] = "elasticInDefault";
    funcs[&easing::elasticOutDefault] = "elasticOutDefault";
    funcs[&easing::elasticInOutDefault] = "elasticInOutDefault";

    int curr = 0;

    Font f;
    f.loadFromFile("arial.ttf");

    Text t("", f, 30);
    t.setColor(Color::Black);

    VertexArray* va = getGraph(funcs.begin()->first);

    while(win.isOpen())
    {
        auto it = funcs.begin();
        advance(it, curr);

        Event e;
        while(win.pollEvent(e))
        {
            if(e.type == Event::Closed)
                win.close();
            if(e.type == Event::KeyPressed)
            {
                switch(e.key.code)
                {
                case Keyboard::Left:
                    if(curr > 0)
                        curr--;
                    break;
                case Keyboard::Right:
                    if(curr < funcs.size() - 1)
                        curr++;
                    break;
                default:
                    break;
                }
                it = funcs.begin();
                advance(it, curr);
                delete va;
                va = getGraph(it->first);
            }
        }
        win.clear(Color::White);

        t.setString(it->second + "    " + to_string(curr + 1) + "/" + to_string(funcs.size()) + "\nUse the arrow left/right keys to change easing");

        win.draw(t);
        win.draw(*va);

        win.display();
    }
}
