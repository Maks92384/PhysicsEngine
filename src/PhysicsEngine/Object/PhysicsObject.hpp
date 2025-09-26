#pragma once

#include <SFML/Graphics.hpp>

class PhysicsObject {
    float mass; // in kg

    sf::Vector3f position; // in meters, Center of mass
    sf::Vector3f velocity; // in meters per second
    sf::Vector3f acceleration; // in meters per second squared

    sf::Vector3f orientation;
    sf::Vector3f angularVelocity; // in radians per second
    sf::Vector3f angularAcceleration; // in radians per second squared

    bool hidden = false;
public:
    PhysicsObject(sf::Vector3f position, float mass);
    PhysicsObject(float mass);
    PhysicsObject(sf::Vector3f position);
    PhysicsObject();

    void setMass(float newMass);
    void setPosition(sf::Vector3f newPosition);
    void setVelocity(sf::Vector3f newVelocity);
    void setAcceleration(sf::Vector3f newAcceleration);
    void setOrientation(sf::Vector3f newOrientation);
    void setAngularVelocity(sf::Vector3f newAngularVelocity);
    void setAngularAcceleration(sf::Vector3f newAngularAcceleration);

    float getMass();
    sf::Vector3f getPosition();
    sf::Vector3f getVelocity();
    sf::Vector3f getAcceleration();
    sf::Vector3f getOrientation();
    sf::Vector3f getAngularVelocity();
    sf::Vector3f getAngularAcceleration();

    void hide();
    void show();
};