#include "PhysicsEngine.hpp"
#include "../Display/Engine3DIntegration.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>
#include <3DEngine/Engine3D.hpp>
#include <3DEngine/functions.hpp>
#include "../Constraints/Constraints.hpp"

vector<PhysicsObject> PhysicsEngine::physicsObjects;

void PhysicsEngine::update(unsigned int deltaTime) {
    for (PhysicsObject& physicsObject : physicsObjects) {
        physicsObject.setAcceleration({0, 0, 0});
        physicsObject.setAngularAcceleration({0, 0, 0});

        sf::Vector3f netForce = {0, 0, 0};

        for (const array<sf::Vector3f, 2>& force : physicsObject.getForces()) {
            const sf::Vector3f& forcePoint = Quaternion::rotatePoint(force[0] - physicsObject.getRotationAxisShift(), physicsObject.getOrientation());  // Point of force application
            const sf::Vector3f& forceVector = force[1];

            netForce += forceVector;

            if (forceVector.length() == 0)
                break;

            /*
            sf::Vector3f test = {0, 1, 0};
            sf::Vector3f test2 = {0.0000000000000001, 9.99999999999999234, 0};
            cout<<test.cross(test2).x<<" "<<test.cross(test2).y<<" "<<test.cross(test2).z<<endl;
            cout<<test.cross(test2).normalized().x<<" "<<test.cross(test2).normalized().y<<" "<<test.cross(test2).normalized().z<<endl;
            */
            /*
            cout<<"-------------------------------------------------------------"<<endl;
            cout<<forcePoint.x<<" "<<forcePoint.y<<" "<<forcePoint.z<<endl;
            cout<<forceVector.x<<" "<<forceVector.y<<" "<<forceVector.z<<endl;
            cout<<setprecision(20)<<forcePoint.dot(forceVector) / forcePoint.length() / forceVector.length()<<endl;
            cout<<!isnan(angleBetween(forcePoint, forceVector))<<endl;
            cout<<(angleBetween(forcePoint, forceVector) != (float) M_PI)<<endl;
            cout<<acos(forcePoint.dot(forceVector) / forcePoint.length() / forceVector.length())<<endl;
            cout<<angleBetween(forcePoint, forceVector)<<endl;
            cout<<(float) M_PI<<endl;
            cout<<M_PI<<endl;
            */

            if (!isnan(angleBetween(forcePoint, forceVector)) && forcePoint.cross(forceVector).length() > 0) {
                /*
                cout<<"-----"<<endl;
                cout<<forcePoint.x<<" "<<forcePoint.y<<" "<<forcePoint.z<<endl;
                cout<<forceVector.x<<" "<<forceVector.y<<" "<<forceVector.z<<endl;
                cout<<forcePoint.cross(forceVector).x<<" "<<forcePoint.cross(forceVector).y<<" "<<forcePoint.cross(forceVector).z<<endl;
                cout<<forcePoint.cross(forceVector).normalized().x<<" "<<forcePoint.cross(forceVector).normalized().y<<" "<<forcePoint.cross(forceVector).normalized().z<<endl;
                */

                sf::Vector3f torque = forcePoint.cross(forceVector).normalized() * forcePoint.length() * forceVector.length() * sin(angleBetween(forcePoint, forceVector));

                float momentOfInertia = physicsObject.getMass() * (5.0f / 3 + (float) pow(physicsObject.getRotationAxisShift().length(), 2));

                if (momentOfInertia != 0)
                    physicsObject.setAngularAcceleration(physicsObject.getAngularAcceleration() + torque / momentOfInertia);
            }
        }

        if (physicsObject.getMass() != 0)
            physicsObject.setAcceleration(physicsObject.getAcceleration() + netForce / physicsObject.getMass());

        physicsObject.setVelocity(physicsObject.getVelocity() + physicsObject.getAcceleration() * (float) deltaTime / 1000000.0f);

        //physicsObject.setAngularAcceleration({0, 0, -10});
        physicsObject.setAngularVelocity(physicsObject.getAngularVelocity() + physicsObject.getAngularAcceleration() * (float) deltaTime / 1000000.0f);


        Constraints::constrain(physicsObject, deltaTime);


        physicsObject.setPosition(physicsObject.getPosition() + physicsObject.getVelocity() * (float) deltaTime / 1000000.0f);

        sf::Vector3f rotationDirection = physicsObject.getAngularVelocity().length() != 0 ? physicsObject.getAngularVelocity().normalized() : sf::Vector3f(0, 0, 0);
        physicsObject.rotateGlobal(Quaternion(physicsObject.getAngularVelocity().length() * (float) deltaTime / 1000000.0f, rotationDirection.x, rotationDirection.y, rotationDirection.z));

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
    Engine3DIntegration::displayConstraints();
}
