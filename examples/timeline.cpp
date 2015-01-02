#include "../include/SFML/Graphics.hpp"
#include "../include/tweensf.h"
#include <iostream>

using namespace std;
using namespace sf;
using namespace tsf;

int main()
{
    RenderWindow win(VideoMode(800, 600), "TweenSF | Example2");

    CircleShape sh1(100);
    sh1.setFillColor(Color::Red);
    CircleShape sh2(100);
    sh2.setFillColor(Color::Black);
    sh2.setPosition(300.0f, 300.0f);
    sh2.setScale(0.5f, 0.5f);

    Properties<CircleShape> p1 = sh1, p2 = sh2;

    Timeline tl;

    // setup command chain
    tl
            .wait(sf::seconds(2))
            .tween(sh1, p2, sf::seconds(4), easing::bounceOut)
            .with().tween(sh2, p1, sf::seconds(4), easing::bounceOut) // with() mean that next command will be executed concurrent with command before
            .wait(sf::seconds(2))
            .tween(sh1, p1, sf::seconds(4), easing::bounceIn)
            .with().tween(sh2, p2, sf::seconds(4), easing::bounceIn)
            .call([]{ cout << "timeline complete!\n"; }); // callback is type of std::function<void(void)>; lambdas also can be callbacks

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
        tl.update(delta); // this updates current executing command (including tweens)

        win.draw(sh1);
        win.draw(sh2);
        win.display();
    }
}
