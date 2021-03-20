/* Copyright 2021 Samuel Dunny */
/* Instructions Menu class (in header file) */

#ifndef INSTRUCTIONSMENU_H
#define INSTRUCTIONSMENU_H

#include "Menu.h"

class InstructionsMenu {
    // private attributes
private:
    sf::RenderWindow* window;       // window that displays all objects
    sf::VideoMode videoMode;        // used in window instantiation (size)
    Menu* menu;                     // used to display button
    sf::Texture backgroundTex;      // variable for the texture of our background
    sf::Sprite background;          // variable for the background

    sf::Text instructs;
    sf::Font font;                      // variable for the font for our menu text
    sf::Texture backsplash;             // variable for the texture of our buttons
    sf::Sprite inst_paper;

    // initializes options menu
    void initInstructions(unsigned int width, unsigned int height);

    // public attributes
public:
    // default constructor
    InstructionsMenu();

    // destructor
    ~InstructionsMenu();

    // update function that polls keystroke events
    int update();

    // render function that draws buttons and background, displays them
    void render();

    // returns true if window is still open
    const bool running() const {
        return window->isOpen();
    }
};

// default constructor (calls initOptionsMenu function with default values)
InstructionsMenu::InstructionsMenu() {
    initInstructions(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

// destrcutor
InstructionsMenu::~InstructionsMenu() { /* intentionally empty */ }

// initializer function
void InstructionsMenu::initInstructions(unsigned int width, unsigned int height) {
    // load text texture
    if (!font.loadFromFile("txts/NotPapayrus.ttf")) {
        std::cout << "Text did not load" << std::endl;
    }

    // load backsplash
    if (!(backsplash.loadFromFile("imgs/blank_button.png"))) {
        std::cout << "Backsplash did not load" << std::endl;
    }

    // load background texture
    if (!(backgroundTex.loadFromFile("imgs/options_background.png"))) {
        std::cout << "Background did not load" << std::endl;
    }

    // set video mode width and height for window
    videoMode.height = height;
    videoMode.width = width;

    this->window = new sf::RenderWindow(videoMode, "Instructions", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    this->menu = new Menu(videoMode.width, videoMode.height, 1);

    this->instructs.setFont(font);
    this->instructs.setFillColor(sf::Color::Black);
    this->instructs.setString("Arrow Keys:\t\tMove around\nSpacebar:\t\t\t Attack\nEscape:\t\t\t\t  Exit game\nObjective:\t\t\t Kill all 4 bosses to\n\t\t\t\t\t\t\t\t conquer the maze");
    this->instructs.setOrigin(sf::Vector2f(instructs.getLocalBounds().width / 2,
        instructs.getLocalBounds().height / 2));
    this->instructs.setPosition(Vector2f((float)videoMode.width / 2, (float)3 * (videoMode.height / 8)));


    //Sets default perams for main menu Text
    this->menu->setText(0, "Exit");
    this->menu->setPos(0, Vector2f((float)videoMode.width/2, (float)7 * (videoMode.height / 8)));

    // set background texture and scale
    this->background.setTexture(backgroundTex);
    this->background.setScale(2.5, 2.5);

    this->inst_paper.setTexture(backsplash);
    this->inst_paper.setOrigin(sf::Vector2f(inst_paper.getLocalBounds().width / 2,
        inst_paper.getLocalBounds().height / 2));

    // sets default position
    inst_paper.setPosition(Vector2f((float)videoMode.width / 2, (float)3 * (videoMode.height / 8)));
    inst_paper.setScale(2.4f, 11.0f);
}

// update function that polls keystroke events
int InstructionsMenu::update() {
    // create event variable
    sf::Event event;

    // whule loop that scans for key strokes
    while (window->pollEvent(event)) {
        switch (event.type) {
            // if a key has been released
        case sf::Event::KeyReleased:
            switch (event.key.code) {

                // the enter key was pressed
            case sf::Keyboard::Enter:
                switch (menu->getSelection()) {

                case 0:
                    //Exit to Main menu
                    window->close();
                    return 0;
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
void InstructionsMenu::render() {
    // clears window
    window->clear();

    // draws background
    window->draw(background);

    window->draw(inst_paper);
    window->draw(instructs);

    // draws buttons
    menu->render(*window);

    // displays all drawn objects
    window->display();
}


#endif // INSTRUCTIONSMENU_H