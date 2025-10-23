#include "Constraints.hpp"
#include <cmath>
#include <iostream>

#include "PlaneConstraint.hpp"
#include "../../../cmake-build-debug/_deps/3dengine-src/src/3DEngine/functions.hpp"

vector<ConstraintTemplate*> Constraints::constraints;

void Constraints::constrain(PhysicsObject& physicsObject, unsigned int deltaTime) {
    physicsObject.setRotationAxisShift({0, 0, 0});

    applyPointConstraint(physicsObject, physicsObject.getPointConstraints(), deltaTime);

    for (const auto& constraint : constraints) {
        if ((*constraint).getType() == "plane") {
            applyPlaneConstraint(physicsObject, *dynamic_cast<PlaneConstraint*>(constraint));
        }
    }
}

void Constraints::applyPlaneConstraint(PhysicsObject& physicsObject, const PlaneConstraint& planeConstraint) {
    array<array<array<sf::Vector3f, 2>, 2>, 2> cornerPoints = physicsObject.getCornerPointsAs3DArray();

    for (unsigned int i = 0; i < 8; i++) {
        cornerPoints[(i>>2)%2][(i>>1)%2][i%2] = Quaternion::unRotatePoint(cornerPoints[(i>>2)%2][(i>>1)%2][i%2], planeConstraint.getOrientation());
    }

    sf::Vector3f lowestPoint = cornerPoints[0][0][0];
    array<int, 3> lowestPointIndex = {0, 0, 0};

    for (int i = 0; i < 8; i++) {
        if (cornerPoints[(i>>2)%2][(i>>1)%2][i%2].y < lowestPoint.y) {
            lowestPoint = cornerPoints[(i>>2)%2][(i>>1)%2][i%2];
            lowestPointIndex = {(i>>2)%2, (i>>1)%2, i%2};
        }
    }

    sf::Vector3f objectVelocity = Quaternion::unRotatePoint(physicsObject.getVelocity(), planeConstraint.getOrientation());
    sf::Vector3f objectPosition = Quaternion::unRotatePoint(physicsObject.getPosition(), planeConstraint.getOrientation());

    if (lowestPoint.y + objectPosition.y > planeConstraint.getOffset())
        return;

    float length = lowestPoint.length(); // distance from the center of mass to the lowest corner

    if (length == 0)
        return;


    float distance = objectPosition.y - planeConstraint.getOffset(); // distance from the center of mass to the plane constraint

    float minimumDistance = 0;

    //---------solving minimum distance----------

    sf::Vector3f lowestPointCopy = lowestPoint;
    sf::Vector3f neighborPointX = cornerPoints[1 - lowestPointIndex[0]][lowestPointIndex[1]][lowestPointIndex[2]] - lowestPoint;
    sf::Vector3f neighborPointY = cornerPoints[lowestPointIndex[0]][1 - lowestPointIndex[1]][lowestPointIndex[2]] - lowestPoint;
    sf::Vector3f neighborPointZ = cornerPoints[lowestPointIndex[0]][lowestPointIndex[1]][1 - lowestPointIndex[2]] - lowestPoint;

    neighborPointX.y = neighborPointY.y = neighborPointZ.y = lowestPointCopy.y = 0;

    if (lowestPointCopy.length() == 0)
        minimumDistance = length;
    else if (neighborPointX.length() == 0)
        minimumDistance = physicsObject.getHitbox().x / 2;
    else if (neighborPointY.length() == 0)
        minimumDistance = physicsObject.getHitbox().y / 2;
    else if (neighborPointZ.length() == 0)
        minimumDistance = physicsObject.getHitbox().z / 2;
    else {
        float angleToX = angleBetween(-lowestPointCopy, neighborPointX);
        float angleToY = angleBetween(-lowestPointCopy, neighborPointY);
        float angleToZ = angleBetween(-lowestPointCopy, neighborPointZ);

        if (angleToX > angleToY && angleToX > angleToZ)
            minimumDistance = physicsObject.getHitbox().x / 2;
        else if (angleToY > angleToX && angleToY > angleToZ) {
            minimumDistance = physicsObject.getHitbox().y / 2;
        }
        else if (angleToZ > angleToX && angleToZ > angleToY)
            minimumDistance = physicsObject.getHitbox().z / 2;
        else if (angleToX == angleToY)
            minimumDistance = sqrt(pow(physicsObject.getHitbox().x / 2, 2) + pow(physicsObject.getHitbox().y / 2, 2));
        else if (angleToY == angleToZ)
            minimumDistance = sqrt(pow(physicsObject.getHitbox().y / 2, 2) + pow(physicsObject.getHitbox().z / 2, 2));
        else if (angleToX == angleToZ)
            minimumDistance = sqrt(pow(physicsObject.getHitbox().x / 2, 2) + pow(physicsObject.getHitbox().z / 2, 2));

    }

    //-------------------------------------------

    if (distance <= minimumDistance) {
        distance = minimumDistance;
        objectVelocity.y = 0;
        objectPosition.y = planeConstraint.getOffset() + minimumDistance;
    }

    physicsObject.setVelocity(Quaternion::rotatePoint(objectVelocity, planeConstraint.getOrientation()));
    physicsObject.setPosition(Quaternion::rotatePoint(objectPosition, planeConstraint.getOrientation()));


    float targetAngle;

    if (abs(distance / length) <= 1)
        targetAngle = acos(distance / length);
    else
        targetAngle = 0;


    sf::Vector3f distanceVector = {0, -distance, 0};

    float currentAngle = angleBetween(distanceVector, lowestPoint);
    float rotationAngle = targetAngle - currentAngle;

    sf::Vector3f rotationAxis = Quaternion::rotatePoint(distanceVector.cross(lowestPoint), planeConstraint.getOrientation());

    //physicsObject.setAngularVelocity(rotationAxis.normalized() * rotationAngle * 144.0f);
    physicsObject.rotateGlobal(Quaternion(rotationAngle, rotationAxis.x, rotationAxis.y, rotationAxis.z));

    // ---------------other axis correction-------------------

    cornerPoints = physicsObject.getCornerPointsAs3DArray();

    for (unsigned int i = 0; i < 8; i++) {
        cornerPoints[(i>>2)%2][(i>>1)%2][i%2] = Quaternion::unRotatePoint(cornerPoints[(i>>2)%2][(i>>1)%2][i%2], planeConstraint.getOrientation());
    }

    lowestPoint = cornerPoints[0][0][0];

    for (int i = 0; i < 8; i++) {
        if (cornerPoints[(i>>2)%2][(i>>1)%2][i%2].y < lowestPoint.y) {
            lowestPoint = cornerPoints[(i>>2)%2][(i>>1)%2][i%2];
        }
    }

    length = lowestPoint.length();

    if (length == 0)
        return;

    if (abs(distance / length) <= 1)
        targetAngle = acos(distance / length);
    else
        targetAngle = 0;

    currentAngle = angleBetween(distanceVector, lowestPoint);
    rotationAngle = targetAngle - currentAngle;

    rotationAxis = Quaternion::rotatePoint(distanceVector.cross(lowestPoint), planeConstraint.getOrientation());

    physicsObject.rotateGlobal(Quaternion(rotationAngle, rotationAxis.x, rotationAxis.y, rotationAxis.z));
}

void Constraints::applyPointConstraint(PhysicsObject& physicsObject, const vector<PointConstraint>& pointConstraints, unsigned int deltaTime) {
    if (pointConstraints.empty())
        return;

    physicsObject.setVelocity({0, 0, 0});

    // if (pointConstraints.size() == 2) TODO

    if (pointConstraints.size() > 1) {
        physicsObject.setAngularVelocity({0, 0, 0});
        return;
    }

    sf::Vector3f positionFromObject = pointConstraints[0].getCoordinates() - physicsObject.getPosition();

    physicsObject.setRotationAxisShift(Quaternion::unRotatePoint(positionFromObject, physicsObject.getOrientation()));

    sf::Vector3f rotationDirection = physicsObject.getAngularVelocity();
    physicsObject.setPosition(pointConstraints[0].getCoordinates() - Quaternion::rotatePoint(positionFromObject, Quaternion(physicsObject.getAngularVelocity().length() * (float) deltaTime / 1000000.0f, rotationDirection.x, rotationDirection.y, rotationDirection.z)));

}

void Constraints::addPlaneConstraint(Quaternion orientation, float offset) {
    constraints.push_back(new PlaneConstraint(orientation, offset));
}

void Constraints::addPlaneConstraint(Quaternion orientation) {
    constraints.push_back(new PlaneConstraint(orientation));
}

void Constraints::addPlaneConstraint(float offset) {
    constraints.push_back(new PlaneConstraint(offset));
}

void Constraints::addPlaneConstraint() {
    constraints.push_back(new PlaneConstraint());
}

void Constraints::addPointConstraint(PhysicsObject& physicsObject, sf::Vector3f coordinates) {
    physicsObject.addPointConstraint(coordinates);
}

vector<ConstraintTemplate*> Constraints::getConstraints() {
    return constraints;
}