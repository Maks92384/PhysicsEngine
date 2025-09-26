#include "PhysicsEngine.hpp"
#include "../Display/Engine3DIntegration.hpp"

#include <iostream>

vector<PhysicsObject> PhysicsEngine::physicsObjects;

void PhysicsEngine::update(float deltaTime) {
    for (PhysicsObject& physicsObject : physicsObjects) {
    }
}

PhysicsObject& PhysicsEngine::createObject(sf::Vector3f position) {
    physicsObjects.push_back(PhysicsObject(position));
    return physicsObjects.back();
}

PhysicsObject& PhysicsEngine::createObject() {
    return createObject({0, 0, 0});
}

void PhysicsEngine::show() {
    Engine3DIntegration::displayPhysicalObjects(physicsObjects);
}
