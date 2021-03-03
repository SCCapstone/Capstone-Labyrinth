// by Sam Dunny

/* 	(1) interfaces cannot be constructed or instantiated,
 * 	    but they can be implemented in object classes
 * 	(2) any class that implements Wall_Interface will
 * 	    have the following functionality (to override)
 *  (3) Just as a note to myself, these are also called
 *      abstract classes. Also, polymorphism works alot
 *      like parent-child inheritance in C++
 *  (4) This class will be purely virtual
 */

#ifndef WALL_INTERFACE
#define WALL_INTERFACE

#include <SFML/Graphics.hpp>
#include "Collider.h"

class Wall_Interface {
protected:
    // all wall patterns will be comprised of configurations of 3 walls
    sf::RectangleShape wall1;
    sf::RectangleShape wall2;
    sf::RectangleShape wall3;

    // useless, needed for collider call
    sf::RectangleShape wall1View;
    sf::RectangleShape wall2View;
    sf::RectangleShape wall3View;

    // useless, needed for collider call
    sf::RectangleShape wall1HB;
    sf::RectangleShape wall2HB;
    sf::RectangleShape wall3HB;

public:
    // no constructor (interface)
    /* Implementation:
     *  placement (given by position argument) is based on corner square, or middle link
     */

    // virtual destructor
    //virtual ~Wall_Interface();

    // takes in window reference, draws player
    virtual void Draw(sf::RenderWindow& window) = 0;

    // needed this method in this class, as referencing in Game_Engine would not work
    virtual bool ColliderCheck(Collider other, float push) = 0;

    // every 'solid' object in game needs this method for collision
    virtual Collider* GetColliders() = 0;
    
};


#endif	// WALL_INTERFACE


/* For GetColliders, whenever its implemented
Collider colARR[2] = { Collider(wall, wallView, wallHB), Collider(wall, wallView, wallHB) };
return colARR;
*/