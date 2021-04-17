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
    //Contructor with a window param
    InstructionsMenu(sf::RenderWindow* win);

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

//Contructor with a window param
InstructionsMenu::InstructionsMenu(sf::RenderWindow* win) {
    this->window = win;
    window->setTitle("Instructions");
    initInstructions(this->window->getSize().x, this->window->getSize().y);
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

    //Only if a window is not passed as a constructor Param
    if (this->window == NULL) {
        this->window = new sf::RenderWindow(videoMode, "Instructions", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    }
    this->menu = new Menu(videoMode.width, videoMode.height, 1);

    this->instructs.setFont(font);
    this->instructs.setFillColor(sf::Color::Black);
    this->instructs.setString("Arrow Keys:\t\tMove around\nSpacebar:\t\t\t Melee Attack\nEscape:\t\t\t\t  Exit game\nObjective:\t\t\t Kill all 4 bosses to\n\t\t\t\t\t\t\t\t conquer the maze");
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
            
            //Mouse Events
            case sf::Event::MouseMoved:
                menu->mouseUpdate(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                break;

            case sf::Event::MouseButtonReleased:
                //Switch for different mouse buttons, might be useful later
                switch (event.mouseButton.button)

            case sf::Mouse::Left:
                menu->mouseUpdate(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                switch (menu->getSelection()) {

                case 0:
                    //Exit to Main menu
                    return -1;
                    break;

                default:
                    break;
                }
                break;

            // if a key has been released
            case sf::Event::KeyReleased:
                switch (event.key.code) {

            // the enter key was pressed
            case sf::Keyboard::Enter:
                switch (menu->getSelection()) {

                case 0:
                    //Exit to Main menu
                    return -1;
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
    return 0;
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