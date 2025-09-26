#pragma once

#include "../Object/PhysicsObject.hpp"

using namespace std;

class Engine3DIntegration {
    static unsigned int objectCount;
public:
    static void displayPhysicalObjects(vector<PhysicsObject>& physicsObjects);
};
