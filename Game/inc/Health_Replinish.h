/* Copyright 2021 Samuel Dunny */
/* Health_Replinish class (in header file) */

#ifndef HEALTH_REPLINISH_H
#define HEALTH_REPLINISH_H

#include "Collider.h"
#include "Animation.h"
#include "Player.h"

class Health_Replinish {
    // private attributes
private:
    sf::RectangleShape heart;

    // creating instance of animation (to animate heart)
    Animation h_animation;

    // what row of the sprite sheet we are using
    unsigned int row;

    // public attributes
public:
    Health_Replinish(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, Vector2u imageCount, float switchTime);
    ~Health_Replinish();

    void Update(float deltaTime);

    // takes in window reference, draws player
    void Draw(sf::RenderWindow& window);

    // mutator
    void SetPosition(sf::Vector2f pos) { heart.setPosition(pos); }

    // accessor
    sf::Vector2f GetPosition() { return heart.getPosition(); }

    bool Replinish(Player* player);
};

Health_Replinish::Health_Replinish(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, Vector2u imageCount, float switchTime) :
    h_animation(texture, imageCount, switchTime) {
    this->row = 0;
    heart.setSize(size);
    heart.setOrigin(size / 2.0f);
    heart.setTexture(texture);
    heart.setPosition(position);
}

Health_Replinish::~Health_Replinish() { /* empty */ }

void Health_Replinish::Update(float deltaTime) {
    h_animation.Update(this->row, deltaTime, true, false, false);
    heart.setTextureRect(h_animation.uvRect);
}

void Health_Replinish::Draw(sf::RenderWindow& window) {
    window.draw(heart);
}

bool Health_Replinish::Replinish(Player* player) {
    // if the player is in the heart's boundary
    if (heart.getGlobalBounds().contains(player->getIndividualPos())) {

        // only replinish if health isn't full already
        if (player->getTotalHealth() == player->getOrignalHealth())
            return false;

        // reset player health to original health
        player->setTotalHealth(player->getOrignalHealth());
        return true;
        //std::cout << "\nHealth consumed" << std::endl;
    }
    return false;
}


#endif  // HEALTH_REPLINISH_H