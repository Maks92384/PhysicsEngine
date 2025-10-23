#pragma once

#include "ConstraintTemplate.hpp"
#include "PlaneConstraint.hpp"
#include "PointConstraint.hpp"
#include "../Object/PhysicsObject.hpp"

using namespace std;

class Constraints {
    static vector<ConstraintTemplate*> constraints;
public:
    static void constrain(PhysicsObject& physicsObject, unsigned int deltaTime);

    static void applyPlaneConstraint(PhysicsObject& physicsObject, const PlaneConstraint& planeConstraint);
    static void applyPointConstraint(PhysicsObject& physicsObject, unsigned int deltaTime);

    static void addPlaneConstraint(Quaternion orientation, float offset);
    static void addPlaneConstraint(Quaternion orientation);
    static void addPlaneConstraint(float offset);
    static void addPlaneConstraint();
    static void addPointConstraint(PhysicsObject& physicsObject, sf::Vector3f coordinates);

    static vector<ConstraintTemplate*> getConstraints();
};
