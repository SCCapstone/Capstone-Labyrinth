/* Copyright 2020 Carson Stabell */
/* Options Menu class (in header file) */

#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "Menu.h"
#include <stdlib.h>

class OptionsMenu {
// private attributes
private:
    sf::RenderWindow* window;       // window that displays all objects
    sf::VideoMode videoMode;        // used in window instantiation (size)
    Menu* menu;                     // used to display buttons
    sf::Texture backgroundTex;      // variable for the texture of our background
    sf::Sprite background;          // variable for the background

    bool cheating;

    
    // initializes options menu
    void initOptionsMenu(unsigned int width, unsigned int height);

// public attributes
public:
    // default constructor
    OptionsMenu();

    // parameterized constructor
    OptionsMenu(unsigned int width, unsigned int height);

    // destructor
    ~OptionsMenu();

    // update function that polls keystroke events
    int update();

    // render function that draws buttons and background, displays them
    void render();

    // returns true if window is still open
    const bool running() const {
      return window->isOpen();
    }

    bool getIsCheating() { return cheating; }
};

// default constructor (calls initOptionsMenu function with default values)
OptionsMenu::OptionsMenu() {
      initOptionsMenu(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

// parameterized constructor (calls initOptionsMenu function)
OptionsMenu::OptionsMenu(unsigned int width, unsigned int height) {
      initOptionsMenu(width, height);
}

// destrcutor
OptionsMenu::~OptionsMenu() { /* intentionally empty */ }

// initializer function
void OptionsMenu::initOptionsMenu(unsigned int width, unsigned int height) {
    // set video mode width and height for window
    videoMode.height = height;
    videoMode.width = width;

    this->window = new sf::RenderWindow(videoMode, "Options Menu", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    this->menu = new Menu(videoMode.width, videoMode.height, 5);

    //Sets default perams for main menu Text
    menu->setText(0, "Effects");
    menu->setText(1, "Music");
    menu->setText(2, "Graphics");
    menu->setText(3, "Cheat Mode: Disabled");
    menu->setText(4, "Exit");

    // load background texture
    if (!(backgroundTex.loadFromFile("imgs/options_background.png"))) {
        std::cout << "Background did not load" << std::endl;
    }

    // set background texture and scale
    background.setTexture(backgroundTex);
    background.setScale(2.5, 2.5);
}

// update function that polls keystroke events
int OptionsMenu::update() {
    // create event variable
    sf::Event event;

    // while loop that scans for key strokes
    while(window->pollEvent(event)) {
        switch(event.type) {
        // if a key has been released
        case sf::Event::KeyReleased:
            switch(event.key.code) {
            
            // the up key was pressed
            case sf::Keyboard::Up:
                menu->MoveUp();
                break;
                
            // the up key was pressed 
            case sf::Keyboard::W:
                menu->MoveUp();
                break;
                      
            // the down key was pressed
            case sf::Keyboard::Down:
                menu->MoveDown();
                break;
            
            // the down key was pressed
            case sf::Keyboard::S:
                menu->MoveDown();
                break;

            // the enter key was pressed
            case sf::Keyboard::Enter:
                switch(menu->getSelection()) {
                
                case 0:
                    //Sssssshhhh options soon
                    break;

                case 3:
                    if (menu->getText(3)._Equal("Cheat Mode: Enabled")) {
                        menu->setText(3, "Cheat Mode: Disabled");
                        cheating = false;
                    }
                    else {
                        menu->setText(3, "Cheat Mode: Enabled");
                        cheating = true;
                    }
                    return 3;
                    break;
                    
                case 4:
                    //Exit to Main menu
                    window->close();
                    if (cheating)
                        return 5;
                    return 6;
                    break;
                    
                default:
                    break;
                }
                break;
    
            default:      
                break;
            }
            break;
        
        // window was closed
        case sf::Event::Closed:
            window->close();
            break;
        
        default:
            break;
        }
    }
    return -1;
}

// render function that draws buttons and background, displays them
void OptionsMenu::render() {
    // clears window
    window->clear();
    
    // draws background
    window->draw(background);
    
    // draws buttons
    menu->render(*window);

    // displays all drawn objects
    window->display();
}


#endif //OPTIONSMENU_H