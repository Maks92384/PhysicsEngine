#pragma once

#include "../Object/PhysicsObject.hpp"

using namespace std;

class Engine3DIntegration {
    static unsigned int objectCount;
    static void makeObjectFromHitbox(sf::Vector3f hitbox, string name);
    static void makeObjectFromPlane(string name);
public:
    static void displayPhysicalObjects(vector<PhysicsObject>& physicsObjects);
    static void displayConstraints();
};
