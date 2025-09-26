#include "PhysicsEngine.hpp"
#include "../Display/Engine3DIntegration.hpp"

#include <iostream>
#include <cmath>
#include <3DEngine/Engine3D.hpp>

#include "../../../cmake-build-debug/_deps/3dengine-src/src/3DEngine/functions.hpp"

vector<PhysicsObject> PhysicsEngine::physicsObjects;

void PhysicsEngine::update(unsigned int deltaTime) {
    for (PhysicsObject& physicsObject : physicsObjects) {
        physicsObject.setAcceleration({0, 0, 0});
        physicsObject.setAngularAcceleration({0, 0, 0});

        for (const array<sf::Vector3f, 2>& force : physicsObject.getForces()) {
            const sf::Vector3f& forcePoint = Engine3D::rotateWithEulerVector(force[0],physicsObject.getOrientation());  // Point of force application
            //const sf::Vector3f& forceVector = Engine3D::rotateWithEulerVector(force[1],-physicsObject.getOrientation());
            const sf::Vector3f& forceVector = force[1];

            float r = forcePoint.length();

            sf::Vector3f linearForce;

            if (r == 0) {
                linearForce = forceVector;
            } else {
                linearForce = forcePoint * cos(angleBetween(forcePoint, forceVector)) * forceVector.length() / forcePoint.length();

                sf::Vector3f torque = forcePoint.cross(forceVector).normalized() * forceVector.length() * sin(angleBetween(forcePoint, forceVector));
                float momentOfInertia = physicsObject.getMass() / 6;

                physicsObject.setAngularAcceleration(physicsObject.getAngularAcceleration() + torque / momentOfInertia);
            }

            physicsObject.setAcceleration(physicsObject.getAcceleration() + linearForce / physicsObject.getMass());
        }

        physicsObject.setVelocity(physicsObject.getVelocity() + physicsObject.getAcceleration() * (float) deltaTime / 1000000.0f);
        physicsObject.setPosition(physicsObject.getPosition() + physicsObject.getVelocity() * (float) deltaTime / 1000000.0f);

        physicsObject.setAngularVelocity(physicsObject.getAngularVelocity() + physicsObject.getAngularAcceleration() * (float) deltaTime / 1000000.0f);
        physicsObject.setOrientation(physicsObject.getOrientation() + physicsObject.getAngularVelocity() * (float) deltaTime / 1000000.0f);

        physicsObject.clearForces();
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
