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
    sf::RenderWindow window(sf::VideoMode(640, 480), "Angle", sf::Style::Default, sf::ContextSettings(0, 0, 4));
    window.setSize(sf::Vector2u(640, 480));
    window.setFramerateLimit(60);

    auto win_x = window.getSize().x;
    auto win_y = window.getSize().y;

    sf::Font font;
    assert(font.loadFromFile("./assets/font/Consola.TTF"));

////--- Text -------------------------------------------------------
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

////--- Shape ------------------------------------------------------
    sf::CircleShape player(20.f, 3);
    player.setFillColor(sf::Color::Magenta);
    player.setOutlineThickness(2.0f);
    player.setOutlineColor(sf::Color::White);
    player.setOrigin(20.0f, 20.0f);
    player.setPosition(sf::Vector2f(win_x / 2, win_y / 2));

    sf::CircleShape enemy(20.f, 3);
    enemy.setFillColor(sf::Color::Red);
    enemy.setOutlineThickness(2.0f);
    enemy.setOutlineColor(sf::Color::White);
    enemy.setOrigin(20.0f, 20.0f);
    enemy.setPosition(sf::Vector2f(100.0f, 100.0f));

////--- Line -------------------------------------------------------
    Line v_line(sf::Vector2f(player.getPosition().x, 0.0f),
                sf::Vector2f(player.getPosition().x, win_y));
    v_line.setColor(sf::Color(208, 208, 208, 255), sf::Color(208, 208, 208, 255));
    Line h_line(sf::Vector2f(0.0f, player.getPosition().y),
                sf::Vector2f(win_x, player.getPosition().y));
    h_line.setColor(sf::Color(208, 208, 208, 255), sf::Color(208, 208, 208, 255));

    Line angle_line(sf::Vector2f(player.getPosition().x, player.getPosition().y), 
                    sf::Vector2f(0.0f, 0.0f));
    angle_line.setColor(sf::Color(208, 208, 208, 255), sf::Color(50, 208, 254, 255));

    Line angle_x(sf::Vector2f(enemy.getPosition().x, player.getPosition().y),
                 sf::Vector2f(enemy.getPosition().x, enemy.getPosition().y));
    angle_x.setColor(sf::Color(208, 208, 208, 255), sf::Color(50, 208, 254, 255));

    Line angle_y(sf::Vector2f(player.getPosition().x, enemy.getPosition().y),
                 sf::Vector2f(enemy.getPosition().x, enemy.getPosition().y));
    angle_y.setColor(sf::Color(208, 208, 208, 255), sf::Color(50, 208, 254, 255));

    bool show_line = true;

////--- Move Algorithm
    float speed = 0.6f;
    float angle = std::atan2(enemy.getPosition().y - player.getPosition().y,
                             player.getPosition().x - enemy.getPosition().x);
    float x = std::floor((speed * cos(angle)) * 1000) / 1000;
    float y = std::floor((speed * sin(angle)) * 1000) / 1000;

////--- Time
    sf::Clock clock;
    sf::Time elapsed;
    
////--- Loop --------------------------------------------------------
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Key::Space) {
                        show_line = !show_line;
                    }
                    break;
                default:
                    break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.move(-3.0f, 0.0f);
            if (player.getPosition().x < -20.0f) player.setPosition(win_x + 20.0f, player.getPosition().y);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {        
            player.move(3.0f, 0.0f);
            if (player.getPosition().x > (win_x + 20.0f)) player.setPosition(-20.0f, player.getPosition().y);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.move(0.0f, -3.0f);
            if (player.getPosition().y < -20.0f) player.setPosition(player.getPosition().x, win_y + 20.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.move(0.0f, 3.0f);
            if (player.getPosition().y > (win_y + 20.0f)) player.setPosition(player.getPosition().x, -20.0f);
        }

        player.setRotation(std::atan2(angle_line.getEndX() - player.getPosition().x, 
                            player.getPosition().y - angle_line.getEndY()) * (180 / 3.14159));
        enemy.setRotation(std::atan2(player.getPosition().x - enemy.getPosition().x,
                            enemy.getPosition().y - player.getPosition().y) * (180 / 3.14159));

        elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() > 1) {
            enemy.move(0.0f, 0.0f);
            angle = std::atan2(enemy.getPosition().y - player.getPosition().y,
                               player.getPosition().x - enemy.getPosition().x);
            x = std::floor((speed * cos(angle)) * 1000) / 1000;
            y = std::floor((speed * sin(angle)) * 1000) / 1000;
            clock.restart();
        }
        enemy.move(x, -y);
        std::cout << x << ", " << y << ", " << (angle * (180 / 3.14159)) << '\n';

        axis_x.setString("X: " + std::to_string((int)(player.getPosition().x)));
        axis_y.setString("Y: " + std::to_string((int)(player.getPosition().y)));
        angle_text.setString("(" + std::to_string((int)(enemy.getPosition().x - player.getPosition().x)) + ", " +
                                   std::to_string((int)(player.getPosition().y - enemy.getPosition().y)) + ")");
        angle_text.setPosition(sf::Vector2f(enemy.getPosition().x + 4.0f, enemy.getPosition().y - 18.0f));
        angle_line.setEnd(sf::Vector2f(enemy.getPosition().x, enemy.getPosition().y));
        angle_x.setStart(sf::Vector2f(enemy.getPosition().x, player.getPosition().y));
        angle_x.setEnd(sf::Vector2f(enemy.getPosition().x, enemy.getPosition().y));
        angle_y.setStart(sf::Vector2f(player.getPosition().x, enemy.getPosition().y));
        angle_y.setEnd(sf::Vector2f(enemy.getPosition().x, enemy.getPosition().y));
        angle_line.setStart(sf::Vector2f(player.getPosition().x, player.getPosition().y));
        v_line.setStart(sf::Vector2f(player.getPosition().x, 0.0f));
        v_line.setEnd(sf::Vector2f(player.getPosition().x, win_y));
        h_line.setStart(sf::Vector2f(0.0f, player.getPosition().y));
        h_line.setEnd(sf::Vector2f(win_x, player.getPosition().y));

    ////-----------------------------------------------------------
        window.clear(sf::Color(48, 56, 65));
        if (show_line == true) {
            window.draw(v_line.getLine(), 2, sf::Lines);
            window.draw(h_line.getLine(), 2, sf::Lines);
            window.draw(angle_x.getLine(), 2, sf::Lines);
            window.draw(angle_y.getLine(), 2, sf::Lines);
            window.draw(angle_text);
        }
        window.draw(angle_line.getLine(), 2, sf::Lines);
        window.draw(player);
        window.draw(enemy);
        window.draw(axis_x);
        window.draw(axis_y);
        window.display();
    }
}
