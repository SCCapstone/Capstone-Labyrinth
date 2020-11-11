/* Copyright 2020 Samuel Dunny */
/* Collider class (in header file) */

#ifndef COLLIDER_H
#define COLLIDER_H

#include <SFML/Graphics.hpp>

/* 
 * This class uses the AABB collision detection algorithm
 */

class Collider {
// private attributes
private:
    sf::RectangleShape& body;

// public attributes
public:
    Collider(sf::RectangleShape& body_shape);
    ~Collider();

    /* Checks to see if two Collider objects are colliding
     * push determines how much give the other object will have
     * ex: push = 0, neither object moves
     *     push = 1, other object will get 'pushed'
     */
    bool CheckCollision(Collider& other, float push);

    // determine position of collidable object
    sf::Vector2f GetPosition() { return body.getPosition(); }

    // need this for AABB calculations
    sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }

    // this method allows us to 'push' moveable objects
    void Move(float dx, float dy) { body.move(dx, dy); }
};

Collider::Collider(sf::RectangleShape& body_shape) :
    body(body_shape) {}

Collider::~Collider() { /* empty */ }

// based on AABB collision detection algorithm
bool Collider::CheckCollision(Collider& other, float push) {
    // getting 'others' coordinates
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();

    // getting our objects coordinates
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if ((intersectX < 0.0f) && (intersectY < 0.0f)) {
        // this performs clamping, ensuring push is always between 0 and 1
        push = std::min(std::max(push, 0.0f), 1.0f);

        // pushing out on the x-axis
        if (intersectX > intersectY) {
            if (deltaX  >0.0f) {
                Move(intersectX * (1.0f-push), 0.0f);
                other.Move(-intersectX * push, 0.0f);
            }
            else {
                Move(-intersectX * (1.0f-push), 0.0f);
                other.Move(intersectX * push, 0.0f);
            }
        }
        // pushing out on the y-axis
        else {
            if (deltaY  >0.0f) {
                Move(0.0f, intersectY * (1.0f-push));
                other.Move(0.0f, -intersectY * push);
            }
            else {
                Move(0.0f, -intersectY * (1.0f-push));
                other.Move(0.0f, intersectY * push);
            }
        }
        return true;
    }
    return false;
}

#endif  // COLLIDER_H