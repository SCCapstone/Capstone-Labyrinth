/* Copyright 2020 Carson Stabell */
/* Options Menu class (in header file) */

#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "SFML/Graphics.hpp"
#include "Menu.h"

class OptionsMenu
{
      private:
      sf::RenderWindow* window;
      Menu* menu;
      sf::Texture backgroundTex;
      sf::Sprite background;
      const float DEFAULT_WIDTH = 600;
      const float DEFAULT_HEIGHT = 600;

      void initOptionsMenu(float width, float height);


      public:
      OptionsMenu();
      OptionsMenu(float width, float height);
      ~OptionsMenu();

      int update();
      void render();

      const bool running() const {
        return window->isOpen();
      }

      
};

OptionsMenu::OptionsMenu()
{
      initOptionsMenu(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}
OptionsMenu::OptionsMenu(float width, float height)
{
      initOptionsMenu(width, height);
}
OptionsMenu::~OptionsMenu()
{
      //Do the destructing
}

void OptionsMenu::initOptionsMenu(float width, float height)
{
      this->window = new sf::RenderWindow(sf::VideoMode((unsigned int)width, (unsigned int)height), "Options Menu");
      this->menu = new Menu(width, height, 5);

      //Sets default perams for main menu Text
      menu->setText(0, "Effects");
      menu->setText(1, "Music");
      menu->setText(2, "Graphics");
      menu->setText(3, "Size");
      menu->setText(4, "Exit");

      if (!(backgroundTex.loadFromFile("imgs/options_background.png")))
      {
          std::cout << "Background did not load" << std::endl;
      }
      background.setTexture(backgroundTex);
      background.setScale(2.5, 2.5);
}

int OptionsMenu::update()
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
                        case sf::Keyboard::W:
                        menu->MoveUp();
                        break;

                        case sf::Keyboard::Down:
                        menu->MoveDown();
                        break;
                        case sf::Keyboard::S:
                        menu->MoveDown();
                        break;

                        case sf::Keyboard::Enter:
                        switch(menu->getSelection())
                        {
                              case 0:
                              //Sssssshhhh options soon
                              break;

                              case 4:
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
            case sf::Event::Closed:
                  window->close();
                  break;
            default:
                  break;

            }
      }
      return -1;
}
void OptionsMenu::render()
{
      window->clear();
      window->draw(background);

      menu->render(*window);

      window->display();
}

#endif //OPTIONSMENU_H