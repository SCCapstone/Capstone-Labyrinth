/* Copyright 2020 Carson Stabell */
/* Menu class (in header file) */

#ifndef MENU_H
#define MENU_H

#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>

// number of buttons we have
const int DEFAULT_NUMBER_OF_ITEMS = 4;

// window dimensions
const unsigned int DEFAULT_WIDTH = 600;
const unsigned int DEFAULT_HEIGHT = 600;

class Menu {
// private attributes
private:
    int selectedItemIndex;              // integer that marks which button we are currently highlighting
    int menuItems;                      // number of menu items (buttons)
    sf::Font font;                      // variable for the font for our menu text
    sf::Texture bButtonTex;             // variable for the texture of our buttons
    std::vector<sf::Text> textMenu;     // vector that contains all the text of our buttons
    std::vector<sf::Sprite> buttons;    // vector that contains all the button sprites

// public attributes
public:
    // default constructor
    Menu();
      
    // parameterized constructor 1
    Menu(unsigned int width, unsigned int height);

    // parameterized constructor 2
    Menu(unsigned int width, unsigned int height, int numOfButtons);
    
    // destructor
    ~Menu();

    // draws all buttons (does not display them)  
    void render(sf::RenderWindow &window);
      
    // functions to update selected item index, highlight selection
    void MoveUp();
    void MoveDown();

    // accessors
    int getSelection() { return selectedItemIndex; }
    std::string getText(int selection) { return textMenu[selection].getString(); }

    // mutators
    void setText(int selection, std::string words);
    void setPos(int, sf::Vector2f);
    void setCharSize(int, int);
};

// default constructor
Menu::Menu() : Menu::Menu(DEFAULT_WIDTH, DEFAULT_HEIGHT) {}

Menu::Menu(unsigned int width, unsigned int height) {
    // load text texture
    if(!font.loadFromFile("txts/NotPapayrus.ttf")) {
        std::cout << "Text did not load" << std::endl;
    }

    // default button selection
    selectedItemIndex = 0;
    textMenu[0].setFillColor(sf::Color::Red);

    // default button amount
    menuItems = DEFAULT_NUMBER_OF_ITEMS;

    // initialize vector
    textMenu.resize(menuItems);

    // default button positions

    // button 1
    textMenu[0].setFont(font);
    textMenu[0].setFillColor(sf::Color::White);
    textMenu[0].setString("Play");
    textMenu[0].setPosition(sf::Vector2f(float(width / 2), float(height/(menuItems + 1) * 1)));

    // button 2
    textMenu[1].setFont(font);
    textMenu[1].setFillColor(sf::Color::White);
    textMenu[1].setString("Options");
    textMenu[1].setPosition(sf::Vector2f(float(width / 2), float(height/(menuItems + 1) * 2)));

    // button 3
    textMenu[2].setFont(font);
    textMenu[2].setFillColor(sf::Color::White);
    textMenu[2].setString("Instructions");
    textMenu[2].setPosition(sf::Vector2f(float(width / 2), float(height / (menuItems + 1) * 4)));

    // button 4
    textMenu[3].setFont(font);
    textMenu[3].setFillColor(sf::Color::White);
    textMenu[3].setString("Exit");
    textMenu[3].setPosition(sf::Vector2f(float(width / 2), float(height/(menuItems + 1) * 3)));
}

//Handles textMenu with varying textMenu options
Menu::Menu(unsigned int width, unsigned int height, int numOfButtons) {
    // load text texture
    if (!font.loadFromFile("txts/NotPapayrus.ttf")) {
        std::cout << "Text did not load" << std::endl;
    }

    // button amount
    menuItems = numOfButtons;
    
    // creates menuItem-amount of texts
    textMenu.assign(menuItems, sf::Text());

    // sets default values for all buttons
    for(int i = 0; i < menuItems; i++) {
        textMenu[i].setFont(font);
        textMenu[i].setFillColor(sf::Color::White);
        textMenu[i].setString("Null");
        textMenu[i].setPosition(sf::Vector2f(float(width / 2), float(height/(menuItems + 1) * (i + 1))));
        textMenu[i].setCharacterSize(20);
    }

    //Sets first entry as default selection and makes red
    selectedItemIndex = 0;
    textMenu[0].setFillColor(sf::Color::Red);
    
    //Setup buttons
    if (!(bButtonTex.loadFromFile("imgs/blank_button.png"))) {
        std::cout << "Blank Button did not load" << std::endl;
    }
    
    // initializes button vector
    buttons.resize(menuItems);
    for (unsigned i = 0; i < buttons.size(); i++) {
        buttons[i].setTexture(bButtonTex);

        // sets default position
        buttons[i].setPosition(sf::Vector2f(textMenu[i].getGlobalBounds().left, textMenu[i].getGlobalBounds().top));
        buttons[i].setScale(1.2f, 1.2f); 
      }
}

// destructor
Menu::~Menu() { /* intentionally empty */ }

// draws all buttons (does not display them)
void Menu::render(sf::RenderWindow &window) {
    for(int i = 0; i < menuItems; i++) {
        window.draw(buttons[i]);
        window.draw(textMenu[i]);
    }
}

// highlights chosen button, updates current selected item index
void Menu::MoveUp() {
    if(selectedItemIndex-1 >= 0) {
        textMenu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        textMenu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

// highlights chosen button, updates current selected item index
void Menu::MoveDown() {
    if(selectedItemIndex+1 < menuItems) {
        textMenu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        textMenu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

// sets text at specified button index, centers both button and text
void Menu::setText(int selection, std::string words) {
    textMenu[selection].setString(words);
    for (unsigned i = 0; i < buttons.size(); i++) {
        // center buttons on their geometric center
        buttons[i].setOrigin(sf::Vector2f(buttons[i].getLocalBounds().width / 2, 
                                          buttons[i].getLocalBounds().height / 2));
        // center text on thier geometric center
        textMenu[selection].setOrigin(sf::Vector2f(textMenu[selection].getLocalBounds().width / 2,
                                                   textMenu[selection].getLocalBounds().height / 2));
      }
}

// places both button and text at given coordinates
void Menu::setPos(int select, sf::Vector2f pos) {
    textMenu[select].setPosition(pos);
    buttons[select].setPosition(pos);
}

// sets text size at given index to specified size
void Menu::setCharSize(int select, int size)
{
    textMenu[select].setCharacterSize(size);
}


#endif  // MENU_H