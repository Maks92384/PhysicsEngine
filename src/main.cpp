#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "configuration.hpp"
#include "events.hpp"
#include "../cmake-build-debug/_deps/3dengine-src/src/3DEngine/functions.hpp"
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

    PhysicsObject& object = PhysicsEngine::createObject({2, (float) sqrt(2) + 1.0f / (float) sqrt(2), 0});

    object.setOrientation({0, 0, -M_PI / 4});

    while (window.isOpen()) {
        clock.restart();

        manageEvents(window);

        object.applyForce({0, 0, 0}, {0, -1, 0});
        //object.applyForce({0, -2, 0},  {0, 1 / (1 - 3 * (float) pow(cos(M_PI / 2 + object.getOrientation().z), 2)), 0});

        /*  ROCKET SIMULATOR

        object.applyForce({0, 0, 0}, {0, -1, 0});

        sf::Vector3f rocketEngineDirection = {0, 0, 0};
        sf::Vector3f rocketEngineForce = {0, 0, 0};
        float rocketEnginePower = 1.5;
        float rocketEngineGimbalAngle = M_PI / 12;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            rocketEngineDirection += {1, 0, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            rocketEngineDirection += {-1, 0, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            rocketEngineDirection += {0, 0, 1};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            rocketEngineDirection += {0, 0, -1};
        if (rocketEngineDirection.length() != 0)
            rocketEngineDirection = rocketEngineDirection.normalized() * sin(rocketEngineGimbalAngle) * rocketEnginePower;
        rocketEngineForce = {rocketEngineDirection.x, cos(rocketEngineGimbalAngle) * rocketEnginePower, rocketEngineDirection.z};

        object.applyForce({0, -2, 0}, Engine3D::rotateWithEulerVector(rocketEngineForce, object.getOrientation()));
        */


        /*
        0.388229 1.44889 0
        cout<<"-----------------------------------"<<endl;
        -0.388229 1.39952 0.375
        cout<<rocketEngine.x<<" "<<rocketEngine.y<<" "<<rocketEngine.z<<endl;
        cout<<object.getVelocity().x<<" "<<object.getVelocity().y<<" "<<object.getVelocity().z<<endl;
        cout<<object.getOrientation().x<<endl;
        */

        if (object.getOrientation().z > -M_PI / 2)
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