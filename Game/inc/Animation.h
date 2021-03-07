/* Copyright 2020 Samuel Dunny */
/* Animation class (in header file) */

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

    // time since you last changed images
    float totalTime;

    // how quickly the animation sprites switch frames
    float switchTime;

// public attributes
public:
    // rect to display animation
    IntRect uvRect;

    /* constructor
     * only need pointer to texture for size
     * imageCount for number of images in sheet
     * switchTime for frame rate
    */
    Animation(Texture* texture, Vector2u imageCount, float switchTime);

    //destructor
    ~Animation();

    /* update function (takes in image and time difference) 
     * bool faceRight is used to determine if the character is facing right
     * TODO add bool up and bool down (maybe?)
    */
    void Update(int row, float deltaTime, bool faceRight, bool down, bool up);
};

Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime) {
    this->imageCount = imageCount;
    this->switchTime = switchTime;

    // starting total time at 0 for beginning of animation
    totalTime = 0.0f;

    // start at first image on x row
    currentImage.x = 0;

    // setting animation width to texture width
    uvRect.width = (int) texture->getSize().x / (int) imageCount.x;

    // setting animation height to texture height
    uvRect.height = (int) texture->getSize().y / (int) imageCount.y;
}

Animation::~Animation() { /* empty */}

void Animation::Update(int row, float deltaTime, bool faceRight, bool down, bool up) {
    currentImage.y = row;
    totalTime += deltaTime;

    // progress row animation (think of it as frames in a reel)
    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;

        if (currentImage.x >= imageCount.x)
            currentImage.x = 0;
    }

    //uvRect.left = currentImage.x * uvRect.width;

    uvRect.top  = currentImage.y * uvRect.height;

    // this inverts left-facing images so we can re-use animations
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