/* Copyright 2020 Carson Stabell */
/* Menu class (in header file) */

#ifndef MENU_H
#define MENU_H

#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>

#define DEFAULT_NUMBER_OF_ITEMS 3

class Menu
{
      public:
      Menu();
      Menu(float width, float height);
      Menu(float width, float height, int size);
      ~Menu();

      void draw(sf::RenderWindow &window);
      void MoveUp();
      void MoveDown();

      void setText(int selectionn, std::string words);
      int getSelection();

      private:
      int selectedItemIndex;
      int menuSize;
      sf::Font font;
      std::vector<sf::Text> textMenu;

      const float DEFAULT_WIDTH = 600;
      const float DEFAULT_HEIGHT = 600;

};

Menu::Menu() : Menu::Menu(DEFAULT_WIDTH, DEFAULT_HEIGHT) {}

Menu::Menu(float width, float height)
{
      if(!font.loadFromFile("text/NotPapayrus.ttf"))
      {/*Handle Error */}

      selectedItemIndex = 0;

      menuSize = DEFAULT_NUMBER_OF_ITEMS;
      textMenu.resize(menuSize);

      textMenu[0].setFont(font);
      textMenu[0].setColor(sf::Color::White);
      textMenu[0].setString("Play");
      textMenu[0].setPosition(sf::Vector2f(width/2, height/(menuSize + 1) * 1));

      textMenu[1].setFont(font);
      textMenu[1].setColor(sf::Color::White);
      textMenu[1].setString("Options");
      textMenu[1].setPosition(sf::Vector2f(width/2, height/(menuSize + 1) * 2));

      textMenu[2].setFont(font);
      textMenu[2].setColor(sf::Color::White);
      textMenu[2].setString("Exit");
      textMenu[2].setPosition(sf::Vector2f(width/2, height/(menuSize + 1) * 3));
}

//Handles textMenu with varying textMenu options
Menu::Menu(float width, float height, int size)
{
      if(!font.loadFromFile("text/NotPapayrus.ttf"))
      {std::cout << "Could not load text" << std::endl;}

      menuSize = size;
      
      textMenu.assign(menuSize, sf::Text());

      for(int i = 0; i < menuSize; i++)
      {
            textMenu[i].setFont(font);
            textMenu[i].setColor(sf::Color::White);
            textMenu[i].setString("Null");
            textMenu[i].setPosition(sf::Vector2f(width/2, height/(menuSize + 1) * (i+1)));
      }

      //Sets first entry as default selection and makes red
      selectedItemIndex = 0;
      textMenu[0].setColor(sf::Color::Red);
}

Menu::~Menu()
{/*Does nothing atm*/}

void Menu::draw(sf::RenderWindow &window)
{
      for(int i = 0; i < menuSize; i++)
      {
            window.draw(textMenu[i]);
      }
}

void Menu::MoveUp()
{
      if(selectedItemIndex-1 >= 0)
      {
            textMenu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex--;
            textMenu[selectedItemIndex].setColor(sf::Color::Red);
      }
}

void Menu::MoveDown()
{
      if(selectedItemIndex+1 < menuSize)
      {
            textMenu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex++;
            textMenu[selectedItemIndex].setColor(sf::Color::Red);
      }
}

void Menu::setText(int selection, std::string words)
{
      textMenu[selection].setString(words);
}

int Menu::getSelection()
{
      return selectedItemIndex;
}

#endif