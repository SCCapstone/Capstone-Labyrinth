/* Copyright 2020 Samuel Dunny */
/* Game Engine class (in header file) */

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Player.h"
#include "Enemy_Spawner.h"
#include "Wall.h"
#include <ctime>

using sf::View;
using sf::VideoMode;
using sf::Event;
using sf::Clock;
using sf::Color;

/* Class that acts as game engine
 * Creates window
 * Creates player
 * Creates enemy spawner
 * Creates 2 wall instances
 */

// how many minotaurs to spawn
const static int minotaur_amount = 2;

class Game_Engine {
// private attributes
private:
    // variables for window creation
    RenderWindow* window;
    VideoMode videoMode;

    // variable for event checking
    Event ev;

    // variables for main character
    Player* player;
    View player_view;
    Texture base_movement;

    // variables for enemy character
    Enemy_Spawner* minotaurs;
    Texture min_texture;

    // wall variables
    //Wall* wall_one;
    //Wall* wall_two;
    //== [ walls section 1 ] ==
    Wall* wall_I1;
    Wall* wall_B2;
    Wall* wall_D2;
    Wall* wall_F2;
    Wall* wall_K2;
    Wall* wall_N2;
    Wall* wall_Q2;
    Wall* wall_E3;
    Wall* wall_H3;
    Wall* wall_O3;
    Wall* wall_D4;
    Wall* wall_K4;
    Wall* wall_R4;
    Wall* wall_A5;
    Wall* wall_G5;
    Wall* wall_J5;
    Wall* wall_N5;
    Wall* wall_P5;
    Wall* wall_D6;
    Wall* wall_K6;
    Wall* wall_S6;
    Wall* wall_E7;
    Wall* wall_G7;
    Wall* wall_N7;
    Wall* wall_P7;
    Wall* wall_C8;
    Wall* wall_H8;
    Wall* wall_J8;
    Wall* wall_R8;
    Wall* wall_E9;
    Wall* wall_L9;
    Wall* wall_O9;
    Wall* wall_G10;
    Wall* wall_J10;
    Wall* wall_P10;
    Wall* wall_D11;
    Wall* wall_M11;
    Wall* wall_G12;
    Wall* wall_J12;
    Wall* wall_N12;
    Wall* wall_F13;
    // == [ walls section 2 ] ==
    Wall* wall_R1;
    Wall* wall_U1;
    Wall* wall_W1;
    Wall* wall_X2;
    Wall* wall_S3;
    Wall* wall_U4;
    Wall* wall_X4;
    Wall* wall_Y5;
    Wall* wall_U6;
    Wall* wall_T7;
    Wall* wall_X7;
    Wall* wall_Y8;
    Wall* wall_V9;
    Wall* wall_A10;
    Wall* wall_S10;
    Wall* wall_W10;
    Wall* wall_Z10;
    Wall* wall_B11;
    Wall* wall_P11;
    Wall* wall_V11;
    Wall* wall_C12;
    Wall* wall_T12;
    Wall* wall_X12;
    Wall* wall_Z12;
    Wall* wall_B13;
    Wall* wall_L13;
    Wall* wall_Q13;
    Wall* wall_U13;
    Wall* wall_E14;
    Wall* wall_H14;
    Wall* wall_K14;
    Wall* wall_N14;
    Wall* wall_R14;
    Wall* wall_V14;
    Wall* wall_B15;
    Wall* wall_D15;
    Wall* wall_Q15;
    Wall* wall_T15;
    Wall* wall_E16;
    Wall* wall_H16;
    Wall* wall_K16;
    Wall* wall_M16;
    Wall* wall_I17;

    Texture brickwall;

    // using these so animation runs at same rate irrespective of machine
    float deltaTime;
    Clock clock;

    // initializer functions
    void initVariables();
    void initPlayer();
    void initEnemies();
    void initWalls();
    void initWindow();

    void ResizeView(const RenderWindow& window, View& view);

    void pollEvents();

    void WallContactUpdate(Individual* character, Wall* aWall, float push);

    // function to test if Individuals exist (player, enemy, etc.)
    bool exists(Individual* other) {
      if (other != nullptr)
         return true;
      return false;
   }
    
// public attributes 
public:
    Game_Engine();

    ~Game_Engine();

    void Update();

    void Render();

    // accessors, returns true if window is still open
    const bool running() const {
        return window->isOpen();
    }
};

/* Public Functions in order:
 * Game_Engine:     default constructor, calls all initializer functions
 * ~Game_Engine:    destructor, deletes dynamic objects
 * Update:          updates all game logic (interations between players, enemies, the environment, and movement in the window)
 * Render:          draws and displays all game objects (player, enemies, walls)
 */
Game_Engine::Game_Engine() {
    std::cout << "-----STARTING INITIALIZATION-----" << std::endl;

    // initializes
    initVariables();
    initWindow();

    std::cout << "-----INITIALIZATION FINISHED-----\n" << std::endl;
}

Game_Engine::~Game_Engine() { 
    delete this->window;

    delete this->player;

    // dont need destructor for enemies

    // temporary wall stuff
    //delete this->wall_one;
    //delete this->wall_two;
    delete this->wall_I1;
    delete this->wall_B2;
    delete this->wall_D2;
    delete this->wall_F2;
    delete this->wall_K2;
    delete this->wall_N2;
    delete this->wall_Q2;
    delete this->wall_E3;
    delete this->wall_H3;
    delete this->wall_O3;
    delete this->wall_D4;
    delete this->wall_K4;
    delete this->wall_R4;
    delete this->wall_A5;
    delete this->wall_G5;
    delete this->wall_J5;
    delete this->wall_N5;
    delete this->wall_P5;
    delete this->wall_D6;
    delete this->wall_K6;
    delete this->wall_S6;
    delete this->wall_E7;
    delete this->wall_G7;
    delete this->wall_N7;
    delete this->wall_P7;
    delete this->wall_C8;
    delete this->wall_H8;
    delete this->wall_J8;
    delete this->wall_R8;
    delete this->wall_E9;
    delete this->wall_L9;
    delete this->wall_O9;
    delete this->wall_G10;
    delete this->wall_J10;
    delete this->wall_P10;
    delete this->wall_D11;
    delete this->wall_M11;
    delete this->wall_G12;
    delete this->wall_J12;
    delete this->wall_N12;
    delete this->wall_F13;

    delete this->wall_R1;
    delete this->wall_U1;
    delete this->wall_W1;
    delete this->wall_X2;
    delete this->wall_S3;
    delete this->wall_U4;
    delete this->wall_X4;
    delete this->wall_Y5;
    delete this->wall_U6;
    delete this->wall_T7;
    delete this->wall_X7;
    delete this->wall_Y8;
    delete this->wall_V9;
    delete this->wall_A10;
    delete this->wall_S10;
    delete this->wall_W10;
    delete this->wall_Z10;
    delete this->wall_B11;
    delete this->wall_P11;
    delete this->wall_V11;
    delete this->wall_C12;
    delete this->wall_T12;
    delete this->wall_X12;
    delete this->wall_Z12;
    delete this->wall_B13;
    delete this->wall_L13;
    delete this->wall_Q13;
    delete this->wall_U13;
    delete this->wall_E14;
    delete this->wall_H14;
    delete this->wall_K14;
    delete this->wall_N14;
    delete this->wall_R14;
    delete this->wall_V14;
    delete this->wall_B15;
    delete this->wall_D15;
    delete this->wall_Q15;
    delete this->wall_T15;
    delete this->wall_E16;
    delete this->wall_H16;
    delete this->wall_K16;
    delete this->wall_M16;
    delete this->wall_I17;
}

void Game_Engine::Update() {
    // used in the update function
    deltaTime = clock.restart().asSeconds();

    // poll events
    pollEvents();

    // update player information if it exists
    if (exists(player)) {
        // .Update() responds to keyboard input and updates the player in the respective direction
        player->Update(deltaTime);

        // must call this after player.Update(), otherwise cammera stutters
        player_view.setCenter(this->player->getIndividualPos());

        // makes wall the immovable object to player


        //WallContactUpdate(player, wall_one, 1.0f);
        //WallContactUpdate(player, wall_two, 1.0f);

        WallContactUpdate(player, wall_I1, 1.0f);
        WallContactUpdate(player, wall_B2, 1.0f);
        WallContactUpdate(player, wall_D2, 1.0f);
        WallContactUpdate(player, wall_F2, 1.0f);
        WallContactUpdate(player, wall_K2, 1.0f);
        WallContactUpdate(player, wall_N2, 1.0f);
        WallContactUpdate(player, wall_Q2, 1.0f);
        WallContactUpdate(player, wall_E3, 1.0f);
        WallContactUpdate(player, wall_H3, 1.0f);
        WallContactUpdate(player, wall_O3, 1.0f);
        WallContactUpdate(player, wall_D4, 1.0f);
        WallContactUpdate(player, wall_K4, 1.0f);
        WallContactUpdate(player, wall_R4, 1.0f);
        WallContactUpdate(player, wall_A5, 1.0f);
        WallContactUpdate(player, wall_G5, 1.0f);
        WallContactUpdate(player, wall_J5, 1.0f);
        WallContactUpdate(player, wall_N5, 1.0f);
        WallContactUpdate(player, wall_P5, 1.0f);
        WallContactUpdate(player, wall_D6, 1.0f);
        WallContactUpdate(player, wall_K6, 1.0f);
        WallContactUpdate(player, wall_S6, 1.0f);
        WallContactUpdate(player, wall_E7, 1.0f);
        WallContactUpdate(player, wall_G7, 1.0f);
        WallContactUpdate(player, wall_N7, 1.0f);
        WallContactUpdate(player, wall_P7, 1.0f);
        WallContactUpdate(player, wall_C8, 1.0f);
        WallContactUpdate(player, wall_H8, 1.0f);
        WallContactUpdate(player, wall_J8, 1.0f);
        WallContactUpdate(player, wall_R8, 1.0f);
        WallContactUpdate(player, wall_E9, 1.0f);
        WallContactUpdate(player, wall_L9, 1.0f);
        WallContactUpdate(player, wall_O9, 1.0f);
        WallContactUpdate(player, wall_G10, 1.0f);
        WallContactUpdate(player, wall_J10, 1.0f);
        WallContactUpdate(player, wall_P10, 1.0f);
        WallContactUpdate(player, wall_D11, 1.0f);
        WallContactUpdate(player, wall_M11, 1.0f);
        WallContactUpdate(player, wall_G12, 1.0f);
        WallContactUpdate(player, wall_J12, 1.0f);
        WallContactUpdate(player, wall_N12, 1.0f);
        WallContactUpdate(player, wall_F13, 1.0f);
        //== [ walls section 2 ] ==
        WallContactUpdate(player, wall_R1, 1.0f);
        WallContactUpdate(player, wall_U1, 1.0f);
        WallContactUpdate(player, wall_W1, 1.0f);
        WallContactUpdate(player, wall_X2, 1.0f);
        WallContactUpdate(player, wall_S3, 1.0f);
        WallContactUpdate(player, wall_U4, 1.0f);
        WallContactUpdate(player, wall_X4, 1.0f);
        WallContactUpdate(player, wall_Y5, 1.0f);
        WallContactUpdate(player, wall_U6, 1.0f);
        WallContactUpdate(player, wall_T7, 1.0f);
        WallContactUpdate(player, wall_X7, 1.0f);
        WallContactUpdate(player, wall_Y8, 1.0f);
        WallContactUpdate(player, wall_V9, 1.0f);
        WallContactUpdate(player, wall_A10, 1.0f);
        WallContactUpdate(player, wall_S10, 1.0f);
        WallContactUpdate(player, wall_W10, 1.0f);
        WallContactUpdate(player, wall_Z10, 1.0f);
        WallContactUpdate(player, wall_B11, 1.0f);
        WallContactUpdate(player, wall_P11, 1.0f);
        WallContactUpdate(player, wall_V11, 1.0f);
        WallContactUpdate(player, wall_C12, 1.0f);
        WallContactUpdate(player, wall_T12, 1.0f);
        WallContactUpdate(player, wall_X12, 1.0f);
        WallContactUpdate(player, wall_Z12, 1.0f);
        WallContactUpdate(player, wall_B13, 1.0f);
        WallContactUpdate(player, wall_L13, 1.0f);
        WallContactUpdate(player, wall_Q13, 1.0f);
        WallContactUpdate(player, wall_U13, 1.0f);
        WallContactUpdate(player, wall_E14, 1.0f);
        WallContactUpdate(player, wall_H14, 1.0f);
        WallContactUpdate(player, wall_K14, 1.0f);
        WallContactUpdate(player, wall_N14, 1.0f);
        WallContactUpdate(player, wall_R14, 1.0f);
        WallContactUpdate(player, wall_V14, 1.0f);
        WallContactUpdate(player, wall_B15, 1.0f);
        WallContactUpdate(player, wall_D15, 1.0f);
        WallContactUpdate(player, wall_Q15, 1.0f);
        WallContactUpdate(player, wall_T15, 1.0f);
        WallContactUpdate(player, wall_E16, 1.0f);
        WallContactUpdate(player, wall_H16, 1.0f);
        WallContactUpdate(player, wall_K16, 1.0f);
        WallContactUpdate(player, wall_M16, 1.0f);
        WallContactUpdate(player, wall_I17, 1.0f);

    }

    // update enemy information if any exist
    if (!(minotaurs->Empty())) {
        // updates the minotaur's information
        minotaurs->Update(deltaTime);

        // makes wall the immovable object to minotaur

        //minotaurs->UpdateWallCollisions(wall_one, 1.0f);
        //minotaurs->UpdateWallCollisions(wall_two, 1.0f);

        minotaurs->UpdateWallCollisions(wall_I1, 1.0f);
        minotaurs->UpdateWallCollisions(wall_B2, 1.0f);
        minotaurs->UpdateWallCollisions(wall_D2, 1.0f);
        minotaurs->UpdateWallCollisions(wall_F2, 1.0f);
        minotaurs->UpdateWallCollisions(wall_K2, 1.0f);
        minotaurs->UpdateWallCollisions(wall_N2, 1.0f);
        minotaurs->UpdateWallCollisions(wall_Q2, 1.0f);
        minotaurs->UpdateWallCollisions(wall_E3, 1.0f);
        minotaurs->UpdateWallCollisions(wall_H3, 1.0f);
        minotaurs->UpdateWallCollisions(wall_O3, 1.0f);
        minotaurs->UpdateWallCollisions(wall_D4, 1.0f);
        minotaurs->UpdateWallCollisions(wall_K4, 1.0f);
        minotaurs->UpdateWallCollisions(wall_R4, 1.0f);
        minotaurs->UpdateWallCollisions(wall_A5, 1.0f);
        minotaurs->UpdateWallCollisions(wall_G5, 1.0f);
        minotaurs->UpdateWallCollisions(wall_J5, 1.0f);
        minotaurs->UpdateWallCollisions(wall_N5, 1.0f);
        minotaurs->UpdateWallCollisions(wall_P5, 1.0f);
        minotaurs->UpdateWallCollisions(wall_D6, 1.0f);
        minotaurs->UpdateWallCollisions(wall_K6, 1.0f);
        minotaurs->UpdateWallCollisions(wall_S6, 1.0f);
        minotaurs->UpdateWallCollisions(wall_E7, 1.0f);
        minotaurs->UpdateWallCollisions(wall_G7, 1.0f);
        minotaurs->UpdateWallCollisions(wall_N7, 1.0f);
        minotaurs->UpdateWallCollisions(wall_P7, 1.0f);
        minotaurs->UpdateWallCollisions(wall_C8, 1.0f);
        minotaurs->UpdateWallCollisions(wall_H8, 1.0f);
        minotaurs->UpdateWallCollisions(wall_J8, 1.0f);
        minotaurs->UpdateWallCollisions(wall_R8, 1.0f);
        minotaurs->UpdateWallCollisions(wall_E9, 1.0f);
        minotaurs->UpdateWallCollisions(wall_L9, 1.0f);
        minotaurs->UpdateWallCollisions(wall_O9, 1.0f);
        minotaurs->UpdateWallCollisions(wall_G10, 1.0f);
        minotaurs->UpdateWallCollisions(wall_J10, 1.0f);
        minotaurs->UpdateWallCollisions(wall_P10, 1.0f);
        minotaurs->UpdateWallCollisions(wall_D11, 1.0f);
        minotaurs->UpdateWallCollisions(wall_M11, 1.0f);
        minotaurs->UpdateWallCollisions(wall_G12, 1.0f);
        minotaurs->UpdateWallCollisions(wall_J12, 1.0f);
        minotaurs->UpdateWallCollisions(wall_N12, 1.0f);
        minotaurs->UpdateWallCollisions(wall_F13, 1.0f);
        //== [ walls section 2 ] ==
        minotaurs->UpdateWallCollisions(wall_R1, 1.0f);
        minotaurs->UpdateWallCollisions(wall_U1, 1.0f);
        minotaurs->UpdateWallCollisions(wall_W1, 1.0f);
        minotaurs->UpdateWallCollisions(wall_X2, 1.0f);
        minotaurs->UpdateWallCollisions(wall_S3, 1.0f);
        minotaurs->UpdateWallCollisions(wall_U4, 1.0f);
        minotaurs->UpdateWallCollisions(wall_X4, 1.0f);
        minotaurs->UpdateWallCollisions(wall_Y5, 1.0f);
        minotaurs->UpdateWallCollisions(wall_U6, 1.0f);
        minotaurs->UpdateWallCollisions(wall_T7, 1.0f);
        minotaurs->UpdateWallCollisions(wall_X7, 1.0f);
        minotaurs->UpdateWallCollisions(wall_Y8, 1.0f);
        minotaurs->UpdateWallCollisions(wall_V9, 1.0f);
        minotaurs->UpdateWallCollisions(wall_A10, 1.0f);
        minotaurs->UpdateWallCollisions(wall_S10, 1.0f);
        minotaurs->UpdateWallCollisions(wall_W10, 1.0f);
        minotaurs->UpdateWallCollisions(wall_Z10, 1.0f);
        minotaurs->UpdateWallCollisions(wall_B11, 1.0f);
        minotaurs->UpdateWallCollisions(wall_P11, 1.0f);
        minotaurs->UpdateWallCollisions(wall_V11, 1.0f);
        minotaurs->UpdateWallCollisions(wall_C12, 1.0f);
        minotaurs->UpdateWallCollisions(wall_T12, 1.0f);
        minotaurs->UpdateWallCollisions(wall_X12, 1.0f);
        minotaurs->UpdateWallCollisions(wall_Z12, 1.0f);
        minotaurs->UpdateWallCollisions(wall_B13, 1.0f);
        minotaurs->UpdateWallCollisions(wall_L13, 1.0f);
        minotaurs->UpdateWallCollisions(wall_Q13, 1.0f);
        minotaurs->UpdateWallCollisions(wall_U13, 1.0f);
        minotaurs->UpdateWallCollisions(wall_E14, 1.0f);
        minotaurs->UpdateWallCollisions(wall_H14, 1.0f);
        minotaurs->UpdateWallCollisions(wall_K14, 1.0f);
        minotaurs->UpdateWallCollisions(wall_N14, 1.0f);
        minotaurs->UpdateWallCollisions(wall_R14, 1.0f);
        minotaurs->UpdateWallCollisions(wall_V14, 1.0f);
        minotaurs->UpdateWallCollisions(wall_B15, 1.0f);
        minotaurs->UpdateWallCollisions(wall_D15, 1.0f);
        minotaurs->UpdateWallCollisions(wall_Q15, 1.0f);
        minotaurs->UpdateWallCollisions(wall_T15, 1.0f);
        minotaurs->UpdateWallCollisions(wall_E16, 1.0f);
        minotaurs->UpdateWallCollisions(wall_H16, 1.0f);
        minotaurs->UpdateWallCollisions(wall_K16, 1.0f);
        minotaurs->UpdateWallCollisions(wall_M16, 1.0f);
        minotaurs->UpdateWallCollisions(wall_I17, 1.0f);

    }

    // make sure player and minotaur exists before you utilize them
    if (!(minotaurs->Empty()) && exists(player)) {
        minotaurs->UpdateHealthBarContact(*player);

        // if the player and the enemy's field of vision collide, enemy chases player
        minotaurs->UpdateEnemyChase(*player, deltaTime);

        // if the player and an enemy collide, update attack and kill information (in enemy spawner)
        minotaurs->UpdateEnemyContact(*player);

        // delete player condition
        if (minotaurs->getKillStatus()) {
            player = nullptr;
            delete player;
            std::cout << "\nPlayer deleted" << std::endl;
        }
    }
}

void Game_Engine::Render() {
    // clears window
    window->clear(Color(150, 150, 150));

    window->setView(player_view);
    
    if (exists(player))
        player->Draw(*window);

    if (!(minotaurs->Empty()))
        minotaurs->Spawn(*window);

    // temporary wall stuff
    //wall_one->Draw(*window);
    //wall_two->Draw(*window);
    wall_I1->Draw(*window);
    wall_B2->Draw(*window);
    wall_D2->Draw(*window);
    wall_F2->Draw(*window);
    wall_K2->Draw(*window);
    wall_N2->Draw(*window);
    wall_Q2->Draw(*window);
    wall_E3->Draw(*window);
    wall_H3->Draw(*window);
    wall_O3->Draw(*window);
    wall_D4->Draw(*window);
    wall_K4->Draw(*window);
    wall_R4->Draw(*window);
    wall_A5->Draw(*window);
    wall_G5->Draw(*window);
    wall_J5->Draw(*window);
    wall_N5->Draw(*window);
    wall_P5->Draw(*window);
    wall_D6->Draw(*window);
    wall_K6->Draw(*window);
    wall_S6->Draw(*window);
    wall_E7->Draw(*window);
    wall_G7->Draw(*window);
    wall_N7->Draw(*window);
    wall_P7->Draw(*window);
    wall_C8->Draw(*window);
    wall_H8->Draw(*window);
    wall_J8->Draw(*window);
    wall_R8->Draw(*window);
    wall_E9->Draw(*window);
    wall_L9->Draw(*window);
    wall_O9->Draw(*window);
    wall_G10->Draw(*window);
    wall_J10->Draw(*window);
    wall_P10->Draw(*window);
    wall_D11->Draw(*window);
    wall_M11->Draw(*window);
    wall_G12->Draw(*window);
    wall_J12->Draw(*window);
    wall_N12->Draw(*window);
    wall_F13->Draw(*window);

    wall_R1->Draw(*window);
    wall_U1->Draw(*window);
    wall_W1->Draw(*window);
    wall_X2->Draw(*window);
    wall_S3->Draw(*window);
    wall_U4->Draw(*window);
    wall_X4->Draw(*window);
    wall_Y5->Draw(*window);
    wall_U6->Draw(*window);
    wall_T7->Draw(*window);
    wall_X7->Draw(*window);
    wall_Y8->Draw(*window);
    wall_V9->Draw(*window);
    wall_A10->Draw(*window);
    wall_S10->Draw(*window);
    wall_W10->Draw(*window);
    wall_Z10->Draw(*window);
    wall_B11->Draw(*window);
    wall_P11->Draw(*window);
    wall_V11->Draw(*window);
    wall_C12->Draw(*window);
    wall_T12->Draw(*window);
    wall_X12->Draw(*window);
    wall_Z12->Draw(*window);
    wall_B13->Draw(*window);
    wall_L13->Draw(*window);
    wall_Q13->Draw(*window);
    wall_U13->Draw(*window);
    wall_E14->Draw(*window);
    wall_H14->Draw(*window);
    wall_K14->Draw(*window);
    wall_N14->Draw(*window);
    wall_R14->Draw(*window);
    wall_V14->Draw(*window);
    wall_B15->Draw(*window);
    wall_D15->Draw(*window);
    wall_Q15->Draw(*window);
    wall_T15->Draw(*window);
    wall_E16->Draw(*window);
    wall_H16->Draw(*window);
    wall_K16->Draw(*window);
    wall_M16->Draw(*window);
    wall_I17->Draw(*window);

    window->display();
}



/* Initializer functions in order:
 * initVariables(): initilizes all variables, calls initPlayer(), initEnemies(), and initWalls()
 * initPlayer():    initializes main player, sets it to sprite sheet, reports player base health and attack value
 * initEnemies():   initializes enemy objects, sets their position, reports enemy base health and attack value
 * initWalls():     initializes wall objects (2), loads texture for them
 * initWindow():    initializes game window, sets view to be center with player
 */
void Game_Engine::initVariables() {
    // clearing any previous memory, not necessary, but safe
    this->window = nullptr;

    // initializing deltaTime 
    deltaTime = 0.0f;

    std::cout << "[1] Initialized Variables" << std::endl;

    // calls all initializers
    initPlayer();
    initEnemies();
    initWalls();
}

void Game_Engine::initPlayer() {
    this->player = nullptr;

    // loading sprite sheet
    base_movement.loadFromFile("imgs/running_updated.png");

    /* Initializing player
     * &base_movement:      reference to texture
     * Vector2u(12, 4):     sprite sheet is 12x4 images
     * 0.05f:               how fast the animations switch between images
     * 300.0f:              player speed in the relation to objects in the window
     * 200:                 player total health (initial)
     */
    player = new Player(&base_movement, Vector2u(12, 4), 0.05f, 300.0f, 200);

    std::cout << "[2] Initialized Player" << std::endl;

    // reports player statistics
    std::cout << "\t**Player Total Health: " << player->getTotalHealth() << "**" << std::endl;
    std::cout << "\t**Player Attack Value: " << player->getAttackValue() << "**" << std::endl;
}

void Game_Engine::initEnemies() {
    this->minotaurs = nullptr;

    // for random positions
    srand((unsigned) time(0));

    // loading sprite sheet
    min_texture.loadFromFile("imgs/minotaur.png");

    /* Initializing enemy
     * enemy_amount:    how many enemies to spawn
     * 20:              enemy attack value
     * &min_texture:    reference to texture
     * Vector2u(10, 5): sprite sheet is 10x5 images
     * 0.35f:           how fast the animations switch between images
     * 37.0f:          player speed in the relation to objects in the window
     * 300              enemy health
     */
    minotaurs = new Enemy_Spawner(minotaur_amount, 20, &min_texture, Vector2u(10, 5), 0.35f, 37.0f, 150);
}

void Game_Engine::initWalls() {
    // temporary wall stuff
    //this->wall_one = nullptr;
    //this->wall_two = nullptr;
    this->wall_I1 = nullptr;
    this->wall_B2 = nullptr;
    this->wall_D2 = nullptr;
    this->wall_F2 = nullptr;
    this->wall_K2 = nullptr;
    this->wall_N2 = nullptr;
    this->wall_Q2 = nullptr;
    this->wall_E3 = nullptr;
    this->wall_H3 = nullptr;
    this->wall_O3 = nullptr;
    this->wall_D4 = nullptr;
    this->wall_K4 = nullptr;
    this->wall_R4 = nullptr;
    this->wall_A5 = nullptr;
    this->wall_G5 = nullptr;
    this->wall_J5 = nullptr;
    this->wall_N5 = nullptr;
    this->wall_P5 = nullptr;
    this->wall_D6 = nullptr;
    this->wall_K6 = nullptr;
    this->wall_S6 = nullptr;
    this->wall_E7 = nullptr;
    this->wall_G7 = nullptr;
    this->wall_N7 = nullptr;
    this->wall_P7 = nullptr;
    this->wall_C8 = nullptr;
    this->wall_H8 = nullptr;
    this->wall_J8 = nullptr;
    this->wall_R8 = nullptr;
    this->wall_E9 = nullptr;
    this->wall_L9 = nullptr;
    this->wall_O9 = nullptr;
    this->wall_G10 = nullptr;
    this->wall_J10 = nullptr;
    this->wall_P10 = nullptr;
    this->wall_D11 = nullptr;
    this->wall_M11 = nullptr;
    this->wall_G12 = nullptr;
    this->wall_J12 = nullptr;
    this->wall_N12 = nullptr;
    this->wall_F13 = nullptr;

    this->wall_R1 = nullptr;
    this->wall_U1 = nullptr;
    this->wall_W1 = nullptr;
    this->wall_X2 = nullptr;
    this->wall_S3 = nullptr;
    this->wall_U4 = nullptr;
    this->wall_X4 = nullptr;
    this->wall_Y5 = nullptr;
    this->wall_U6 = nullptr;
    this->wall_T7 = nullptr;
    this->wall_X7 = nullptr;
    this->wall_Y8 = nullptr;
    this->wall_V9 = nullptr;
    this->wall_A10 = nullptr;
    this->wall_S10 = nullptr;
    this->wall_W10 = nullptr;
    this->wall_Z10 = nullptr;
    this->wall_B11 = nullptr;
    this->wall_P11 = nullptr;
    this->wall_V11 = nullptr;
    this->wall_C12 = nullptr;
    this->wall_T12 = nullptr;
    this->wall_X12 = nullptr;
    this->wall_Z12 = nullptr;
    this->wall_B13 = nullptr;
    this->wall_L13 = nullptr;
    this->wall_Q13 = nullptr;
    this->wall_U13 = nullptr;
    this->wall_E14 = nullptr;
    this->wall_H14 = nullptr;
    this->wall_K14 = nullptr;
    this->wall_N14 = nullptr;
    this->wall_R14 = nullptr;
    this->wall_V14 = nullptr;
    this->wall_B15 = nullptr;
    this->wall_D15 = nullptr;
    this->wall_Q15 = nullptr;
    this->wall_T15 = nullptr;
    this->wall_E16 = nullptr;
    this->wall_H16 = nullptr;
    this->wall_K16 = nullptr;
    this->wall_M16 = nullptr;
    this->wall_I17 = nullptr;


    /* Initializing walls
     * &brickwall:              reference to texture
     * Vector2f(float, float):  size of object
     * Vector2f(float, float):  position in the window
     */

    float scale = 250.0f;

    brickwall.loadFromFile("imgs/wall.png");
    //wall_one = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(500.0f, 200.0f));
    //wall_two = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(500.0f, 800.0f));
    wall_I1 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(1.0f*scale, 9.0f*scale));
    wall_B2 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(2.0f*scale, 2.0f*scale));
    wall_D2 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(2.0f*scale, 4.0f*scale));
    wall_F2 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(2.0f*scale, 6.0f*scale));
    wall_K2 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(2.0f*scale, 11.0f*scale));
    wall_N2 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(2.0f*scale, 14.0f*scale));
    wall_Q2 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(2.0f*scale, 17.0f*scale));
    wall_E3 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(3.0f*scale, 5.0f*scale));
    wall_H3 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(3.0f*scale, 8.0f*scale));
    wall_O3 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(3.0f*scale, 15.0f*scale));
    wall_D4 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(4.0f*scale, 4.0f*scale));
    wall_K4 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(4.0f*scale, 11.0f*scale));
    wall_R4 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(4.0f*scale, 16.0f*scale));
    wall_A5 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(5.0f*scale, 1.0f*scale));
    wall_G5 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(5.0f*scale, 7.0f*scale));
    wall_J5 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(5.0f*scale, 12.0f*scale));
    wall_N5 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(5.0f*scale, 14.0f*scale));
    wall_P5 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(5.0f*scale, 16.0f*scale));
    wall_D6 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(6.0f*scale, 4.0f*scale));
    wall_K6 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(6.0f*scale, 11.0f*scale));
    wall_S6 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(6.0f*scale, 19.0f*scale));
    wall_E7 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(7.0f*scale, 5.0f*scale));
    wall_G7 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(7.0f*scale, 7.0f*scale));
    wall_N7 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(7.0f*scale, 14.0f*scale));
    wall_P7 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(7.0f*scale, 16.0f*scale));
    wall_C8 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(8.0f*scale, 3.0f*scale));
    wall_H8 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(8.0f*scale, 8.0f*scale));
    wall_J8 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(8.0f*scale, 10.0f*scale));
    wall_R8 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(8.0f*scale, 18.0f*scale));
    wall_E9 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(9.0f*scale, 5.0f*scale));
    wall_L9 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(9.0f*scale, 12.0f*scale));
    wall_O9 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(9.0f*scale, 15.0f*scale));
    wall_G10 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(10.0f*scale, 7.0f*scale));
    wall_J10 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(10.0f*scale, 10.0f*scale));
    wall_P10 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(10.0f*scale, 16.0f*scale));
    wall_D11 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(11.0f*scale, 4.0f*scale));
    wall_M11 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(11.0f*scale, 13.0f*scale));
    wall_G12 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(12.0f*scale, 7.0f*scale));
    wall_J12 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(12.0f*scale, 10.0f*scale));
    wall_N12 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(12.0f*scale, 14.0f*scale));
    wall_F13 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(13.0f*scale, 6.0f*scale));

    wall_R1 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(1.0f*scale, 18.0f*scale));
    wall_U1 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(1.0f*scale, 21.0f*scale));
    wall_W1 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(1.0f*scale, 23.0f*scale));
    wall_X2 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(2.0f*scale, 24.0f*scale));
    wall_S3 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(2.0f*scale, 19.0f*scale));
    wall_U4 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(4.0f*scale, 21.0f*scale));
    wall_X4 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(4.0f*scale, 24.0f*scale));
    wall_Y5 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(5.0f*scale, 25.0f*scale));
    wall_U6 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(6.0f*scale, 21.0f*scale));
    wall_T7 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(7.0f*scale, 20.0f*scale));
    wall_X7 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(7.0f*scale, 24.0f*scale));
    wall_Y8 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(8.0f*scale, 25.0f*scale));
    wall_V9 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(9.0f*scale, 22.0f*scale));
    wall_A10 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(10.0f*scale, 1.0f*scale));
    wall_S10 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(10.0f*scale, 19.0f*scale));
    wall_W10 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(10.0f*scale, 23.0f*scale));
    wall_Z10 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(10.0f*scale, 26.0f*scale));
    wall_B11 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(11.0f*scale, 2.0f*scale));
    wall_P11 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(11.0f*scale, 16.0f*scale));
    wall_V11 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(11.0f*scale, 22.0f*scale));
    wall_C12 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(12.0f*scale, 3.0f*scale));
    wall_T12 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(12.0f*scale, 20.0f*scale));
    wall_X12 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(12.0f*scale, 24.0f*scale));
    wall_Z12 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(12.0f*scale, 26.0f*scale));
    wall_B13 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(13.0f*scale, 2.0f*scale));
    wall_L13 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(13.0f*scale, 12.0f*scale));
    wall_Q13 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(13.0f*scale, 17.0f*scale));
    wall_U13 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(13.0f*scale, 21.0f*scale));
    wall_E14 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(14.0f*scale, 5.0f*scale));
    wall_H14 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(14.0f*scale, 8.0f*scale));
    wall_K14 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(14.0f*scale, 11.0f*scale));
    wall_N14 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(14.0f*scale, 14.0f*scale));
    wall_R14 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(14.0f*scale, 18.0f*scale));
    wall_V14 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(14.0f*scale, 22.0f*scale));
    wall_B15 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(15.0f*scale, 2.0f*scale));
    wall_D15 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(15.0f*scale, 4.0f*scale));
    wall_Q15 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(15.0f*scale, 17.0f*scale));
    wall_T15 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(15.0f*scale, 20.0f*scale));
    wall_E16 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(16.0f*scale, 5.0f*scale));
    wall_H16 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(16.0f*scale, 8.0f*scale));
    wall_K16 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(16.0f*scale, 11.0f*scale));
    wall_M16 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(16.0f*scale, 13.0f*scale));
    wall_I17 = new Wall(&brickwall, Vector2f(2.0f*scale, 1.0f*scale), Vector2f(17.0f*scale, 9.0f*scale));


    std::cout << "[4] Initialized Walls" << std::endl;
}

void Game_Engine::initWindow() {
    // setting dimensions of the window
    videoMode.height = 1000.0f;
    videoMode.width = 1000.0f;

    // initializing window (dynamic allocation)
    this->window = new RenderWindow(videoMode, "Game Window", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window->setKeyRepeatEnabled(false);

    // sets player view and centers player in window
    player_view.setCenter(Vector2f(0.0f,0.0f));
    player_view.setSize(Vector2f(videoMode.width, videoMode.height));

    std::cout << "[5] Initialized Window" << std::endl;
}


// ResizeView function, used to keep proportions in event of window resizing
void Game_Engine::ResizeView(const RenderWindow& window, View& view) {
    // calculating aspect ratio
    float aspectRatio = float(window.getSize().x) / float (window.getSize().y);
    view.setSize(videoMode.width * aspectRatio, videoMode.height);
}


/* Game Driver functions in order:
 * pollEvents():            gets called in Update(), constantly checks for events (pressing keys, lifting keys, exiting window)
 * WallContactUpdate():     gets called in Update(), updates the contact settings between Individuals and the walls
 * Update():                main driver of this class, updates all game objects (position, health, settings)
 * Render():                main drawing function of this class, draws all updated objects
 */
void Game_Engine::pollEvents() {
    // polls for window close event
    while(window->pollEvent(ev)) {
        switch (ev.type) {

            // window is closing
            case Event::Closed:
                window->close();
                std::cout << "Window Closed (X)" << std::endl;
                break;

            // window is resized
            case Event::Resized:
                ResizeView(*window, player_view);
                //std::cout << "Window Resized" << std::endl;
                break;

            // keys have been pressed
            case Event::KeyPressed:
                if (this->ev.key.code == Keyboard::Escape) {
                    window->close();
                    std::cout << "Window Closed (Esc)" << std::endl;
                }
                break;

            // default case
            default:
                break;
        }
    }
}

void Game_Engine::WallContactUpdate(Individual* character, Wall* aWall, float push) {
    // a value of 1.0f is an immovable object, wheres 0.0f would move quickly
    aWall->ColliderCheck(character->GetCollider(), push);
}

#endif  // GAME_ENGINE_H