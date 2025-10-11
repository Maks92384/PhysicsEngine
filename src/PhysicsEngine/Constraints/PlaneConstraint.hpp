#pragma once
#include "ConstraintTemplate.hpp"
#include <SFML/Graphics.hpp>

class PlaneConstraint : public ConstraintTemplate {
    sf::Vector3f orientation; // euler vector
    float offset;
public:
    PlaneConstraint(sf::Vector3f orientation, float offset);
    PlaneConstraint(sf::Vector3f orientation);

    sf::Vector3f getOrientation();
    float getOffset();

    void setOrientation(sf::Vector3f newOrientation);
    void setOffset(float newOffset);
};
