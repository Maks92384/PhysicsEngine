#pragma once
#include "ConstraintTemplate.hpp"
#include "SFML/Graphics.hpp"

class PointConstraint : public ConstraintTemplate {
    sf::Vector3f coordinates;
public:
    PointConstraint(sf::Vector3f coordinates);

    void setCoordinates(sf::Vector3f coordinates);
    sf::Vector3f getCoordinates() const;
};
