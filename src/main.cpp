#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <iomanip>

#include "configuration.hpp"
#include "events.hpp"
#include "../cmake-build-debug/_deps/3dengine-src/src/3DEngine/functions.hpp"
#include "3DEngine/Camera.hpp"
#include "3DEngine/Engine3D.hpp"
#include "PhysicsEngine/Constraints/Constraints.hpp"
#include "PhysicsEngine/Core/PhysicsEngine.hpp"
#include "PhysicsEngine/Math/Quaternion.hpp"

using namespace std;

int main() {
    auto window = sf::RenderWindow(sf::VideoMode(conf::window_size), "PhysicsEngine", sf::State::Fullscreen);
    window.setFramerateLimit(conf::maxFps);
    window.setMouseCursorVisible(false);
    sf::Mouse::setPosition(static_cast<sf::Vector2i>(conf::window_size) / 2);
    Engine3D::enableDebugMode();
    Camera::setRotation({0, 0, 0});
    Camera::setPosition({0, 0, 1000});

    sf::Clock clock;
    unsigned int deltaTime = 0; // Time between frames in microseconds

    PhysicsObject& object = PhysicsEngine::createObject({0, 0, 0});

    //object.setAngularVelocity({-20, 0, 0});

    while (window.isOpen()) {
        clock.restart();

        manageEvents(window);

        // Moment of inertia DEMO

        //object.applyForce({-2, 0, 0}, {0, -10, 0});
        //object.applyForce({2, 0, 0}, {0, 10, 0});

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