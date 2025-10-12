#include "PlaneConstraint.hpp"

PlaneConstraint::PlaneConstraint(Quaternion orientation, float offset) : orientation(orientation), offset(offset) {
    type = "plane";
}
PlaneConstraint::PlaneConstraint(Quaternion orientation) : PlaneConstraint(orientation, 0) {}

PlaneConstraint::PlaneConstraint(float offset) : PlaneConstraint(Quaternion(0, 0, 0, 0), offset) {}

PlaneConstraint::PlaneConstraint() : PlaneConstraint(0) {}


Quaternion PlaneConstraint::getOrientation() const {
    return orientation;
}

float PlaneConstraint::getOffset() const {
    return offset;
}


void PlaneConstraint::setOrientation(Quaternion newOrientation) {
    orientation = newOrientation;
}

void PlaneConstraint::setOffset(float newOffset) {
    offset = newOffset;
}