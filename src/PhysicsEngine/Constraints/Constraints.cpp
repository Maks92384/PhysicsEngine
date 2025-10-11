#include "Constraints.hpp"
#include <cmath>
#include "PlaneConstraint.hpp"

vector<ConstraintTemplate*> Constraints::constraints;

void Constraints::constrain(PhysicsObject& physicsObject) {
    for (const auto& constraint : constraints) {
        if ((*constraint).getType() == "plane") {
            //if (physicsObject.getPosition().y < 0.0f - (*dynamic_cast<PlaneConstraint*>(constraint)).getOffset() + 2 * cos(physicsObject.getOrientation().z)) {
                //physicsObject.setOrientation({0, 0, -acos((physicsObject.getPosition().y + 1) / 2)});
            //}
        }
    }
}

void Constraints::addPlaneConstraint(sf::Vector3f orientation, float offset) {
    constraints.push_back(new PlaneConstraint(orientation, offset));
}

void Constraints::addPlaneConstraint(sf::Vector3f orientation) {
    constraints.push_back(new PlaneConstraint(orientation));
}

vector<ConstraintTemplate*> Constraints::getConstraints() {
    return constraints;
}