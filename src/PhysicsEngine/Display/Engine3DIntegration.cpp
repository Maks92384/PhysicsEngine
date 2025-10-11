#include "Engine3DIntegration.hpp"
#include "../Configuration/PhysicsEngineConfiguration.hpp"
#include "3DEngine/Engine3D.hpp"
#include "../Constraints/Constraints.hpp"

#include <cmath>
#include <iostream>
#include <iomanip>

#include "../Constraints/PlaneConstraint.hpp"

unsigned int Engine3DIntegration::objectCount = 0;

void Engine3DIntegration::displayPhysicalObjects(vector<PhysicsObject>& physicsObjects) {
    for (unsigned int i = 0; i < physicsObjects.size(); i++) {
        if (i + 1 > objectCount) {
            objectCount++;
            makeObjectFromHitbox(physicsObjects[i].getHitbox(), "PhysicalObject_" + i);
        }
        Engine3D::getObject("PhysicalObject_" + i).setPosition((physicsObjects[i].getPosition() + Quaternion::rotatePoint(sf::Vector3f{-2, 0, 0}, physicsObjects[i].getOrientation())) * physicsConf::distanceScale);
        Engine3D::getObject("PhysicalObject_" + i).setScale(physicsConf::distanceScale);
        Engine3D::getObject("PhysicalObject_" + i).setRotation(physicsObjects[i].getOrientation().toEulerVector());
    }
}

void Engine3DIntegration::displayConstraints() {
    int i = 0;
    for (const auto& constraint : Constraints::getConstraints()) {
        if ((*constraint).getType() == "plane") {
            makeObjectFromPlane("planeObject_" + i);
        }

        Engine3D::getObject("planeObject_" + i).setPosition(sf::Vector3f(0, -(*dynamic_cast<PlaneConstraint*>(constraint)).getOffset(), 0) * physicsConf::distanceScale);
        Engine3D::getObject("planeObject_" + i).setScale(100);

        i++;
    }
}

void Engine3DIntegration::makeObjectFromHitbox(sf::Vector3f hitbox, string name) {
    vector<sf::Vector3f> points;

    points.push_back(sf::Vector3f(-hitbox.x / 2, hitbox.y / 2, hitbox.z / 2));
    points.push_back(sf::Vector3f(hitbox.x / 2, hitbox.y / 2, hitbox.z / 2));
    points.push_back(sf::Vector3f(hitbox.x / 2, hitbox.y / 2, -hitbox.z / 2));
    points.push_back(sf::Vector3f(-hitbox.x / 2, hitbox.y / 2, -hitbox.z / 2));
    points.push_back(sf::Vector3f(-hitbox.x / 2, -hitbox.y / 2, hitbox.z / 2));
    points.push_back(sf::Vector3f(hitbox.x / 2, -hitbox.y / 2, hitbox.z / 2));
    points.push_back(sf::Vector3f(hitbox.x / 2, -hitbox.y / 2, -hitbox.z / 2));
    points.push_back(sf::Vector3f(-hitbox.x / 2, -hitbox.y / 2, -hitbox.z / 2));

    vector<vector<unsigned int>> faces;

    faces.push_back({0, 1, 2, 3});
    faces.push_back({1, 0, 4, 5});
    faces.push_back({2, 1, 5, 6});
    faces.push_back({3, 2, 6, 7});
    faces.push_back({0, 3, 7, 4});
    faces.push_back({7, 6, 5, 4});

    Engine3D::makeNewObject(name, points, faces, true);
}

void Engine3DIntegration::makeObjectFromPlane(string name) {
    vector<sf::Vector3f> points;

    for (unsigned int i = 0; i <= 10; i++) {
        for (unsigned int j = 0; j <= 10; j++) {
            points.push_back(sf::Vector3f(0.0f - 5 + j, 0.0f, 0.0f - 5 + i));
        }
    }

    vector<vector<unsigned int>> faces;

    for (unsigned int i = 0; i < 10; i++) {
        for (unsigned int j = 0; j < 10; j++) {
            faces.push_back({11 * (i + 1) + j, 11 * (i + 1) + j + 1, 11 * i + j + 1, 11 * i + j});
        }
    }


    Engine3D::makeNewObject(name, points, faces, true);
}