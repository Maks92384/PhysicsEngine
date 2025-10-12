#include "PhysicsObject.hpp"
#include "../Configuration/PhysicsEngineConfiguration.hpp"
#include "3DEngine/Engine3D.hpp"


PhysicsObject::PhysicsObject(sf::Vector3f position, sf::Vector3f hitbox, float mass) : position(position), hitbox(hitbox), mass(mass), velocity({0, 0, 0}), acceleration( {0, 0, 0}), orientation(Quaternion(0, 0, 0, 0)), angularVelocity( {0, 0, 0}), angularAcceleration({0, 0, 0}) {}

PhysicsObject::PhysicsObject(sf::Vector3f position, float mass) : PhysicsObject(position, physicsConf::defaultHitbox,  mass) {}

PhysicsObject::PhysicsObject(sf::Vector3f position, sf::Vector3f hitbox) : PhysicsObject(position, hitbox, 1) {}

PhysicsObject::PhysicsObject(float mass) : PhysicsObject({0, 0, 0}, mass) {}

PhysicsObject::PhysicsObject(sf::Vector3f position) : PhysicsObject(position, 1) {}

PhysicsObject::PhysicsObject() : PhysicsObject(1) {}



void PhysicsObject::applyForce(sf::Vector3f applicationPoint, sf::Vector3f force) {
    forces.push_back({applicationPoint, force});
}

void PhysicsObject::clearForces() {
    forces.clear();
}

vector<array<sf::Vector3f, 2>>& PhysicsObject::getForces() {
    return forces;
}


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

void PhysicsObject::setOrientation(Quaternion newOrientationQuaternion) {
    orientation = newOrientationQuaternion;
}

void PhysicsObject::rotateGlobal(Quaternion rotationQuaternion) {
    orientation = rotationQuaternion.multiply(orientation);
}

void PhysicsObject::rotateLocal(Quaternion rotationQuaternion) {
    orientation = orientation.multiply(rotationQuaternion);
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

Quaternion PhysicsObject::getOrientation() {
    return orientation;
}

sf::Vector3f PhysicsObject::getAngularVelocity() {
    return angularVelocity;
}

sf::Vector3f PhysicsObject::getAngularAcceleration() {
    return angularAcceleration;
}

sf::Vector3f PhysicsObject::getHitbox() {
    return hitbox;
}

vector<sf::Vector3f> PhysicsObject::getCornerPointsUnrotated() {
    vector<sf::Vector3f> cornerPoints;

    cornerPoints.push_back(sf::Vector3f(-hitbox.x / 2, hitbox.y / 2, hitbox.z / 2));
    cornerPoints.push_back(sf::Vector3f(hitbox.x / 2, hitbox.y / 2, hitbox.z / 2));
    cornerPoints.push_back(sf::Vector3f(hitbox.x / 2, hitbox.y / 2, -hitbox.z / 2));
    cornerPoints.push_back(sf::Vector3f(-hitbox.x / 2, hitbox.y / 2, -hitbox.z / 2));
    cornerPoints.push_back(sf::Vector3f(-hitbox.x / 2, -hitbox.y / 2, hitbox.z / 2));
    cornerPoints.push_back(sf::Vector3f(hitbox.x / 2, -hitbox.y / 2, hitbox.z / 2));
    cornerPoints.push_back(sf::Vector3f(hitbox.x / 2, -hitbox.y / 2, -hitbox.z / 2));
    cornerPoints.push_back(sf::Vector3f(-hitbox.x / 2, -hitbox.y / 2, -hitbox.z / 2));

    return cornerPoints;
}

vector<sf::Vector3f> PhysicsObject::getCornerPoints() {
    vector<sf::Vector3f> cornerPoints = getCornerPointsUnrotated();

    for (sf::Vector3f& cornerPoint : cornerPoints) {
        cornerPoint = Quaternion::rotatePoint(cornerPoint, orientation);
    }

    return cornerPoints;
}

array<array<array<sf::Vector3f, 2>, 2>, 2> PhysicsObject::getCornerPointsAs3DArray() {
    array<array<array<sf::Vector3f, 2>, 2>, 2> cornerPoints;

    cornerPoints[0][0][0] = Quaternion::rotatePoint(sf::Vector3f(-hitbox.x / 2, hitbox.y / 2, hitbox.z / 2), orientation);
    cornerPoints[1][0][0] = Quaternion::rotatePoint(sf::Vector3f(hitbox.x / 2, hitbox.y / 2, hitbox.z / 2), orientation);
    cornerPoints[1][0][1] = Quaternion::rotatePoint(sf::Vector3f(hitbox.x / 2, hitbox.y / 2, -hitbox.z / 2), orientation);
    cornerPoints[0][0][1] = Quaternion::rotatePoint(sf::Vector3f(-hitbox.x / 2, hitbox.y / 2, -hitbox.z / 2), orientation);
    cornerPoints[0][1][0] = Quaternion::rotatePoint(sf::Vector3f(-hitbox.x / 2, -hitbox.y / 2, hitbox.z / 2), orientation);
    cornerPoints[1][1][0] = Quaternion::rotatePoint(sf::Vector3f(hitbox.x / 2, -hitbox.y / 2, hitbox.z / 2), orientation);
    cornerPoints[1][1][1] = Quaternion::rotatePoint(sf::Vector3f(hitbox.x / 2, -hitbox.y / 2, -hitbox.z / 2), orientation);
    cornerPoints[0][1][1] = Quaternion::rotatePoint(sf::Vector3f(-hitbox.x / 2, -hitbox.y / 2, -hitbox.z / 2), orientation);

    return cornerPoints;
}


void PhysicsObject::hide() {
    hidden = true;
}

void PhysicsObject::show() {
    hidden = false;
}

bool PhysicsObject::isHidden() {
    return hidden;
}

