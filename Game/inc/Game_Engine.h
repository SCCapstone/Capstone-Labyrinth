/* Copyright 2020 Samuel Dunny */
/* Game_Engine class (in header file) */

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Player.h"
#include "Enemy_Spawner.h"
#include "Replinish_Spawner.h"
#include "Maze_Builder.h"
#include "Exit_Page.h"

#include <ctime>

using sf::View;
using sf::VideoMode;
using sf::Event;
using sf::Clock;
using sf::Color;

/* Class that acts as game engine
 * Creates window (from SFML)
 * Creates player (Player)
 * Creates enemies (Enemy_Spawner)
 * Creates a maze (Maze_Builder)
 */

// Constant Values

static int MAX_ENEMY_AMT = 1000;
const static bool genMAXEnemies = false;                                // set to true to generate MAX number of enemies (test code)
const static int totalEnemyAmount = 80;

// default cheat mode view, gets set to 10 or 1 in init
static int zoomOutFactor;                                           // factor to see more maze (can be boosted in cheat mode)
int zoomValue = 6;

const static int player_attVal = 10;                                    // factor for player attack value (can be boosted in cheat mode)
const static int player_health = 200;                                   // how much health the player originally starts with (can be boosted in cheat mode)
const static float player_speed = 300.0f;                               // factor for player speed
const static Vector2f player_size = Vector2f(100.0f, 150.0f);

// quadrant spawn limits (x, y)
const static Vector2f SAM_SpawnLimit = Vector2f(15.0f, -19.0f);
const static Vector2f Q4_SpawnLimit = Vector2f(-28.0f, -17.0f);
const static Vector2f Q3_SpawnLimit = Vector2f(-28.0f, 26.0f);
const static Vector2f Q2_SpawnLimit = Vector2f(15.0f, 26.0f);

const static Vector2f SAM_enemySpawnOrigin = Vector2f(0.0f, 0.0f);
/*
const static Vector2f q2_enemySpawnOrigin = Vector2f(-1.0f, 1.0f);
const static Vector2f q3_enemySpawnOrigin = Vector2f(-1.0f, 1.0f);
const static Vector2f q4_enemySpawnOrigin = Vector2f(-1.0f, 1.0f);
*/

// will use these as values for other enemy types, TODO add different attrributes for other enemies
const static int SAM_QuadrantHeartAmt = 10;
const static Vector2f SAM_enemySize = player_size;
const static float SAM_minotaur_speed = 27.0f;                          // how fast minotaurs are
const static int SAM_minotaur_health = 150;                             // how much health the minotaurs originally start with
const static int SAM_minotaur_attVal = 19;                              // how much damage minotaurs can do (made it an odd number for better percentages when calculating health)

static int SAM_minotaur_amount = (int)totalEnemyAmount/4;               // how many minotaurs to spawn
static int q2_enemy_amount = (int)totalEnemyAmount / 4;                 // how many minotaurs to spawn
static int q3_enemy_amount = (int)totalEnemyAmount / 4;                 // how many minotaurs to spawn
static int q4_enemy_amount = (int)totalEnemyAmount / 4;                 // how many minotaurs to spawn


// variables for testing
const bool test_win_msg = false;
const bool test_loss_msg = false;

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

    // variables for enemy characters
    Enemy_Spawner* minotaurs;
    Enemy_Spawner* enemies_q2;
    Enemy_Spawner* enemies_q3;
    Enemy_Spawner* enemies_q4;

    // boss enemies
    Enemy* Minos;
    Enemy* boss_q2;
    Enemy* boss_q3;
    Enemy* boss_q4;

    // variables to manage boss deletion
    bool SAM_Boss_dead = false;
    bool q2_Boss_dead = false;
    bool q3_Boss_dead = false;
    bool q4_Boss_dead = false;

    Texture min_texture;

    // maze variable
    Maze_Builder* maze;

    Replinish_Spawner* replinishers;
    Replinish_Spawner* replinishers_q2;
    Replinish_Spawner* replinishers_q3;
    Replinish_Spawner* replinishers_q4;
    Texture hr_text;

    // using these so animation runs at same rate irrespective of machine
    float deltaTime;
    Clock clock;

    // stores cheat mode setting
    bool inCheatMode;

    // stores player status
    bool playerDead;

    Exit_Page* exitpage;
    Vector2f playerCoords_copy; // stores copy of players position when they die for message display purposes

    // initializer functions
    void initVariables();
    void initPlayer();
    void initReplinishers();
    void initEnemies();
    void initWalls();
    void initWindow();

    // function to keep ratio accurate in event of window resizing
    void ResizeView(const RenderWindow& window, View& view);

    // function responsible for catching and dealing with all Events
    void pollEvents();

    // function to test if Individuals exist (player, enemy, etc.)
    bool exists(Individual* other) {
      if (other != nullptr)
         return true;
      return false;
    }

    void noEnemySpawnInWall(Enemy_Spawner* enms, Maze_Builder* mz, Vector2f origin, Vector2f limit, int amount);
    void noHeartSpawnInWall(Replinish_Spawner* hrts, Maze_Builder* mz, Vector2f origin, Vector2f limit, int amount);

// public attributes 
public:
    
    Game_Engine(bool inCheatMode);      // constructor
    ~Game_Engine();                     // destructor
    void Update();                      // updates all game objects, states (contact, attack, moving)
    void Render();                      // renders all objects and states in window

    // accessor, returns true if window is still open
    const bool running() const { return window->isOpen(); }
    const bool isPlayerDead() const { return playerDead; }
    bool isGameCheating() { return inCheatMode;  }
};

/* Public Functions in order:
 * Game_Engine():   default constructor, calls all initializer functions
 * ~Game_Engine():  destructor, deletes dynamic objects
 * Update():        updates all game logic (interactions between players, enemies, the environment, and movement in the window)
 * Render():        draws and displays all game objects (player, enemies, walls)
 */
Game_Engine::Game_Engine(bool inCheatMode) {
    std::cout << "-----STARTING INITIALIZATION-----" << std::endl;

    this->inCheatMode = inCheatMode;
    this->playerDead = false;

    // determine window scope based on cheat mode condition
    if (this->inCheatMode)
        zoomOutFactor = zoomValue;
    else
        zoomOutFactor = 1;

    // initializes
    initVariables();
    initWindow();

    std::cout << "-----INITIALIZATION FINISHED-----\n" << std::endl;
}

Game_Engine::~Game_Engine() {
    // Window destructor
    delete this->window;

    // Player destructor
    delete this->player;

    // Boss destructor
    delete this->Minos;
    delete this->boss_q2;
    delete this->boss_q3;
    delete this->boss_q4;

    // Wall_Builder destructor
    delete this->maze;

    // Exit page destructor
    delete this->exitpage;

    // dont need destructor for enemies
    // don't need a destructor for hearts
}

void Game_Engine::Update() {
    // used in the update function
    deltaTime = clock.restart().asSeconds();

    // poll events
    pollEvents();

    // update replinishers
    if (!(replinishers->Empty())) {
        replinishers->Update(deltaTime);
    }
    if (!(replinishers_q2->Empty())) {
        replinishers_q2->Update(deltaTime);
    }
    if (!(replinishers_q3->Empty())) {
        replinishers_q3->Update(deltaTime);
    }
    if (!(replinishers_q4->Empty())) {
        replinishers_q4->Update(deltaTime);
    }

    // update player information if it exists
    if (exists(player)) {
        // .Update() responds to keyboard input and updates the player in the respective direction
        player->Update(deltaTime);

        // must call this after player.Update(), otherwise cammera stutters
        player_view.setCenter(this->player->getIndividualPos());

        // makes maze the immovable object to player
        maze->MazeContactUpdate_Player(player, 1.0f);

        // replinish player health
        if (!(replinishers->Empty())) {
            replinishers->UpdatePlayerContact(*player);
        }
        if (!(replinishers_q2->Empty())) {
            replinishers_q2->UpdatePlayerContact(*player);
        }
        if (!(replinishers_q3->Empty())) {
            replinishers_q3->UpdatePlayerContact(*player);
        }
        if (!(replinishers_q4->Empty())) {
            replinishers_q4->UpdatePlayerContact(*player);
        }
    }

    if (exists(Minos)) {
        srand((unsigned)time(0));
        int rv = rand() % 5 + 1;
        Minos->Update(deltaTime, rv);

        // makes maze the immovable object to player
        maze->MazeContactUpdate_Boss(Minos, 1.0f);
    }
    if (exists(boss_q2)) {
        srand((unsigned)time(0));
        int rv = rand() % 5 + 1;
        boss_q2->Update(deltaTime, rv);

        // makes maze the immovable object to player
        maze->MazeContactUpdate_Boss(boss_q2, 1.0f);
    }
    if (exists(boss_q3)) {
        srand((unsigned)time(0));
        int rv = rand() % 5 + 1;
        boss_q3->Update(deltaTime, rv);

        // makes maze the immovable object to player
        maze->MazeContactUpdate_Boss(boss_q3, 1.0f);
    }
    if (exists(boss_q4)) {
        srand((unsigned)time(0));
        int rv = rand() % 5 + 1;
        boss_q4->Update(deltaTime, rv);

        // makes maze the immovable object to player
        maze->MazeContactUpdate_Boss(boss_q4, 1.0f);
    }

    // update enemy information if any exist
    if (!(minotaurs->Empty())) {
        // updates the minotaur's information
        minotaurs->Update(deltaTime);

        // makes maze the immovable object to minotaur
        maze->MazeContactUpdate_Enemies(minotaurs, 1.0f);
    }
    if (!(enemies_q2->Empty())) {
        // updates the minotaur's information
        enemies_q2->Update(deltaTime);

        // makes maze the immovable object to minotaur
        maze->MazeContactUpdate_Enemies(enemies_q2, 1.0f);
    }
    if (!(enemies_q3->Empty())) {
        // updates the minotaur's information
        enemies_q3->Update(deltaTime);

        // makes maze the immovable object to minotaur
        maze->MazeContactUpdate_Enemies(enemies_q3, 1.0f);
    }
    if (!(enemies_q4->Empty())) {
        // updates the minotaur's information
        enemies_q4->Update(deltaTime);

        // makes maze the immovable object to minotaur
        maze->MazeContactUpdate_Enemies(enemies_q4, 1.0f);
    }

    // make sure player and minotaur exists before you utilize them
    if (!(minotaurs->Empty()) && exists(player)) {
        minotaurs->UpdateHealthBarContact(*player);

        // if the player and the enemy's field of vision collide, enemy chases player
        minotaurs->UpdateEnemyChase(*player, deltaTime);

        // if the player and an enemy collide, update attack and kill information (in enemy spawner)
        minotaurs->UpdateEnemyContact(*player, inCheatMode);

        playerCoords_copy = player->getIndividualPos();

        // delete player condition
        if (minotaurs->getKillStatus()) {
            player = nullptr;
            delete player;
            std::cout << "\nPlayer deleted" << std::endl;
            playerDead = true;
            exitpage->setLost(playerDead);
        }
    }
    if (!(enemies_q2->Empty()) && exists(player)) {
        enemies_q2->UpdateHealthBarContact(*player);

        // if the player and the enemy's field of vision collide, enemy chases player
        enemies_q2->UpdateEnemyChase(*player, deltaTime);

        // if the player and an enemy collide, update attack and kill information (in enemy spawner)
        enemies_q2->UpdateEnemyContact(*player, inCheatMode);

        playerCoords_copy = player->getIndividualPos();

        // delete player condition
        if (enemies_q2->getKillStatus()) {
            player = nullptr;
            delete player;
            std::cout << "\nPlayer deleted" << std::endl;
            playerDead = true;
            exitpage->setLost(playerDead);
        }
    }
    if (!(enemies_q3->Empty()) && exists(player)) {
        enemies_q3->UpdateHealthBarContact(*player);

        // if the player and the enemy's field of vision collide, enemy chases player
        enemies_q3->UpdateEnemyChase(*player, deltaTime);

        // if the player and an enemy collide, update attack and kill information (in enemy spawner)
        enemies_q3->UpdateEnemyContact(*player, inCheatMode);

        playerCoords_copy = player->getIndividualPos();

        // delete player condition
        if (enemies_q3->getKillStatus()) {
            player = nullptr;
            delete player;
            std::cout << "\nPlayer deleted" << std::endl;
            playerDead = true;
            exitpage->setLost(playerDead);
        }
    }
    if (!(enemies_q4->Empty()) && exists(player)) {
        enemies_q4->UpdateHealthBarContact(*player);

        // if the player and the enemy's field of vision collide, enemy chases player
        enemies_q4->UpdateEnemyChase(*player, deltaTime);

        // if the player and an enemy collide, update attack and kill information (in enemy spawner)
        enemies_q4->UpdateEnemyContact(*player, inCheatMode);

        playerCoords_copy = player->getIndividualPos();

        // delete player condition
        if (enemies_q4->getKillStatus()) {
            player = nullptr;
            delete player;
            std::cout << "\nPlayer deleted" << std::endl;
            playerDead = true;
            exitpage->setLost(playerDead);
        }
    }

    if (exists(Minos) && exists(player)) {
        player->HealthBarColliderCheck(Minos->GetCollider(), 0.0f);

        if (player->VisionColliderCheck(Minos->GetCollider(), 0.0f)) {
            Minos->Chase(*player, deltaTime);
        }

        // 0.5f to show that enemies and player have same force on each other
        if (player->ColliderCheck(Minos->GetCollider(), 0.5f)) {

            // player attacking enemy
            if (Minos->getTotalHealth() > player->getAttackValue()) {
                player->Attack(*Minos);
            }
            else {
                SAM_Boss_dead = true;
                std::cout << "\nBOSS deleted: " << std::endl;
            }

            // enemy attacking player
            if (this->inCheatMode == false) {
                if (player->getTotalHealth() > Minos->getAttackValue()) {
                    Minos->ConstantAttack(*player);
                }
                else {
                    playerCoords_copy = player->getIndividualPos();
                    player = nullptr;
                    delete player;
                    std::cout << "\nPlayer deleted" << std::endl;
                    playerDead = true;
                    exitpage->setLost(playerDead);
                }
            }
        }
    }
    if (exists(boss_q2) && exists(player)) {
        player->HealthBarColliderCheck(boss_q2->GetCollider(), 0.0f);

        if (player->VisionColliderCheck(boss_q2->GetCollider(), 0.0f)) {
            boss_q2->Chase(*player, deltaTime);
        }

        // 0.5f to show that enemies and player have same force on each other
        if (player->ColliderCheck(boss_q2->GetCollider(), 0.5f)) {

            // player attacking enemy
            if (boss_q2->getTotalHealth() > player->getAttackValue()) {
                player->Attack(*boss_q2);
            }
            else {
                q2_Boss_dead = true;
                std::cout << "\nBOSS deleted: " << std::endl;
            }

            // enemy attacking player
            if (this->inCheatMode == false) {
                if (player->getTotalHealth() > boss_q2->getAttackValue()) {
                    boss_q2->ConstantAttack(*player);
                }
                else {
                    playerCoords_copy = player->getIndividualPos();
                    player = nullptr;
                    delete player;
                    std::cout << "\nPlayer deleted" << std::endl;
                    playerDead = true;
                    exitpage->setLost(playerDead);
                }
            }
        }
    }
    if (exists(boss_q3) && exists(player)) {
        player->HealthBarColliderCheck(boss_q3->GetCollider(), 0.0f);

        if (player->VisionColliderCheck(boss_q3->GetCollider(), 0.0f)) {
            boss_q3->Chase(*player, deltaTime);
        }

        // 0.5f to show that enemies and player have same force on each other
        if (player->ColliderCheck(boss_q3->GetCollider(), 0.5f)) {

            // player attacking enemy
            if (boss_q3->getTotalHealth() > player->getAttackValue()) {
                player->Attack(*boss_q3);
            }
            else {
                q3_Boss_dead = true;
                std::cout << "\nBOSS deleted: " << std::endl;
            }

            // enemy attacking player
            if (this->inCheatMode == false) {
                if (player->getTotalHealth() > boss_q3->getAttackValue()) {
                    boss_q3->ConstantAttack(*player);
                }
                else {
                    playerCoords_copy = player->getIndividualPos();
                    player = nullptr;
                    delete player;
                    std::cout << "\nPlayer deleted" << std::endl;
                    playerDead = true;
                    exitpage->setLost(playerDead);
                }
            }
        }
    }
    if (exists(boss_q4) && exists(player)) {
        player->HealthBarColliderCheck(boss_q4->GetCollider(), 0.0f);

        if (player->VisionColliderCheck(boss_q4->GetCollider(), 0.0f)) {
            boss_q4->Chase(*player, deltaTime);
        }

        // 0.5f to show that enemies and player have same force on each other
        if (player->ColliderCheck(boss_q4->GetCollider(), 0.5f)) {

            // player attacking enemy
            if (boss_q4->getTotalHealth() > player->getAttackValue()) {
                player->Attack(*boss_q4);
            }
            else {
                q4_Boss_dead = true;
                std::cout << "\nBOSS deleted: " << std::endl;
            }

            // enemy attacking player
            if (this->inCheatMode == false) {
                if (player->getTotalHealth() > boss_q4->getAttackValue()) {
                    boss_q4->ConstantAttack(*player);
                }
                else {
                    playerCoords_copy = player->getIndividualPos();
                    player = nullptr;
                    delete player;
                    std::cout << "\nPlayer deleted" << std::endl;
                    playerDead = true;
                    exitpage->setLost(playerDead);
                }
            }
        }
    }

    // deletes boss
    if (SAM_Boss_dead) {
        Minos = nullptr;
        delete Minos;
    }
    if (q2_Boss_dead) {
        boss_q2 = nullptr;
        delete boss_q2;
    }
    if (q3_Boss_dead) {
        boss_q3 = nullptr;
        delete boss_q3;
    }
    if (q4_Boss_dead) {
        boss_q4 = nullptr;
        delete boss_q4;
    }

    // game has been won
    if (SAM_Boss_dead && q2_Boss_dead && q3_Boss_dead && q4_Boss_dead) {
        //std::cout << "\nALL BOSSES DEFEATED: " << std::endl;
        exitpage->setLost(false);
    }
}

void Game_Engine::Render() {
    // clears window

    // default background
    window->clear(Color(150, 150, 150));

    // centers window view on player
    window->setView(player_view);
    
    // draws maze and custom background
    maze->Draw(*window);

    // draws health replinishing items (if they exist)
    if (!(replinishers->Empty()))
        replinishers->Spawn(*window);
    if (!(replinishers_q2->Empty()))
        replinishers_q2->Spawn(*window);
    if (!(replinishers_q3->Empty()))
        replinishers_q3->Spawn(*window);
    if (!(replinishers_q4->Empty()))
        replinishers_q4->Spawn(*window);

    // draws player (if it exists)
    if (exists(player))
        player->Draw(*window);

    // draws enemies (if they exist)
    if (!(minotaurs->Empty()))
        minotaurs->Spawn(*window);
    if (!(enemies_q2->Empty()))
        enemies_q2->Spawn(*window);
    if (!(enemies_q3->Empty()))
        enemies_q3->Spawn(*window);
    if (!(enemies_q4->Empty()))
        enemies_q4->Spawn(*window);

    // draws bosses (if they exists)
    if (exists(Minos))
        Minos->Draw(*window);
    if (exists(boss_q2))
        boss_q2->Draw(*window);
    if (exists(boss_q3))
        boss_q3->Draw(*window);
    if (exists(boss_q4))
        boss_q4->Draw(*window);

    // draws win message
    if (!exists(Minos) && !exists(boss_q2) && !exists(boss_q3) && !exists(boss_q4)) {
        exitpage->Render(*window, playerCoords_copy);
    }

    // draws loss message
    if (!exists(player)) {
        exitpage->Render(*window, playerCoords_copy);
    }

    // testing win message
    if (test_win_msg) {
        exitpage->setLost(false);
        exitpage->Render(*window, playerCoords_copy);
    }

    // testing loss message
    if (test_loss_msg) {
        exitpage->setLost(true);
        exitpage->Render(*window, playerCoords_copy);
    }

    // display all drawn objects
    window->display();
}



/* Initializer functions in order:
 * initVariables():     initilizes all variables, calls initPlayer(), initEnemies(), and initWalls()
 * initPlayer():        initializes main player, sets it to sprite sheet, reports player base health and attack value
 * initReplinishers():  initializes health replinish objects, sets their positions randomly
 * initEnemies():       initializes enemy objects, sets their position randomly, reports enemy base health and attack value
 * initWalls():         initializes wall objects (2), loads texture for them
 * initWindow():        initializes game window, sets view to be center with player
 */
void Game_Engine::initVariables() {
    // clearing any previous memory, not necessary, but safe
    this->window = nullptr;

    // initializing deltaTime 
    deltaTime = 0.0f;

    // calls all initializers
    initPlayer();
    initWalls();            // walls needs to be initalized before enemies for random placement to work
    initEnemies();
    initReplinishers();

    std::cout << "[5] Initialized Variables" << std::endl;
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

    // if in cheat mode, double player health and attack value
    if (inCheatMode) {
        // doesn't particularily matter, as player doesn't take damage in cheat mode anyhow
        int player_health_dub = player_health * 2;
        int player_attVal_dub = player_attVal * 2;
        player = new Player(&base_movement, Vector2u(12, 4), player_size, 0.05f, player_speed, player_health_dub, player_attVal_dub);
    }
    else {
        player = new Player(&base_movement, Vector2u(12, 4), player_size, 0.05f, player_speed, player_health, player_attVal);
    }

    std::cout << "[1] Initialized Player" << std::endl;

    // reports player statistics
    std::cout << "\t**Player Total Health: " << player->getTotalHealth() << "**" << std::endl;
    std::cout << "\t**Player Attack Value: " << player->getAttackValue() << "**" << std::endl;
}

void Game_Engine::initReplinishers() {
    this->replinishers = nullptr;
    this->replinishers_q2 = nullptr;
    this->replinishers_q3 = nullptr;
    this->replinishers_q4 = nullptr;

    hr_text.loadFromFile("imgs/spinning_heart.png");

    replinishers = new Replinish_Spawner(SAM_QuadrantHeartAmt, Vector2f(0.2f * scale, 0.3f * scale), &hr_text, Vector2u(4, 1), 0.5f, SAM_enemySpawnOrigin, SAM_SpawnLimit);
    noHeartSpawnInWall(replinishers, maze, SAM_enemySpawnOrigin, SAM_SpawnLimit, SAM_QuadrantHeartAmt);

    replinishers_q2 = new Replinish_Spawner(SAM_QuadrantHeartAmt, Vector2f(0.2f * scale, 0.3f * scale), &hr_text, Vector2u(4, 1), 0.5f, SAM_enemySpawnOrigin, Q2_SpawnLimit);
    noHeartSpawnInWall(replinishers_q2, maze, SAM_enemySpawnOrigin, Q2_SpawnLimit, SAM_QuadrantHeartAmt);

    replinishers_q3 = new Replinish_Spawner(SAM_QuadrantHeartAmt, Vector2f(0.2f * scale, 0.3f * scale), &hr_text, Vector2u(4, 1), 0.5f, SAM_enemySpawnOrigin, Q3_SpawnLimit);
    noHeartSpawnInWall(replinishers_q3, maze, SAM_enemySpawnOrigin, Q3_SpawnLimit, SAM_QuadrantHeartAmt);

    replinishers_q4 = new Replinish_Spawner(SAM_QuadrantHeartAmt, Vector2f(0.2f * scale, 0.3f * scale), &hr_text, Vector2u(4, 1), 0.5f, SAM_enemySpawnOrigin, Q4_SpawnLimit);
    noHeartSpawnInWall(replinishers_q4, maze, SAM_enemySpawnOrigin, Q4_SpawnLimit, SAM_QuadrantHeartAmt);
}

void Game_Engine::initEnemies() {
    this->minotaurs = nullptr;
    this->enemies_q2 = nullptr;
    this->enemies_q3 = nullptr;
    this->enemies_q4 = nullptr;

    this->Minos = nullptr;
    this->boss_q2 = nullptr;
    this->boss_q3 = nullptr;
    this->boss_q4 = nullptr;

    // loading sprite sheet
    min_texture.loadFromFile("imgs/minotaurv8.png");

    // testing condition
    if (genMAXEnemies) {
        SAM_minotaur_amount = MAX_ENEMY_AMT / 4;
        q2_enemy_amount = MAX_ENEMY_AMT / 4;
        q3_enemy_amount = MAX_ENEMY_AMT / 4;
        q4_enemy_amount = MAX_ENEMY_AMT / 4;
    }

    // Initializing enemy spawners
    // spawn bounds must be exclusive (any free, non-wall space in bounds is viable spawn location)
    minotaurs = new Enemy_Spawner(SAM_minotaur_amount, SAM_minotaur_attVal, SAM_enemySize, &min_texture, Vector2u(10, 3), 0.35f, SAM_minotaur_speed, SAM_minotaur_health, SAM_enemySpawnOrigin, SAM_SpawnLimit);
    noEnemySpawnInWall(minotaurs, maze, SAM_enemySpawnOrigin, SAM_SpawnLimit, SAM_minotaur_amount);

    enemies_q2 = new Enemy_Spawner(q2_enemy_amount, SAM_minotaur_attVal, SAM_enemySize, &min_texture, Vector2u(10, 3), 0.35f, SAM_minotaur_speed, SAM_minotaur_health, SAM_enemySpawnOrigin, Q2_SpawnLimit);
    noEnemySpawnInWall(enemies_q2, maze, SAM_enemySpawnOrigin, Q2_SpawnLimit, q2_enemy_amount);
    
    enemies_q3 = new Enemy_Spawner(q3_enemy_amount, SAM_minotaur_attVal, SAM_enemySize, &min_texture, Vector2u(10, 3), 0.35f, SAM_minotaur_speed, SAM_minotaur_health, SAM_enemySpawnOrigin, Q3_SpawnLimit);
    noEnemySpawnInWall(enemies_q3, maze, SAM_enemySpawnOrigin, Q3_SpawnLimit, q3_enemy_amount);

    enemies_q4 = new Enemy_Spawner(q4_enemy_amount, SAM_minotaur_attVal, SAM_enemySize, &min_texture, Vector2u(10, 3), 0.35f, SAM_minotaur_speed, SAM_minotaur_health, SAM_enemySpawnOrigin, Q4_SpawnLimit);
    noEnemySpawnInWall(enemies_q4, maze, SAM_enemySpawnOrigin, Q4_SpawnLimit, q4_enemy_amount);

    // boss enemy for upper right quadrant
    Minos = new Enemy(&min_texture, Vector2u(10, 3), SAM_enemySize,  0.35f, 0.75f * SAM_minotaur_speed, 2 * SAM_minotaur_health, int(1.5 * SAM_minotaur_attVal));
    Minos->setPos(maze->getFirstQuadBossCoords());

    // boss enemy for lower right quadrant
    boss_q2 = new Enemy(&min_texture, Vector2u(10, 3), SAM_enemySize, 0.35f, 0.75f * SAM_minotaur_speed, 2 * SAM_minotaur_health, int(1.5 * SAM_minotaur_attVal));
    boss_q2->setPos(maze->getSecondQuadBossCoords());

    // boss enemy for lower left quadrant
    boss_q3 = new Enemy(&min_texture, Vector2u(10, 3), SAM_enemySize, 0.35f, 0.75f * SAM_minotaur_speed, 2 * SAM_minotaur_health, int(1.5 * SAM_minotaur_attVal));
    boss_q3->setPos(maze->getThirdQuadBossCoords());

    // boss enemy for lower right quadrant
    boss_q4 = new Enemy(&min_texture, Vector2u(10, 3), SAM_enemySize, 0.35f, 0.75f * SAM_minotaur_speed, 2 * SAM_minotaur_health, int(1.5 * SAM_minotaur_attVal));
    boss_q4->setPos(maze->getFourthQuadBossCoords());
}

void Game_Engine::initWalls() {
    // ensure maze isn't already initialized
    this->maze = nullptr;

    // instantiate a maze object with the scale for all walls
    maze = new Maze_Builder(Vector2f(1.0f * scale, 1.0f * scale));
    
    std::cout << "[2] Initialized Maze" << std::endl;
}

void Game_Engine::initWindow() {
    // setting dimensions of the window
    videoMode.height = (unsigned int)1000;
    videoMode.width = (unsigned int)1000;

    this->exitpage = nullptr;

    // initializing window (dynamic allocation)
    this->window = new RenderWindow(videoMode, "Capstone Labyrinth", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window->setKeyRepeatEnabled(false);

    // sets player view and centers player in window
    player_view.setCenter(Vector2f(0.0f,0.0f));

    float factor_x = float(videoMode.width * zoomOutFactor);
    float factor_y = float(videoMode.height * zoomOutFactor);
    player_view.setSize(Vector2f(factor_x, factor_y));

    // default exit page is for a win (arbitrarily pickey x factor for font sizing)
    exitpage = new Exit_Page(factor_x);

    std::cout << "[6] Initialized Window" << std::endl;
}



/* Game Driver functions in order:
 * ResizeView(RenderWindow&, View&):                used to keep proportions in event of window resizing
 * pollEvents():                                    gets called in Update(), constantly checks for events (pressing keys, lifting keys, exiting window)
 * noEnemySpawnInWall(Enemy_Spawn*, Maze_Builder*): ensures enemies don't spawn in walls, randomly spawns them somewhere else until they arent in a wall
 * noHeartSpawnInWall(Enemy_Spawn*, Maze_Builder*): ensures hearts don't spawn in walls, randomly spawns them somewhere else until they arent in a wall
 */
void Game_Engine::ResizeView(const RenderWindow& window, View& view) {
    // calculating aspect ratio
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);

    float newRatio_x = float(videoMode.width * zoomOutFactor * aspectRatio);
    float newRatio_y = float(videoMode.height * zoomOutFactor);
    view.setSize(newRatio_x, newRatio_y);
}

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

void Game_Engine::noEnemySpawnInWall(Enemy_Spawner* ens, Maze_Builder* mz, Vector2f origin, Vector2f limit, int amount) {
    for (int i = 0; i < amount; i++) {
        while (mz->inMazeWalls(ens->getEnemy(i)->getIndividualPos())) {
            ens->getEnemy(i)->setRandPos(origin, limit);
        }
    }
}

void Game_Engine::noHeartSpawnInWall(Replinish_Spawner* hrts, Maze_Builder* mz, Vector2f origin, Vector2f limit, int amount) {
    for (int i = 0; i < amount; i++) {
        while (mz->inMazeWalls(hrts->getHeart(i)->GetHeartPosition())) {
            hrts->getHeart(i)->setRandPos(origin, limit);
        }
    }
}

#endif  // GAME_ENGINE_H