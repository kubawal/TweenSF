#include "../include/SFML/Graphics.hpp"
#include "../include/tweensf.h"
#include <iostream>

using namespace std;
using namespace sf;
using namespace tsf;

int main()
{
    RenderWindow win(VideoMode(800, 600), "TweenSF | ConvexShape/VertexArray tweening");

    ConvexShape cs(4);
    cs.setPoint(3, Vector2f(0.0f, 0.0f));
    cs.setPoint(2, Vector2f(200.0f, 0.0f));
    cs.setPoint(1, Vector2f(200.0f, 200.0f));
    cs.setPoint(0, Vector2f(0.0f, 200.0f));
    cs.setFillColor(Color::Black);

    // WARNING: cannot change point count, doing this will cause UB!
    Properties<ConvexShape> p1 = cs;
    p1.points[3] = Vector2f(150.0f, 200.0f);
    p1.points[2] = Vector2f(500.0f, 200.0f);
    p1.points[1] = Vector2f(600.0f, 500.0f);
    p1.points[0] = Vector2f(200.0f, 400.0f);

    Tween<ConvexShape> tween(cs, p1, sf::seconds(2), easing::backInOut(2.3f)); // easing::backInOut(ratio) creates new easing function
    // easing::backInOutDefault means easing::backInOut(1.7f)

    Clock timer;

    while(win.isOpen())
    {
        Event e;
        while(win.pollEvent(e))
        {
            if(e.type == Event::Closed)
                win.close();
        }

        win.clear(Color::White);

        sf::Time delta = timer.restart();
        tween.update(delta);

        win.draw(cs);
        win.display();
    }
}
