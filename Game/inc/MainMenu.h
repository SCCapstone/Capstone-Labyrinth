/* Copyright 2020 Carson Stabell */
/* Main Menu class (in header file) */

#ifndef MAINMENU_H
#define MAINMENU_H

#include "OptionsMenu.h"
#include <iostream>
#include <vector>

class MainMenu
{
      private:
      sf::RenderWindow* window;
      Menu* menu;
      const float DEFAULT_WIDTH = 600;
      const float DEFAULT_HEIGHT = 600;
      const int DEFAULT_NUM_MENU_ITEMS = 3;

      //Sprite Stuff
      sf::Texture titleTex;
//      sf::Texture bButtonTex; //blank button texture
      sf::Sprite* title;
 //     std::vector<sf::Sprite> buttons;
      sf::Texture backgroundTex;
      sf::Sprite background;

      void initMainMenu(float width, float height, int numMenuItems, sf::RenderWindow* win);
      void runOptionsMenu();


      public:
      MainMenu();
      MainMenu(float width, float height);
      MainMenu(sf::RenderWindow* win);
      ~MainMenu();

      int update();
      void render();

      const bool running() const {
        return window->isOpen();
      }

      
};

MainMenu::MainMenu()
{
      initMainMenu(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_NUM_MENU_ITEMS, NULL);
}
MainMenu::MainMenu(float width, float height)
{
      initMainMenu(width, height, DEFAULT_NUM_MENU_ITEMS, NULL);
}
MainMenu::MainMenu(sf::RenderWindow* win)
{
    initMainMenu(0, 0, DEFAULT_NUM_MENU_ITEMS, win);
}
MainMenu::~MainMenu()
{
      //Do the destructing
}
#pragma optimize("", off)
void MainMenu::initMainMenu(float width, float height, int numMenuItems, sf::RenderWindow* win)
{
    if (win != NULL) {
        this->window = win;
        width = (float)window->getSize().x;
        height = (float)window->getSize().y;
    }
    else {
        this->window = new sf::RenderWindow(sf::VideoMode((unsigned int)width, (unsigned int)height), "Main Menu");
    }
      this->menu = new Menu(width, height, numMenuItems);

      //Sets default perams for main menu Text
      menu->setText(0, "Enter the Labyrinth");
      menu->setText(1, "Options ");
      menu->setText(2, "Surrender to the Labyrinth");
      float middle = width/3 - 20.0f; //just gets the middle, not dynamic yet
     //Setup the Title
      if(!(titleTex.loadFromFile("imgs/title_logo.png")))
      {std::cout << "Title did not load" << std::endl;}
      title = new sf::Sprite();
      title->setTexture(titleTex);
      title->setScale(1.5, 1.5);
      title->setOrigin(sf::Vector2f(20.0f, 20.0f));
      title->setPosition(sf::Vector2f(middle, 0.0F));
      /*
      //Setup buttons
      if(!(bButtonTex.loadFromFile("imgs/blank_button.png")))
      {std::cout << "Blank Button did not load" << std::endl;}
      buttons.resize(numMenuItems);
      for(auto i = 0; i < buttons.size(); i++)
      {
            buttons[i].setTexture(bButtonTex);
            buttons[i].setPosition(sf::Vector2f(middle, height/5 * (i+2)));
            buttons[i].setOrigin(sf::Vector2f(25.0f, 50.0f));
            buttons[i].setScale(1.2f, 1.2f);
            menu->setCharSize(i, 20);
      }*/
      menu->setPos(0, sf::Vector2f(middle + 40.0f, height/5 * (0+2) + 11.0f));
      menu->setPos(1, sf::Vector2f(middle + 85.0f, height/5 * (1+2) + 11.0f));
      menu->setPos(2, sf::Vector2f(middle + 10.0f, height/5 * (2+2) + 11.0f));
      
      if (!(backgroundTex.loadFromFile("imgs/wall.png")))
      {
          std::cout << "Background did not load" << std::endl;
      }
      background.setTexture(backgroundTex);
      background.setScale(15, 15);
}
#pragma optimize("", on)


int MainMenu::update()
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
                              //Play is just close window rn
                              window->close();
                              return 0;
                              break;

                              case 1:
                              //Do the options screen
                              runOptionsMenu();
                              break;

                              case 2:
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
            case sf::Event::Closed:
                  window->close();
                  break;
            default:
                  break;

            }
      }
      return -1;
}
void MainMenu::render()
{
      window->clear();
      window->draw(background);
      
      window->draw(*title);
      /*for(int i = 0; i < buttons.size(); i++)
      {
            window->draw(buttons[i]);
            menu->draw(*window);
      }*/
      menu->render(*window);

      window->display();
}

void MainMenu::runOptionsMenu()
{
      OptionsMenu options;
      int optionsReturn = -1;
      while(options.running())
      {
            options.update();
            options.render();
      }
}

#endif //MAINMENU_H