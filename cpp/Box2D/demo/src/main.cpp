#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include <string>

#define lineRef 400.f
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "window");
    window.setFramerateLimit(60);
    sf::Font font;
    font.loadFromFile("../font/CONSOLA.TTF");
    sf::Text text_gnd;
    text_gnd.setFont(font);
    text_gnd.setString("400");
    text_gnd.setCharacterSize(14);
    text_gnd.setFillColor(sf::Color::White);

    sf::Vertex line_1[] = {
        sf::Vertex(sf::Vector2f(0.f, lineRef)),
        sf::Vertex(sf::Vector2f(800.f, lineRef))
    };

    sf::RectangleShape gndBox(sf::Vector2f(800.f, 200.f));
    gndBox.setFillColor(sf::Color(255,178,102,40));
    gndBox.setOutlineThickness(1.f);
    
    sf::RectangleShape box_1(sf::Vector2f(40.f, 40.f));
    box_1.setFillColor(sf::Color(192,192,192,90));
    box_1.setOutlineThickness(1.f);
    box_1.setOutlineColor(sf::Color::Magenta);
    
    sf::RectangleShape box_2(sf::Vector2f(40.f, 40.f));
    box_2.setFillColor(sf::Color(192,192,192,90));
    box_2.setOutlineThickness(1.f);
    box_2.setOutlineColor(sf::Color::Magenta);

    b2Vec2 gravity(0.f, 10.f);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(400.0f, 500.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(400.f, 100.f);
    groundBody->CreateFixture(&groundBox, 1.0f);

    b2BodyDef bodyDef;
    bodyDef.bullet = true;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(400.0f, 20.0f);
    b2Body* body = world.CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(20.0f, 20.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.restitution = 0.8f;
    fixtureDef.density = 2.0f;
    fixtureDef.friction = 0.5f;
    body->CreateFixture(&fixtureDef);
    
    b2BodyDef body2Def;
    body2Def.bullet = true;
    body2Def.type = b2_dynamicBody;
    body2Def.position.Set(400.0f, 80.0f);
    b2Body* body2 = world.CreateBody(&body2Def);
    b2PolygonShape dynamicBox2;
    dynamicBox2.SetAsBox(20.0f, 20.0f);
    b2FixtureDef fixture2Def;
    fixture2Def.shape = &dynamicBox2;
    fixture2Def.restitution = 0.8f;
    fixture2Def.density = 4.0f;
    fixture2Def.friction = 0.5f;
    body2->CreateFixture(&fixture2Def);

    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    body2->SetTransform(b2Vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), body2->GetAngle());
                }
            }
        }
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();
        b2Vec2 position2 = body2->GetPosition();
        //float angle = body->GetAngle();
        //printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
        
        text_gnd.setPosition(500.f, 400.1f);
        box_1.setPosition(position.x - 20.f, position.y - 20.f);
        box_2.setPosition(position2.x - 20.f, position2.y - 20.f);
        gndBox.setPosition(0.f, 400.f);

        // Display
        window.clear(sf::Color::Black);
        window.draw(line_1, 2, sf::Lines);
        window.draw(text_gnd);
        window.draw(box_1);
        window.draw(box_2);
        window.draw(gndBox);
        window.display();
    }
    return 0;
}