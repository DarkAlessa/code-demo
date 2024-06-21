#include "line.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <string>
#include <cmath>
//#define NDEBUG
#include <cassert>

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "Angle");
    window.setSize(sf::Vector2u(640, 480));
    window.setFramerateLimit(60);

    [[maybe_unused]] auto win_x = window.getSize().x;
    [[maybe_unused]] auto win_y = window.getSize().y;

    sf::Font font;
    assert(font.loadFromFile("./assets/font/Consola.TTF"));

    sf::Text axis_x;
    axis_x.setFont(font);
    axis_x.setCharacterSize(11);
    axis_x.setFillColor(sf::Color::White);
    axis_x.setPosition(sf::Vector2f(10.0f, 10.0f));
    axis_x.setString("X: 0");

    sf::Text axis_y = axis_x;
    axis_y.setString("Y: 0");
    axis_y.setPosition(sf::Vector2f(10.0f, 24.0f));

    sf::Text angle_text = axis_x;

    sf::CircleShape compass(20.f, 3);
    compass.setFillColor(sf::Color::Magenta);
    compass.setOutlineThickness(2.0f);
    compass.setOutlineColor(sf::Color::White);
    compass.setOrigin(20.0f, 20.0f);
    compass.setPosition(sf::Vector2f(win_x / 2, win_y / 2));
////---------------------------------------------------------------
    sf::Vector2f vp_start(compass.getPosition().x, 0.0f);
    sf::Vector2f vp_end(compass.getPosition().x, win_y);
    sf::Vector2f hp_start(0.0f, compass.getPosition().y);
    sf::Vector2f hp_end(win_x, compass.getPosition().y);
    
    Line v_line(vp_start, vp_end);
    Line h_line(hp_start, hp_end);

    sf::Vector2f angle_start(compass.getPosition().x, compass.getPosition().y);
    sf::Vector2f angle_end(0.0f, 0.0f);

    Line angle_line(angle_start, angle_end);
    angle_line.setColor(sf::Color::White, sf::Color(50, 208, 254, 255));

    Line angle_x(sf::Mouse::getPosition(window).x, compass.getPosition().y,
                 sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    angle_x.setColor(sf::Color::White, sf::Color(50, 208, 254, 255));
    Line angle_y(compass.getPosition().x, sf::Mouse::getPosition(window).y,
                 sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    angle_y.setColor(sf::Color::White, sf::Color(50, 208, 254, 255));

    bool show_line = true;
////---------------------------------------------------------------
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.scancode == sf::Keyboard::Scan::Space) {
                        show_line = !show_line;
                    }
                    break;
                default:
                    break;
            }
        }

        compass.move(sf::Vector2f(1.0f, 0.0f));
        if (compass.getPosition().x > (win_x + 20.0f)) compass.setPosition(-20.0f, compass.getPosition().y);

        axis_x.setString("X: " + std::to_string(sf::Mouse::getPosition(window).x));
        axis_y.setString("Y: " + std::to_string(sf::Mouse::getPosition(window).y));
        angle_text.setString( "(" + std::to_string((int)(sf::Mouse::getPosition(window).x - compass.getPosition().x)) + ", " +
                                    std::to_string((int)(compass.getPosition().y - sf::Mouse::getPosition(window).y)) + ")");
        angle_text.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x + 2.0f, sf::Mouse::getPosition(window).y - 16.0f));
        angle_line.setEnd(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
        angle_x.setStart(sf::Vector2f(sf::Mouse::getPosition(window).x, compass.getPosition().y));
        angle_x.setEnd(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
        angle_y.setStart(sf::Vector2f(compass.getPosition().x, sf::Mouse::getPosition(window).y));
        angle_y.setEnd(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            compass.move(sf::Vector2f(-2.0f, 0.0f));
            if (compass.getPosition().x < -20.0f) compass.setPosition(win_x + 20.0f, compass.getPosition().y);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            compass.move(sf::Vector2f(2.0f, 0.0f));
            if (compass.getPosition().x > (win_x + 20.0f)) compass.setPosition(-20.0f, compass.getPosition().y);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            compass.move(sf::Vector2f(0.0f, -2.0f));
            if (compass.getPosition().y < -20.0f) compass.setPosition(compass.getPosition().x, win_y + 20.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            compass.move(sf::Vector2f(0.0f, 2.0f));
            if (compass.getPosition().y > (win_y + 20.0f)) compass.setPosition(compass.getPosition().x, -20.0f);
        }

        compass.setRotation(std::atan2(angle_line.getEndX() - compass.getPosition().x, 
                            compass.getPosition().y - angle_line.getEndY()) * (180 / 3.14159));
        angle_line.setStart(sf::Vector2f(compass.getPosition().x, compass.getPosition().y));

        v_line.setStart(sf::Vector2f(compass.getPosition().x, 0.0f));
        v_line.setEnd(sf::Vector2f(compass.getPosition().x, win_y));
        h_line.setStart(sf::Vector2f(0.0f, compass.getPosition().y));
        h_line.setEnd(sf::Vector2f(win_x, compass.getPosition().y));
        
    ////-----------------------------------------------------------
        window.clear(sf::Color(48, 56, 65));
        if (show_line == true) {
            window.draw(v_line.getLine(), 2, sf::Lines);
            window.draw(h_line.getLine(), 2, sf::Lines);
            window.draw(angle_x.getLine(), 2, sf::Lines);
            window.draw(angle_y.getLine(), 2, sf::Lines);
        }
        window.draw(angle_line.getLine(), 2, sf::Lines);
        window.draw(compass);
        window.draw(axis_x);
        window.draw(axis_y);
        window.draw(angle_text);
        window.display();
    }
}
