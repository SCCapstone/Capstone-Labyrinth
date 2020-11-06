/* Copyright 2020 Samuel Dunny */
/* Player class (in header file) */

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>

// from std library
using std::string;
using std::cout;
using std::endl;

// from sf library
using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;

class Player {
// private attributes
private:
   Texture p_Texture;
   Sprite p_Sprite;

// public attributes
public:
   // default constructor
   Player() {/* default */}

   // parameterized constructor, given filepath to .png image
   Player(string img_Directory) {
      if (!p_Texture.loadFromFile(img_Directory))
        cout << "ERROR opening " << img_Directory << " file" << endl;
      p_Texture.setSmooth(true);
      p_Sprite.setTexture(p_Texture);
   }

   // draw function
   void drawPlayer(RenderWindow &window) {
      window.draw(p_Sprite);
   }

   // move player function
   void movePlayer(char direction, float moveSpeed);
};

// move player function
void Player::movePlayer(char direction, float moveSpeed) {
   if (direction == 'u')
      p_Sprite.move(0, -moveSpeed);
   else if (direction == 'd')
      p_Sprite.move(0, moveSpeed);
   else if (direction == 'l')
      p_Sprite.move(-moveSpeed, 0);
   else if (direction == 'r')
      p_Sprite.move(moveSpeed, 0);
}

#endif  // PLAYER_H