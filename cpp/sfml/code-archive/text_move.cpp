#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "OMG");
    sf::Font font;
    font.loadFromFile("../font/SuperGame-X3Rz9.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Hello World");
    text.setFillColor(sf::Color::White);
    //text.setOutlineThickness(1.f);
    //text.setOutlineColor(sf::Color::Red);
    // Event
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
              window.close();
            } 
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            text.move(sf::Vector2f(-1.f, 0));
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            text.move(sf::Vector2f(1.f, 0));
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            text.move(sf::Vector2f(0, -1.f));
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            text.move(sf::Vector2f(0, 1.f));
        } else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            text.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        }
        // Display
        window.clear(sf::Color::Black);
        window.draw(text);
        window.display();
    }
}