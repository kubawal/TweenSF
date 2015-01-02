#include "../include/SFML/Graphics.hpp"
#include "../include/tweensf.h"

using namespace std;
using namespace sf;
using namespace tsf;

int main()
{
    RenderWindow win(VideoMode(800, 600), "TweenSF | Example1");

    CircleShape sh(100);
    sh.setFillColor(Color::Black);

    Properties<CircleShape> p1 = sh;
    p1.position += Vector2f(300, 300);
    p1.scale = Vector2f(0.5f, 0.5f);
    p1.fillColor = Color::Red;

    // arguments: object to tween, target properties, duration, easing (default easing::linear)
    Tween<CircleShape> tween(sh, p1, sf::seconds(5), easing::bounceOut);

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
        tween.update(delta); // tween calculates properties and automatically updates target object properties

        win.draw(sh);
        win.display();
    }
}
