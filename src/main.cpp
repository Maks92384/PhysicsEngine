#include <SFML/Graphics.hpp>
#include "configuration.hpp"
#include "events.hpp"
#include "3DEngine/Camera.hpp"
#include "3DEngine/Engine3D.hpp"

using namespace std;

int main() {
    auto window = sf::RenderWindow(sf::VideoMode(conf::window_size), "PhysicsEngine", sf::State::Fullscreen);
    window.setFramerateLimit(conf::maxFps);
    window.setMouseCursorVisible(false);
    sf::Mouse::setPosition(static_cast<sf::Vector2i>(conf::window_size) / 2);

    while (window.isOpen())
    {
        manageEvents(window);


        Camera::updateCamera(window);
        Engine3D::render();


        window.clear(sf::Color(100, 100, 100));

        Engine3D::draw(window);

        window.display();
    }
}