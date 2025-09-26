#include <SFML/Graphics.hpp>
#include <cmath>
#include "configuration.hpp"
#include "events.hpp"
#include "3DEngine/Camera.hpp"
#include "3DEngine/Engine3D.hpp"
#include "PhysicsEngine/Core/PhysicsEngine.hpp"

using namespace std;

int main() {
    auto window = sf::RenderWindow(sf::VideoMode(conf::window_size), "PhysicsEngine", sf::State::Fullscreen);
    window.setFramerateLimit(conf::maxFps);
    window.setMouseCursorVisible(false);
    sf::Mouse::setPosition(static_cast<sf::Vector2i>(conf::window_size) / 2);
    Engine3D::enableDebugMode();

    sf::Clock clock;
    unsigned int deltaTime = 0; // Time between frames in microseconds

    PhysicsObject& object = PhysicsEngine::createObject({0, 0, 0});


    while (window.isOpen())
    {
        clock.restart();

        manageEvents(window);

        object.applyForce({0, 0, 0}, {0, -0.1, 0});
        object.applyForce({1, 0, 0}, {0, 0.2, 0});

        PhysicsEngine::update(deltaTime);
        PhysicsEngine::show();

        Camera::updateCamera(window);
        Engine3D::render();

        window.clear(sf::Color(100, 100, 100));

        Engine3D::draw(window);

        window.display();
        deltaTime = clock.getElapsedTime().asMicroseconds();
    }
}