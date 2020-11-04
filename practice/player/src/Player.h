// by Sam Dunny, Capstone 490

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>    // for sfml methods
#include <SFML/Audio.hpp>       // for audio methods
#include <iostream>             // for output
#include <string>

/*
 * This class is for a game character
 * each motion (left, right, up, down) is represented by 3 textures
 * 12 textures total, with 12 sprites to represent them
 */

class Player : public sf::Drawable {
 private:
    // Game_Stats Player_stats TODO
    // Items Weapon_slot TODO
    // Items Armor_slot TODO
    // Items Special_slot TODO
    double field_of_vision;
    //Theme theme

    sf::Sprite step_1;
    sf::Sprite step_2;
    sf::Sprite step_3;
    sf::Sprite step_4;
    sf::Sprite step_5;
    sf::Sprite step_6;
    sf::Sprite step_7;
    sf::Sprite step_8;
    sf::Sprite step_9;
    sf::Sprite step_10;
    sf::Sprite step_11;
    sf::Sprite step_12;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // You can draw other high-level objects
        target.draw(step_1, states);
        // ... or use the low-level API
        //states.texture = &m_texture;
        //target.draw(m_vertices, states);
        // ... or draw with OpenGL directly
        //glBegin(GL_QUADS);
        //...
        //glEnd();
    }

 public:
    // constructor
    Player(double fov) {
       field_of_vision = fov;
    };

    // pickupItem function: to pickup up new items TODO
    //void pickupItem();

    // dropItem function: to drop item
    //void dropItem();

    // move function: to move player down
    //void move(int newx, int newy);

    // setting origin of the sprite relative ot sprite dimensions
    void setOrigin(int text_width, int text_height);

    // setting position of sprite relative to the window (middle)
    void setPosition(int window_width, int window_height);

    // setting all sprite textures
    void setTextures(sf::Texture t1,
                     sf::Texture t2,
                     sf::Texture t3,
                     sf::Texture t4,
                     sf::Texture t5,
                     sf::Texture t6,
                     sf::Texture t7,
                     sf::Texture t8,
                     sf::Texture t9,
                     sf::Texture t10,
                     sf::Texture t11,
                     sf::Texture t12
                     );

   void move(int newX, int newY) {
   step_1.move(newX, newY);
   step_2.move(newX, newY);
   step_3.move(newX, newY);
   step_4.move(newX, newY);
   step_5.move(newX, newY);
   step_6.move(newX, newY);
   step_7.move(newX, newY);
   step_8.move(newX, newY);
   step_9.move(newX, newY);
   step_10.move(newX, newY);
   step_11.move(newX, newY);
   step_12.move(newX, newY);
   std::cout << "Moving: X => " << newX << ", Y => " << newY << std::endl;
   }

    // accessors for sprite attributes
    sf::Sprite getSp1() {return step_1; }
    sf::Sprite getSp2() {return step_2; }
    sf::Sprite getSp3() {return step_3; }
    sf::Sprite getSp4() {return step_4; }
    sf::Sprite getSp5() {return step_5; }
    sf::Sprite getSp6() {return step_6; }
    sf::Sprite getSp7() {return step_7; }
    sf::Sprite getSp8() {return step_8; }
    sf::Sprite getSp9() {return step_9; }
    sf::Sprite getSp10() {return step_10; }
    sf::Sprite getSp11() {return step_11; }
    sf::Sprite getSp12() {return step_12; }


    // accessors
    double getFOV() { return field_of_vision; }
    // TODO add rest

    // mutators
    void setFOV(double newFOV) { field_of_vision = newFOV; }
    // TODO add rest


};

#endif  // PLAYER_H