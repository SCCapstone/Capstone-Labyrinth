/* Copyright 2020 Carson Stabell */
/* Main Menu class (in header file) */

#ifndef MAINMENU_H
#define MAINMENU_H

#include "SFML/Graphics.hpp"
#include "Menu.h"

class MainMenu
{
      private:
      sf::RenderWindow* window;
      Menu* menu;
      const float DEFAULT_WIDTH = 600;
      const float DEFAULT_HEIGHT = 600;

      void initMainMenu(float width, float height);


      public:
      MainMenu();
      MainMenu(float width, float height);
      ~MainMenu();

      void update();
      void render();

      const bool running() const {
        return window->isOpen();
      }

      
};

MainMenu::MainMenu()
{
      initMainMenu(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}
MainMenu::MainMenu(float width, float height)
{
      initMainMenu(width, height);
}
MainMenu::~MainMenu()
{
      //Do the destructing
}

void MainMenu::initMainMenu(float width, float height)
{
      this->window = new sf::RenderWindow(sf::VideoMode(width,height), "Main Menu");
      this->menu = new Menu(width, height);
}

void MainMenu::update()
{
      sf::Event event;

      while(window->pollEvent(event))
      {
            switch(event.type)
            {
            case sf::Event::KeyReleased:
                  switch(event.key.code)
                  {
                        case sf::Keyboard::Up:
                        menu->MoveUp();
                        break;

                        case sf::Keyboard::Down:
                        menu->MoveDown();
                        break;

                        default:
                        break;
                  }
                  break;
            case sf::Event::Closed:
                  window->close();
                  break;
            default:
                  break;

            }
      }
}
void MainMenu::render()
{
      window->clear();

      menu->draw(*window);

      window->display();
}

#endif //MAINMENU_H