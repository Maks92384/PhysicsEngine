#pragma once
#include "ConstraintTemplate.hpp"
#include "../Math/Quaternion.hpp"
#include <SFML/Graphics.hpp>

class PlaneConstraint : public ConstraintTemplate {
    Quaternion orientation; // A Quaternion describing plane direction
    float offset; // distance from world center in meters
public:
    PlaneConstraint(Quaternion orientation, float offset);
    PlaneConstraint(Quaternion orientation);
    PlaneConstraint(float offset);
    PlaneConstraint();

    Quaternion getOrientation() const;
    float getOffset() const;

    void setOrientation(Quaternion newOrientation);
    void setOffset(float newOffset);
};
