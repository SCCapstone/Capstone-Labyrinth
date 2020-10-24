// by Sam Dunny
#include <SFML/Graphics.hpp>    // for sfml methods
#include <unistd.h>             // for usleep
#include <iostream>             // for output

#define width 52
#define length 66

// sprite image from internet: https://koenig-media.raywenderlich.com/uploads/2012/06/PixelArtTutorial.png

int main()
{
    // create window with size 400x400
    sf::RenderWindow window(sf::VideoMode(800, 800), "Sprite");
    window.clear(sf::Color::White);

    // sprite texture i pulled for the internet
    sf::Texture text;
    text.loadFromFile("sprite2.png");
    // 0, 160, 120, 100
    if (!text.loadFromFile("sprite2.png", sf::IntRect(0, 0,width, length))) {
        std::cout << "ERROR" << std::endl;
    }
    text.setSmooth(true);

    // Sprite frederick facing right
    sf::Sprite frederick_r;
    frederick_r.setTexture(text);
    frederick_r.setOrigin(75,50);
    frederick_r.setPosition(200, 400);

    // Sprite frederick faciung left
    sf::Sprite frederick_l;
    frederick_l.setTexture(text);
    frederick_l.scale(-1.f,1.f);
    frederick_l.setOrigin(75,50);
    frederick_l.setPosition(600, 400);

    int fight_time = 1;

    // main loop
    while (window.isOpen())
    {
        // creates event 
        sf::Event event;

        // constantly polls window event
        while (window.pollEvent(event))
        {
            // if event = closed, close window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // western movement
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

            if (frederick_r.getGlobalBounds().intersects(frederick_l.getGlobalBounds())) {
                std::cout << "The Fredericks are fighting for the " << fight_time << " time" << std::endl;
                fight_time++;
                // bounce sprite east
                frederick_r.move(4,0);
            } else {
                window.clear();
                // move sprite 
                frederick_r.move(-1,0);
                window.draw(frederick_r);
                window.draw(frederick_l);
                window.display();

                // north western movement
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    if (frederick_r.getGlobalBounds().intersects(frederick_l.getGlobalBounds())) {
                        std::cout << "The Fredericks are fighting for the " << fight_time << " time" << std::endl;
                        fight_time++;
                        // bounce sprite 
                        frederick_r.move(4,4);
                    } else {
                    window.clear();
                    // move sprite north west
                    frederick_r.move(-1,-1);
                    window.draw(frederick_r);
                    window.draw(frederick_l);
                    window.display();
                    usleep(1000);
                    }
                }

                // south western movement
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    if (frederick_r.getGlobalBounds().intersects(frederick_l.getGlobalBounds())) {
                        std::cout << "The Fredericks are fighting for the " << fight_time << " time" << std::endl;
                        fight_time++;
                        // bounce sprite north east
                        frederick_r.move(4,-4);
                    } else {
                        window.clear();
                        // move sprite south west
                        frederick_r.move(-1,1);
                        window.draw(frederick_r);
                        window.draw(frederick_l);
                        window.display();
                        usleep(1000);
                    }
                }
                usleep(1000);
            }
        }
        
        // eastern movement
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            
            if (frederick_r.getGlobalBounds().intersects(frederick_l.getGlobalBounds())) {
                std::cout << "The Fredericks are fighting for the " << fight_time << " time" << std::endl;
                fight_time++;
                // bounce sprite west
                frederick_r.move(-4,0);
            } else {
                window.clear();
                // move sprite east
                frederick_r.move(1,0);
                window.draw(frederick_r);
                window.draw(frederick_l);
                window.display();
            
                // north eastern movement
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    if (frederick_r.getGlobalBounds().intersects(frederick_l.getGlobalBounds())) {
                        std::cout << "The Fredericks are fighting for the " << fight_time << " time" << std::endl;
                        fight_time++;
                        // bounce sprite south west
                        frederick_r.move(-4,4);
                    } else {
                        window.clear();
                        // move sprite north east
                        frederick_r.move(1,-1);
                        window.draw(frederick_r);
                        window.draw(frederick_l);
                        window.display();
                    }
                    usleep(1000);
                }

                // south eastern movement
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                     if (frederick_r.getGlobalBounds().intersects(frederick_l.getGlobalBounds())) {
                        std::cout << "The Fredericks are fighting for the " << fight_time << " time" << std::endl;
                        fight_time++;
                        // bounce north west
                        frederick_r.move(-4,-4);
                    } else {
                        window.clear();
                        // move sprite south east
                        frederick_r.move(1,1);
                        window.draw(frederick_r);
                        window.draw(frederick_l);
                        window.display();
                    }
                    usleep(1000);
                }
            }
            usleep(1000);
        }

        // northern movement
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            
            if (frederick_r.getGlobalBounds().intersects(frederick_l.getGlobalBounds())) {
                std::cout << "The Fredericks are fighting for the " << fight_time << " time" << std::endl;
                fight_time++;
                // bounce sprite south
                frederick_r.move(0,4);
            } else {
                window.clear();
                // move sprite north
                frederick_r.move(0,-1);
                window.draw(frederick_r);
                window.draw(frederick_l);
                window.display();
            
                // north eastern movement
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    if (frederick_r.getGlobalBounds().intersects(frederick_l.getGlobalBounds())) {
                        std::cout << "The Fredericks are fighting for the " << fight_time << " time" << std::endl;
                        fight_time++;
                        // bounce sprite south west
                        frederick_r.move(-4,4);
                    } else {
                        window.clear();
                        // move sprite north east
                        frederick_r.move(1,-1);
                        window.draw(frederick_r);
                        window.draw(frederick_l);
                        window.display();
                    }
                    usleep(1000);
                }

                // north western movement
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                     if (frederick_r.getGlobalBounds().intersects(frederick_l.getGlobalBounds())) {
                        std::cout << "The Fredericks are fighting for the " << fight_time << " time" << std::endl;
                        fight_time++;
                        // bounce south east
                        frederick_r.move(4,4);
                    } else {
                        window.clear();
                        // move sprite north west
                        frederick_r.move(-1,-1);
                        window.draw(frederick_r);
                        window.draw(frederick_l);
                        window.display();
                    }
                    usleep(1000);
                }
            }
            usleep(1000);
        }

        // southern movement
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            
            if (frederick_r.getGlobalBounds().intersects(frederick_l.getGlobalBounds())) {
                std::cout << "The Fredericks are fighting for the " << fight_time << " time" << std::endl;
                fight_time++;
                // bounce sprite south
                frederick_r.move(0,-4);
            } else {
                window.clear();
                // move sprite north
                frederick_r.move(0,1);
                window.draw(frederick_r);
                window.draw(frederick_l);
                window.display();
            
                // south eastern movement
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    if (frederick_r.getGlobalBounds().intersects(frederick_l.getGlobalBounds())) {
                        std::cout << "The Fredericks are fighting for the " << fight_time << " time" << std::endl;
                        fight_time++;
                        // bounce sprite south west
                        frederick_r.move(-4,4);
                    } else {
                        window.clear();
                        // move sprite north east
                        frederick_r.move(1,1);
                        window.draw(frederick_r);
                        window.draw(frederick_l);
                        window.display();
                    }
                    usleep(1000);
                }

                // south western movement
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                     if (frederick_r.getGlobalBounds().intersects(frederick_l.getGlobalBounds())) {
                        std::cout << "The Fredericks are fighting for the " << fight_time << " time" << std::endl;
                        fight_time++;
                        // bounce north east
                        frederick_r.move(4,-4);
                    } else {
                        window.clear();
                        // move sprite south west
                        frederick_r.move(-1,1);
                        window.draw(frederick_r);
                        window.draw(frederick_l);
                        window.display();
                    }
                    usleep(1000);
                }
            }
            usleep(1000);
        }

        // cleans the window each loop
        window.clear();
        window.draw(frederick_r);
        window.draw(frederick_l);
        window.display();
        usleep(100000); 
    }

    return 0;
}