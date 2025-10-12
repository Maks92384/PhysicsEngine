#pragma once

#include <SFML/Graphics.hpp>
#include "../Math/Quaternion.hpp"

using namespace std;

class PhysicsObject {
    float mass; // in kg

    sf::Vector3f hitbox; // {witdh, height, depth} along the axes, in meters

    vector<array<sf::Vector3f, 2>> forces; // All the forces affecting the object.    [point of application relative to the center of mass, force vector]
                                           // The magnitude of the force vector is also the value of the force in Newtons

    sf::Vector3f position; // in meters, Center of mass
    sf::Vector3f velocity; // in meters per second
    sf::Vector3f acceleration; // in meters per second squared

    Quaternion orientation; // normalized Quaternion describing the orientation
    sf::Vector3f angularVelocity; // in radians per second
    sf::Vector3f angularAcceleration; // in radians per second squared

    bool hidden = false;
public:
    PhysicsObject(sf::Vector3f position, sf::Vector3f hitbox, float mass);
    PhysicsObject(sf::Vector3f position, sf::Vector3f hitbox);
    PhysicsObject(sf::Vector3f position, float mass);
    PhysicsObject(float mass);
    PhysicsObject(sf::Vector3f position);
    PhysicsObject();

    void applyForce(sf::Vector3f applicationPoint, sf::Vector3f force);
    void clearForces();
    vector<array<sf::Vector3f, 2>>& getForces();

    void setMass(float newMass);
    void setPosition(sf::Vector3f newPosition);
    void setVelocity(sf::Vector3f newVelocity);
    void setAcceleration(sf::Vector3f newAcceleration);
    void setOrientation(Quaternion newOrientationQuaternion);
    void rotateGlobal(Quaternion rotationQuaternion);
    void rotateLocal(Quaternion rotationQuaternion);
    void setAngularVelocity(sf::Vector3f newAngularVelocity);
    void setAngularAcceleration(sf::Vector3f newAngularAcceleration);

    float getMass();
    sf::Vector3f getPosition();
    sf::Vector3f getVelocity();
    sf::Vector3f getAcceleration();
    Quaternion getOrientation();
    sf::Vector3f getAngularVelocity();
    sf::Vector3f getAngularAcceleration();
    sf::Vector3f getHitbox();
    vector<sf::Vector3f> getCornerPointsUnrotated();
    vector<sf::Vector3f> getCornerPoints();
    array<array<array<sf::Vector3f, 2>, 2>, 2> getCornerPointsAs3DArray();

    void hide();
    void show();
    bool isHidden();
};