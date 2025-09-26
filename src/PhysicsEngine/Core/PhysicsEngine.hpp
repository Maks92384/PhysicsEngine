#pragma once

#include "../Object/PhysicsObject.hpp"

using namespace std;

class PhysicsEngine {
    static vector<PhysicsObject> physicsObjects;
public:
    static void update(float deltaTime);
    static PhysicsObject& createObject(sf::Vector3f position);
    static PhysicsObject& createObject();

    static void show();
};
