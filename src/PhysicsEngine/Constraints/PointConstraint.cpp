#include "PointConstraint.hpp"

PointConstraint::PointConstraint(sf::Vector3f coordinates) : coordinates(coordinates) {
    type = "point";
}

void PointConstraint::setCoordinates(sf::Vector3f coordinates) {
    this->coordinates = coordinates;
}

sf::Vector3f PointConstraint::getCoordinates() const {
    return coordinates;
}