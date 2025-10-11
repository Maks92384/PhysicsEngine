#pragma once

#include "ConstraintTemplate.hpp"
#include "../Object/PhysicsObject.hpp"

using namespace std;

class Constraints {
    static vector<ConstraintTemplate*> constraints;
public:
    static void constrain(PhysicsObject& physicsObject);

    static void addPlaneConstraint(sf::Vector3f orientation, float offset);
    static void addPlaneConstraint(sf::Vector3f orientation);

    static vector<ConstraintTemplate*> getConstraints();
};
