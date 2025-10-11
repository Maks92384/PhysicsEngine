#include "PlaneConstraint.hpp"

PlaneConstraint::PlaneConstraint(sf::Vector3f orientation, float offset) : orientation(orientation), offset(offset) {
    type = "plane";
}
PlaneConstraint::PlaneConstraint(sf::Vector3f orientation) : PlaneConstraint(orientation, 0) {}


sf::Vector3f PlaneConstraint::getOrientation() {
    return orientation;
}

float PlaneConstraint::getOffset() {
    return offset;
}


void PlaneConstraint::setOrientation(sf::Vector3f newOrientation) {
    orientation = newOrientation;
}

void PlaneConstraint::setOffset(float newOffset) {
    offset = newOffset;
}