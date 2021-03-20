/* Copyright 2021 Samuel Dunny */
/* Exit page class (in header file) */

#ifndef EXIT_PAGE_H
#define EXIT_PAGE_H

#include "SFML/Graphics.hpp"

class Exit_Page {
    // private attributes
private:
    sf::Text instructs;
    sf::Font font;                      // variable for the font for our menu text

    bool lost;

    // public attributes
public:
    // default constructor
    Exit_Page(float factor);

    // destructor
    ~Exit_Page();

    // render function that draws text, displays them
    void Render(sf::RenderWindow& window,  Vector2f coords);
    void setLost(bool cond) { 
        this->lost = cond;
        setMsg(cond);
    }

    void setMsg(bool lost);

    void setTextSize();
};

// default constructor
Exit_Page::Exit_Page(float factor) {
    // load text texture
    if (!font.loadFromFile("txts/NotPapayrus.ttf")) {
        std::cout << "Text did not load" << std::endl;
    }
    // assume you havent lost yet
    lost = false;
    this->instructs.setFont(font);
    this->instructs.setFillColor(sf::Color::Red);
    this->instructs.setOutlineColor(sf::Color::Black);
    this->instructs.setOutlineThickness(10);

    this->instructs.setCharacterSize(factor / 13);
    this->instructs.setOutlineThickness(factor / 52);
}

// destructor
Exit_Page::~Exit_Page() { /* intentionally empty */ }

// render function that draws text, displays them
void Exit_Page::Render(RenderWindow& window, Vector2f coords) {
    this->instructs.setOrigin(sf::Vector2f(instructs.getLocalBounds().width / 2,
        instructs.getLocalBounds().height / 2));
    this->instructs.setPosition(coords);
    window.draw(instructs);
}

void Exit_Page::setMsg(bool youLost) {
    if (youLost)
        this->instructs.setString("YOU HAVE BEEN TAKEN\n\t\t\tBY THE MAZE");
    else
        this->instructs.setString("YOU HAVE WON");
}


#endif	// EXIT_PAGE_H