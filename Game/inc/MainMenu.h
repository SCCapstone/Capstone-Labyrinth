/* Copyright 2020 Carson Stabell */
/* Main Menu class (in header file) */

#ifndef MAINMENU_H
#define MAINMENU_H

#include "OptionsMenu.h"
#include "InstructionsMenu.h"
#include <iostream>
#include <vector>

class MainMenu {
// private attributes
private:
    sf::RenderWindow* window;       // window to display all objects
    sf::VideoMode videoMode;        // used in window instantiation (size)
    Menu* menu;                     // used to display buttons
    
    //Sprite Stuff
    sf::Texture titleTex;
    sf::Sprite* title;
    sf::Texture backgroundTex;
    sf::Sprite background;

    bool is_cheating = false;

    // initializer function for main menu
    void initMainMenu(unsigned int width, unsigned int height, int numMenuItems, sf::RenderWindow* win);

    // function that is responisble for instantiating and running the options menu
    void runOptionsMenu();

    void runInstructions();

// public attributes
public:
      MainMenu();                               // default constructor
      MainMenu(sf::RenderWindow* win);          // param constructor

      // destructor
      ~MainMenu();

      // update function that polls for keystrokes
      int update();

      // render function that draws and displays all objects within window
      void render();

      // returns true if window is still open
      const bool running() const {
        return window->isOpen();
      }

      bool inCheatMode() { return is_cheating; }
};

// default constructor
MainMenu::MainMenu() {
    // initializes menu with default width, default height, default button amount, and no given window
    initMainMenu(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_NUMBER_OF_ITEMS, NULL);
}

// parameterized constructor
MainMenu::MainMenu(sf::RenderWindow* win) {
    // initializes menu with no width, no height, default button amount, and given window
    initMainMenu(0, 0, DEFAULT_NUMBER_OF_ITEMS, win);
}

// destructor
MainMenu::~MainMenu() { /* intentionally empty */ }

// initializes the main menu, places all the buttons accordingly 
void MainMenu::initMainMenu(unsigned int width, unsigned int height, int numMenuItems, sf::RenderWindow* win)
{
    // constructed using parameterized constructor
    if (win != NULL) {
        this->window = win;
        // getting dimensions from the window
        videoMode.height = window->getSize().x;
        videoMode.width = window->getSize().y;
    }
    // constructed using default constructor
    else {
        // setting default dimensions of the window
        videoMode.height = height;
        videoMode.width = width;
        this->window = new sf::RenderWindow(videoMode, "Main Menu", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    }
    
    // instantiates menu using new dimensions
    this->menu = new Menu(videoMode.width, videoMode.height, numMenuItems);

    // calculate middle to center buttons
    unsigned int width_middle = videoMode.width / 2;

    //Sets parameters for main menu options text
    menu->setText(0, "Enter the Labyrinth");
    menu->setText(1, "Options ");
    menu->setText(2, "Instructions");
    menu->setText(3, "Surrender to the Labyrinth");

    // place buttons in menu 
    menu->setPos(0, sf::Vector2f((float)width_middle, (float) 4 * (videoMode.height / 8)));
    menu->setPos(1, sf::Vector2f((float)width_middle, (float) 5 * (videoMode.height / 8)));
    menu->setPos(2, sf::Vector2f((float)width_middle, (float) 6 * (videoMode.height / 8)));
    menu->setPos(3, sf::Vector2f((float)width_middle, (float) 7 * (videoMode.height / 8)));

    // load title image
    if(!(titleTex.loadFromFile("imgs/title_logo.png"))) {
        std::cout << "Title did not load" << std::endl;
    }

    // create new sprite and set it's texture and scale
    title = new sf::Sprite();
    title->setTexture(titleTex);
    title->setScale(1.5, 1.5);

    // set sprite's origin to its center (by default at top left corner)
    title->setOrigin(sf::Vector2f(title->getLocalBounds().width/2, title->getLocalBounds().height/2));

    // set sprite in the middle of the window, and 1/3 the way down
    title->setPosition(sf::Vector2f((float)width_middle, (float)videoMode.height/3));
    
    // load background image for menu backsplash
    if (!(backgroundTex.loadFromFile("imgs/wall.png"))) {
        std::cout << "Background did not load" << std::endl;
    }

    // set the background texture anbd scale
    background.setTexture(backgroundTex);
    background.setScale(15, 15);
}

// update function that polls for keystrokes
int MainMenu::update() {
    // create event variable
    sf::Event event;
    
    // while loop that constantly polls for user input
    while(window->pollEvent(event)) {
        // switch on events (keystrokes)
        switch(event.type) {
        
        // if any key was released
        case sf::Event::KeyReleased:
            // switch on key release codes
            switch(event.key.code) {
            
                // user pressed the up key
            case sf::Keyboard::Up:
                menu->MoveUp();
                break;
            
            // user pressed the up key
            case sf::Keyboard::W:
                menu->MoveUp();
                break;
             
            // user pressed the down key
            case sf::Keyboard::Down:
                menu->MoveDown();
                break;
            
            // user pressed the down key
            case sf::Keyboard::S:
                menu->MoveDown();
                break;

            // user pressed the enter key
            case sf::Keyboard::Enter:
                // retrieves selected button's index
                switch(menu->getSelection()) {
                
                case 0:
                    //Play is just close window rn
                    window->close();
                    return 0;
                    break;
                          
                case 1:
                    //Do the options screen
                    runOptionsMenu();
                    break;

                case 2:
                    // run the instructions screen
                    runInstructions();
                    break;
                    
                case 3:
                    //Time to exit, have to make it different from play somehow
                    window->close();
                    return 1;
                    break;

                default:
                    break;
                }
                break;
            
            default:
                break;
            }
            break;
        
        // user closed the window
        case sf::Event::Closed:
            window->close();
            break;
            
        default:
            break;
        }
    }
    return -1;
}

// renders all menu objects
void MainMenu::render() {
    // clears the window
    window->clear();

    // draws the background
    window->draw(background);
      
    // draws the title graphic
    window->draw(*title);

    // draws all buttons
    menu->render(*window);

    // displays all drawn items
    window->display();
}

// instantiates OptionsMenu object, runs options menu
void MainMenu::runOptionsMenu() {
    // creates new optiuons sub-menu
    OptionsMenu options;

    int cheat_mode = 0;

    // runs the options menu until exit condition
    while(options.running())
    {
          cheat_mode = options.update();
          options.render();
    }

    // 5 means cheating, 6 means not cheating
    //std::cout << cheat_mode << std::endl;
    is_cheating = options.getIsCheating();
    //std::cout << options.getIsCheating() << std::endl;
}

// instantiates OptionsMenu object, runs options menu
void MainMenu::runInstructions() {
    // creates new optiuons sub-menu
    InstructionsMenu instructions;

    // runs the options menu until exit condition
    while (instructions.running())
    {
        instructions.update();
        instructions.render();
    }
}

#endif //MAINMENU_H