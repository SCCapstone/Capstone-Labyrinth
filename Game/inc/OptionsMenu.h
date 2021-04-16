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

    bool cheating = false;

    
    // initializes options menu
    void initOptionsMenu(unsigned int width, unsigned int height);

    //Executes proper command based on what selection is made
    int itemSelected();

// public attributes
public:
    // default constructor
    OptionsMenu(bool is_cheating);

    // parameterized constructor
    OptionsMenu(unsigned int width, unsigned int height);
    // constructor that will take in a window pointer
    OptionsMenu(bool is_cheating, sf::RenderWindow* win);

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
OptionsMenu::OptionsMenu(bool is_cheating) {
    this->cheating = is_cheating;
      initOptionsMenu(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

// parameterized constructor (calls initOptionsMenu function)
OptionsMenu::OptionsMenu(unsigned int width, unsigned int height) {
      initOptionsMenu(width, height);
}

// constructor that takes a window pointer
OptionsMenu::OptionsMenu(bool is_cheating, sf::RenderWindow* win) {
    this->cheating = is_cheating;
    this->window = win;
    this->window->setTitle("Options Menu");
    initOptionsMenu(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

// destrcutor
OptionsMenu::~OptionsMenu() { /* intentionally empty */ }

// initializer function
void OptionsMenu::initOptionsMenu(unsigned int width, unsigned int height) {
    // set video mode width and height for window if window is unspecified
    if (window == NULL) {
        videoMode.height = height;
        videoMode.width = width;

        this->window = new sf::RenderWindow(videoMode, "Options Menu", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    }

    this->menu = new Menu(this->window->getSize().x, this->window->getSize().y, 2);

    //Sets default perams for main menu Text
    //menu->setText(0, "Effects");
    //menu->setText(1, "Music");
    //menu->setText(2, "Graphics");
    if (cheating)
        menu->setText(0, "Cheat Mode: Enabled");
    else
        menu->setText(0, "Cheat Mode: Disabled");
    menu->setText(1, "Exit");

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

            //Mouse Events 
        case sf::Event::MouseMoved:
            menu->mouseUpdate(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            break;
        case sf::Event::MouseButtonReleased:
            //Switch for different mouse buttons, might be useful later
            switch (event.mouseButton.button)
        case sf::Mouse::Left:
            menu->mouseUpdate(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            return itemSelected();
            break;


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
                itemSelected();
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
    return 0;
}

int OptionsMenu::itemSelected() {
    switch (menu->getSelection()) {

    case 0:
        if (menu->getText(0)._Equal("Cheat Mode: Enabled")) {
            menu->setText(0, "Cheat Mode: Disabled");
            cheating = false;
        }
        else {
            menu->setText(0, "Cheat Mode: Enabled");
            cheating = true;
        }
        return 3;
        break;

    case 1:
        //Go to Main menu
        return -1;
        break;

    default:
        return -1;
        break;
    }
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