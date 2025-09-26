#include "PhysicsObject.hpp"


PhysicsObject::PhysicsObject(sf::Vector3f position, float mass) : mass(mass), position(position), velocity({0, 0, 0}), acceleration( {0, 0, 0}), angularVelocity( {0, 0, 0}), angularAcceleration({0, 0, 0}) {}

PhysicsObject::PhysicsObject(float mass) : PhysicsObject({0, 0, 0}, mass) {}

PhysicsObject::PhysicsObject(sf::Vector3f position) : PhysicsObject(position, 1) {}

PhysicsObject::PhysicsObject() : PhysicsObject({0, 0, 0}, 1) {}

void PhysicsObject::setMass(float newMass) {
    mass = newMass;
}

void PhysicsObject::setPosition(sf::Vector3f newPosition) {
    position = newPosition;
}

void PhysicsObject::setVelocity(sf::Vector3f newVelocity) {
    velocity = newVelocity;
}

void PhysicsObject::setAcceleration(sf::Vector3f newAcceleration) {
    acceleration = newAcceleration;
}

void PhysicsObject::setOrientation(sf::Vector3f newOrientation) {
    orientation = newOrientation;
}

void PhysicsObject::setAngularVelocity(sf::Vector3f newVelocity) {
    angularVelocity = newVelocity;
}

void PhysicsObject::setAngularAcceleration(sf::Vector3f newVelocity) {
    angularAcceleration = newVelocity;
}

float PhysicsObject::getMass() {
    return mass;
}

sf::Vector3f PhysicsObject::getPosition() {
    return position;
}

sf::Vector3f PhysicsObject::getVelocity() {
    return velocity;
}

sf::Vector3f PhysicsObject::getAcceleration() {
    return acceleration;
}

sf::Vector3f PhysicsObject::getOrientation() {
    return orientation;
}

sf::Vector3f PhysicsObject::getAngularVelocity() {
    return angularVelocity;
}

sf::Vector3f PhysicsObject::getAngularAcceleration() {
    return angularAcceleration;
}

void PhysicsObject::hide() {
    hidden = true;
}

void PhysicsObject::show() {
    hidden = false;
}
