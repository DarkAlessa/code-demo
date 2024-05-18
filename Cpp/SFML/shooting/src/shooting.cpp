#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
//#define NDEBUG
#include <cassert>

#define bulletShape_x   4.f
#define bulletShape_y   6.f
#define bulletSize      sf::Vector2f(bulletShape_x, bulletShape_y)
#define bulletVelocity  10.f
#define playerMoveSpeed 4.f

class Bullet {
public:
    sf::RectangleShape bulletShape;
    Bullet() : bulletShape(bulletSize) {
        bulletShape.setFillColor(sf::Color::Red);
    }
};

class Enemy {
public:
    sf::RectangleShape enemy;
    Enemy() : enemy(sf::Vector2f(20.f, 20.f)) {
        enemy.setFillColor(sf::Color::Magenta);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 600), "Shooting");
    window.setFramerateLimit(60);

    // Player
    sf::RectangleShape player(sf::Vector2f(10.f, 10.f));
    player.setFillColor(sf::Color::Green);
    player.setPosition((window.getSize().x / 2) - 5.f, window.getSize().y - 10.f);
    sf::Vector2f playerPosition;

    // Shooting sound
    sf::SoundBuffer shootBuffer;
    assert(shootBuffer.loadFromFile("./assets/sfx/laser.wav") == true);
    sf::Sound sound;
    sound.setBuffer(shootBuffer);
    sound.setVolume(10.f);

    // Collision sound
    sf::SoundBuffer collBuffer;
    assert(collBuffer.loadFromFile("./assets/sfx/ball_tap.wav") == true);
    sf::Sound collSound;
    collSound.setBuffer(collBuffer);
    collSound.setVolume(10.f);

    // Enemy
    Enemy em;
    std::vector<Enemy> enemyTile;

    // Bullet
    Bullet bullet;
    std::vector<Bullet> magazine;

    // Seed
    int x_pos;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<std::mt19937::result_type> dist;

    sf::Clock clock;
    sf::Time time;
    sf::Event event;

    while (window.isOpen()) {
        playerPosition = player.getPosition();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    bullet.bulletShape.setPosition(playerPosition.x + 3.25f, window.getSize().y - 6.f);
                    magazine.push_back(bullet);
                    sound.play();
                }
            } 
        }

        time = clock.getElapsedTime();
        if (time.asMilliseconds() > 800) {
            x_pos = dist(gen) % 380;
            em.enemy.setPosition(x_pos, -20.f);
            enemyTile.push_back(em);
            clock.restart();
        }

        // Enemy move
        for (size_t i = 0; i < enemyTile.size(); i++) {
            enemyTile[i].enemy.move(sf::Vector2f(0.f, 0.8f));
            if (enemyTile[i].enemy.getPosition().y > window.getSize().y) {
                enemyTile.erase(enemyTile.begin() + i);
            }
        }

        // Shooting 
        for (size_t i = 0; i < magazine.size(); i++) {
            magazine[i].bulletShape.move(sf::Vector2f(0, -bulletVelocity));
            if (magazine[i].bulletShape.getPosition().y < 0) {
                magazine.erase(magazine.begin() + i);
            } else { // Enemy collision
                for (size_t k = 0; k < enemyTile.size(); k++) {
                    if (magazine[i].bulletShape.getGlobalBounds().intersects(enemyTile[k].enemy.getGlobalBounds())) {
                        collSound.play();
                        magazine.erase(magazine.begin() + i);
                        enemyTile.erase(enemyTile.begin() + k);
                        break;
                    }
                }
            }
        }

        // Player move
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.move(sf::Vector2f(-playerMoveSpeed, 0));
            if (playerPosition.x <= 0) {
                player.setPosition(0, (window.getSize().y - 10.f));
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.move(sf::Vector2f(playerMoveSpeed, 0));
            if (playerPosition.x >= (window.getSize().x - 10.f)) {
                player.setPosition((window.getSize().x - 10.f), (window.getSize().y - 10.f));
            }
        }

        // Display
        window.clear(sf::Color::Black);
        window.draw(player);

        for (const auto& et : enemyTile) {
            window.draw(et.enemy);
        }

        for (const auto& mz : magazine) {
            window.draw(mz.bulletShape);
        }

        window.display();
    }
}