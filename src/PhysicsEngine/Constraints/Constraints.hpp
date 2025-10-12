#pragma once

#include "ConstraintTemplate.hpp"
#include "PlaneConstraint.hpp"
#include "../Object/PhysicsObject.hpp"

using namespace std;

class Constraints {
    static vector<ConstraintTemplate*> constraints;
public:
    static void constrain(PhysicsObject& physicsObject);

    static void applyPlaneConstraint(PhysicsObject& physicsObject, const PlaneConstraint& planeConstraint);

    static void addPlaneConstraint(Quaternion orientation, float offset);
    static void addPlaneConstraint(Quaternion orientation);
    static void addPlaneConstraint(float offset);
    static void addPlaneConstraint();

    static vector<ConstraintTemplate*> getConstraints();
};
