/* Copyright 2020 Carson Stabell */
/* Menu class (in header file) */

#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
      public:
      Menu();
      Menu(float width, float height);
      ~Menu();

      void draw(sf::RenderWindow &window);
      void MoveUp();
      void MoveDown();

      private:
      int selectedItemIndex;
      sf::Font font;
      sf::Text menu[MAX_NUMBER_OF_ITEMS];
      const float DEFAULT_WIDTH = 600;
      const float DEFAULT_HEIGHT = 600;

};

Menu::Menu()
{
      Menu(DEFAULT_WIDTH,DEFAULT_HEIGHT);
}
Menu::Menu(float width, float height)
{
      if(!font.loadFromFile("text/NotPapayrus.ttf"))
      {/*Handle Error */}

      selectedItemIndex = 0;

      menu[0].setFont(font);
      menu[0].setColor(sf::Color::Red);
      menu[0].setString("Play");
      menu[0].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS + 1) * 1));

      menu[1].setFont(font);
      menu[1].setColor(sf::Color::White);
      menu[1].setString("Options");
      menu[1].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS + 1) * 2));

      menu[2].setFont(font);
      menu[2].setColor(sf::Color::White);
      menu[2].setString("Exit");
      menu[2].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS + 1) * 3));
}

Menu::~Menu()
{/*Does nothing atm*/}

void Menu::draw(sf::RenderWindow &window)
{
      for(int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
      {
            window.draw(menu[i]);
      }
}

void Menu::MoveUp()
{
      if(selectedItemIndex-1 >= 0)
      {
            menu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex--;
            menu[selectedItemIndex].setColor(sf::Color::Red);
      }
}

void Menu::MoveDown()
{
      if(selectedItemIndex+1 < MAX_NUMBER_OF_ITEMS)
      {
            menu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex++;
            menu[selectedItemIndex].setColor(sf::Color::Red);
      }
}