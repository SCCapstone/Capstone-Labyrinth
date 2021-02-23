/* Copyright 2020 Samuel Dunny */
/* HealthBar class (in header file) */

#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "Animation.h"

// from sf library
using sf::RenderWindow;
using sf::Texture;
using sf::Vector2f;
using sf::RectangleShape;
using sf::Keyboard;

class HealthBar {
    // private attributes
private:
    RectangleShape healthbar;

    // creating instance of animation (to animate body)
    Animation health_anim;

    // 'speed' of health bar (has to travel at same speed as enemy and player)
    int speed;

    // what row of the sprite sheet we are using
    unsigned int row;

    // determine which way to move health bar
    bool movingUp;
    bool movingDown;

    // public attributes
public:
    // Constructor
    HealthBar(RectangleShape* body, Vector2f dimensions, Texture* texture, Vector2u imageCount, float switchTime, float speed);

    //Destructor
    ~HealthBar();

    // Update functionality
    void Update(unsigned int row, float deltaTime);

    // takes in window reference, draws player
    void Draw(RenderWindow& window);

    void Move(Vector2f movement);

    void setTextureRectangle(IntRect &rect);
};

HealthBar::HealthBar(RectangleShape* body, Vector2f dimensions, Texture* texture, Vector2u imageCount, float switchTime, float speed) :
    health_anim(texture, imageCount, switchTime) {

    this->speed = speed;

    // default row is 4 (full health)
    row = 4;

    healthbar.setSize(Vector2f(dimensions.x, dimensions.y/3.0f));
    healthbar.setOrigin(healthbar.getSize() / 2.0f);
    healthbar.setTexture(texture);
    // set health bar position above player
    healthbar.setPosition(body->getPosition().x, body->getPosition().y - (2.0f*dimensions.y/3.0f));
}

HealthBar::~HealthBar() { /* empty */}

void HealthBar::Update(unsigned int row, float deltaTime) {
    health_anim.Update(row, deltaTime, false, false, false);
}

void HealthBar::Draw(RenderWindow& window) {
    window.draw(healthbar);
}

void HealthBar::Move(Vector2f movement) {
    healthbar.move(movement);
}

void HealthBar::setTextureRectangle(IntRect& rect) {
    healthbar.setTextureRect(rect);
}

#endif  // HEALTHBAR_H