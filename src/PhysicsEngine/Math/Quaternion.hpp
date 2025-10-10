#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class Quaternion {
    float w, x, y, z;
public:
    Quaternion(float angle, float x, float y, float z);

    static sf::Vector3f rotatePoint(const sf::Vector3f& point, const Quaternion& q);

    Quaternion multiply(const Quaternion& q2) const;
    Quaternion conjugated() const;
    Quaternion multiplyByScalar(float scalar) const;
    Quaternion normalized() const;
    void normalize();

    void set(float angle, float x, float y, float z);

    void setW(float w);
    void setX(float x);
    void setY(float y);
    void setZ(float z);

    float getW() const;
    float getX() const;
    float getY() const;
    float getZ() const;

    float getAngle() const;
    sf::Vector3f getAxis() const;

    sf::Vector3f toEulerVector() const;
};
