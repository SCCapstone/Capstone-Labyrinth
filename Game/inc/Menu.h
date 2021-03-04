/* Copyright 2020 Carson Stabell */
/* Menu class (in header file) */

// Edit by Sam Dunny: .setColor() method was deprecated, replaced with .setFillColor() (2/2/21)

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

      void render(sf::RenderWindow &window);
      void MoveUp();
      void MoveDown();

      void setText(int selectionn, std::string words);
      int getSelection();
      void setPos(int, sf::Vector2f);
      void setOri(int, sf::Vector2f);
      void setCharSize(int, int);

      private:
      int selectedItemIndex;
      int menuItems;
      sf::Font font;
      sf::Texture bButtonTex;
      std::vector<sf::Text> textMenu;
      std::vector<sf::Sprite> buttons;
      

      const float DEFAULT_WIDTH = 600;
      const float DEFAULT_HEIGHT = 600;

};

Menu::Menu() : Menu::Menu(DEFAULT_WIDTH, DEFAULT_HEIGHT) {}

Menu::Menu(float width, float height)
{
      if(!font.loadFromFile("txts/NotPapayrus.ttf"))
      {/*Handle Error */}

      selectedItemIndex = 0;

      menuItems = DEFAULT_NUMBER_OF_ITEMS;
      textMenu.resize(menuItems);

      textMenu[0].setFont(font);
      textMenu[0].setFillColor(sf::Color::White);
      textMenu[0].setString("Play");
      textMenu[0].setPosition(sf::Vector2f(width/2, height/(menuItems + 1) * 1));

      textMenu[1].setFont(font);
      textMenu[1].setFillColor(sf::Color::White);
      textMenu[1].setString("Options");
      textMenu[1].setPosition(sf::Vector2f(width/2, height/(menuItems + 1) * 2));

      textMenu[2].setFont(font);
      textMenu[2].setFillColor(sf::Color::White);
      textMenu[2].setString("Exit");
      textMenu[2].setPosition(sf::Vector2f(width/2, height/(menuItems + 1) * 3));
}

//Handles textMenu with varying textMenu options
Menu::Menu(float width, float height, int size)
{
      if(!font.loadFromFile("txts/NotPapayrus.ttf"))
      {std::cout << "Could not load text" << std::endl;}

      menuItems = size;
      
      textMenu.assign(menuItems, sf::Text());

      for(int i = 0; i < menuItems; i++)
      {
            textMenu[i].setFont(font);
            textMenu[i].setFillColor(sf::Color::White);
            textMenu[i].setString("Null");
            textMenu[i].setPosition(sf::Vector2f(width/2, height/(menuItems + 1) * (i+1)));
            textMenu[i].setCharacterSize(20);
      }

      //Sets first entry as default selection and makes red
      selectedItemIndex = 0;
      textMenu[0].setFillColor(sf::Color::Red);

      //Setup buttons
      if (!(bButtonTex.loadFromFile("imgs/blank_button.png")))
      {
          std::cout << "Blank Button did not load" << std::endl;
      }
      buttons.resize(menuItems);
      for (auto i = 0; i < buttons.size(); i++)
      {
          buttons[i].setTexture(bButtonTex);
          buttons[i].setPosition(sf::Vector2f(textMenu[i].getGlobalBounds().left, textMenu[i].getGlobalBounds().top));
         /* buttons[i].setOrigin(sf::Vector2f(
              (buttons[i].getLocalBounds().width/2) - (textMenu[i].getLocalBounds().width/2),   //Should Dynamically adjust
              buttons[i].getLocalBounds().height/2 - textMenu[i].getLocalBounds().height/2));*/ //the buttons to center the text
          buttons[i].setScale(1.2f, 1.2f);
         
      }
     /* buttons[0].setOrigin(sf::Vector2f(20, 10));
      buttons[1].setOrigin(sf::Vector2f(50, 10));
      buttons[2].setOrigin(sf::Vector2f(20, 10));*/


      
      
}

Menu::~Menu()
{/*Does nothing atm*/}

void Menu::render(sf::RenderWindow &window)
{
      for(int i = 0; i < menuItems; i++)
      {
            window.draw(buttons[i]);
            window.draw(textMenu[i]);
      }
}

void Menu::MoveUp()
{
      if(selectedItemIndex-1 >= 0)
      {
            textMenu[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex--;
            textMenu[selectedItemIndex].setFillColor(sf::Color::Red);
      }
}

void Menu::MoveDown()
{
      if(selectedItemIndex+1 < menuItems)
      {
            textMenu[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex++;
            textMenu[selectedItemIndex].setFillColor(sf::Color::Red);
      }
}

void Menu::setText(int selection, std::string words)
{
      textMenu[selection].setString(words);
      for (auto i = 0; i < buttons.size(); i++) {
          buttons[i].setOrigin(sf::Vector2f(
              0 + (buttons[i].getGlobalBounds().width / 2) - (textMenu[i].getGlobalBounds().width / 2),   //Should Dynamically adjust
              (buttons[i].getGlobalBounds().height / 2) - (textMenu[i].getGlobalBounds().height - 5.0))); //the buttons to center the text
         /* std::cout << i << " " << 
              (buttons[i].getGlobalBounds().width / 2) - (textMenu[i].getGlobalBounds().width / 2) << " " <<
              buttons[i].getGlobalBounds().height / 2 - textMenu[i].getGlobalBounds().height / 2 << std::endl;
          std::cout << (buttons[i].getGlobalBounds().width / 2) << " " << (textMenu[i].getGlobalBounds().width / 2) << " " <<
              buttons[i].getGlobalBounds().height / 2 << " " << textMenu[i].getGlobalBounds().height / 2 << std::endl; */
      }

}

int Menu::getSelection()
{
      return selectedItemIndex;
}

void Menu::setPos(int select, sf::Vector2f pos)
{
      textMenu[select].setPosition(pos);
      buttons[select].setPosition(pos);
    //  buttons[select].setPosition(sf::Vector2f(textMenu[select].getGlobalBounds().left, textMenu[select].getGlobalBounds().top));
      
     /* for (auto i = 0; i < textMenu.size(); i++) {
          std::cout << "text Coords" << textMenu[i].getGlobalBounds().width << " " << textMenu[i].getGlobalBounds().height << std::endl;
          std::cout << "buttons Coords" << buttons[i].getGlobalBounds().width << " " << buttons[i].getGlobalBounds().height << std::endl;

          std::cout << "Text pos" << textMenu[i].getPosition().x << " " << textMenu[i].getPosition().y << "Button pos" << buttons[i].getPosition().x << " " << buttons[i].getPosition().y << std::endl;
      }*/
}

void Menu::setOri(int select, sf::Vector2f pos)
{
      textMenu[select].setOrigin(pos);
     // buttons[select].setOrigin(sf::Vector2f(textMenu[select].getGlobalBounds().left, textMenu[select].getGlobalBounds().top));

}

void Menu::setCharSize(int select, int size)
{
      textMenu[select].setCharacterSize(size);
}

#endif