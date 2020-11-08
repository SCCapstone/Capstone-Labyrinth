/* Copyright 2020 Samuel Dunny */
/* Player class (in header file) */

#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <SFML/Graphics.hpp>

using sf::Vector2u;
using sf::IntRect;
using sf::Texture;

class Animation {
// private attributes
private:
    // attribute that stores number of images in sprite sheet (has to fill sheet)
    Vector2u imageCount;

    // attribute that stores current image
    Vector2u currentImage;

    // these next 2 variables control the animation time

    // time since yo ulast changed images
    float totalTime;

    // how quickly the animation sprites switch
    float switchTime;

// public attributes
public:
    // rect to display animation
    IntRect uvRect;

    /* default constructor
     * only need pointer to texture for size
     * imageCount for number of images in sheet
    */
    Animation(Texture* texture, Vector2u imageCount, float switchTime);

    //destructor
    ~Animation(){}

    /* update function (takes in image and time difference) 
     * bool faceRight is used to determine if the character is facing right
     * TODO add bool up and bool down (maybe?)
    */
    void Update(int row, float deltaTime, bool faceRight);
};

Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime) {
    this->imageCount = imageCount;
    this->switchTime = switchTime;

    // starting total time at 0 for beginning of animation
    totalTime = 0.0f;

    // start at first image on x row
    currentImage.x = 0;

    // setting animation width to texture width
    uvRect.width = texture->getSize().x / float(imageCount.x);

    // setting animation height to texture height
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

void Animation::Update(int row, float deltaTime, bool faceRight) {
    currentImage.y = row;
    totalTime += deltaTime;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;

        if (currentImage.x >= imageCount.x)
            currentImage.x = 0;
    }

    //uvRect.left = currentImage.x * uvRect.width;

    uvRect.top  = currentImage.y * uvRect.height;

    if (faceRight) {
        // moving right
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }
    else {
        // moving left by starting at the otherside of the image, and inversing
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
}

#endif  // ANIMATION_H