#include "Engine3DIntegration.hpp"

#include "../Configuration/PhysicsEngineConfiguration.hpp"
#include "3DEngine/Engine3D.hpp"

unsigned int Engine3DIntegration::objectCount = 0;

void Engine3DIntegration::displayPhysicalObjects(vector<PhysicsObject>& physicsObjects) {
    for (unsigned int i = 0; i < physicsObjects.size(); ++i) {
        if (i + 1 > objectCount) {
            objectCount++;
            Engine3D::loadFromFile("../Models/testBox.obj", "PhysicalObject_" + i);
        }
        Engine3D::getObject("PhysicalObject_" + i).setPosition(physicsObjects[i].getPosition() * physicsConf::distanceScale);
        Engine3D::getObject("PhysicalObject_" + i).setRotation({physicsObjects[i].getOrientation().x, physicsObjects[i].getOrientation().y, physicsObjects[i].getOrientation().z});
    }
}