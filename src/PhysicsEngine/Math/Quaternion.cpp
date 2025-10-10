#include "Quaternion.hpp"
#include <cmath>
#include <iostream>


Quaternion::Quaternion(float angle, float x, float y, float z) {
    set(angle, x, y, z);
}

void Quaternion::set(float angle, float x, float y, float z) {
    sf::Vector3f axis = {x, y, z};

    if (axis.length() != 0)
        axis = axis.normalized();
    axis = axis * sin(angle / 2);

    this->w = cos(angle / 2);
    this->x = axis.x;
    this->y = axis.y;
    this->z = axis.z;
}

Quaternion Quaternion::multiply(const Quaternion& q2) const {
    const Quaternion& q1 = *this;

    float a1 = q1.getW();
    float b1 = q1.getX();
    float c1 = q1.getY();
    float d1 = q1.getZ();

    float a2 = q2.getW();
    float b2 = q2.getX();
    float c2 = q2.getY();
    float d2 = q2.getZ();


    Quaternion newQuaternion = Quaternion(0, 0, 0, 0);

    newQuaternion.setW(a1 * a2 - b1 * b2 - c1 * c2 - d1 * d2);
    newQuaternion.setX(a1 * b2 + b1 * a2 + c1 * d2 - d1 * c2);
    newQuaternion.setY(a1 * c2 - b1 * d2 + c1 * a2 + d1 * b2);
    newQuaternion.setZ(a1 * d2 + b1 * c2 - c1 * b2 + d1 * a2);

    return newQuaternion;
}

Quaternion Quaternion::conjugated() const {
    Quaternion newQuaternion = Quaternion(w, -x, -y, -z);
    return newQuaternion;
}

Quaternion Quaternion::multiplyByScalar(float scalar) const {
    Quaternion newQuaternion = Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
    return newQuaternion;
}


Quaternion Quaternion::normalized() const {
    Quaternion q = Quaternion(0, 0, 0, 0);

    double length = sqrt(w * w + x * x + y * y + z * z);

    if (length == 0)
        return q;

    q.setW(w / length);
    q.setX(x / length);
    q.setY(y / length);
    q.setZ(z / length);

    return q;
}

void Quaternion::normalize() {
    double length = sqrt(w * w + x * x + y * y + z * z);

    if (length == 0)
        return;

    w = w / length;
    x = x / length;
    y = y / length;
    z = z / length;
}

sf::Vector3f Quaternion::rotate(const sf::Vector3f& point, const Quaternion& q) {
    Quaternion p = Quaternion(0, 0, 0, 0);
    p.setW(0);
    p.setX(point.x);
    p.setY(point.y);
    p.setZ(point.z);

    p.normalize();

    p = q.multiply(p);
    p = p.multiply(q.conjugated());

    sf::Vector3f newPoint = {p.x, p.y, p.z};

    return newPoint;
}


void Quaternion::setW(float w) {
    this->w = w;
}

void Quaternion::setX(float x) {
    this->x = x;
}

void Quaternion::setY(float y) {
    this->y = y;
}

void Quaternion::setZ(float z) {
    this->z = z;
}


float Quaternion::getW() const {
    return w;
}

float Quaternion::getX() const {
    return x;
}

float Quaternion::getY() const {
    return y;
}

float Quaternion::getZ() const {
    return z;
}