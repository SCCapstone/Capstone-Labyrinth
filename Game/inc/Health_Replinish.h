/* Copyright 2021 Samuel Dunny */
/* Health_Replinish class (in header file) */

#ifndef HEALTH_REPLINISH_H
#define HEALTH_REPLINISH_H


class Health_Replinish {
    // private attributes
private:
    sf::RectangleShape heart;

    // creating instance of animation (to animate heart)
    Animation h_animation;

    // what row of the sprite sheet we are using
    unsigned int row;

    // public attributes
public:
    Health_Replinish(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, Vector2u imageCount, float switchTime);
    ~Health_Replinish();

    void Update(float deltaTime);

    // takes in window reference, draws player
    void Draw(sf::RenderWindow& window);

    // mutator
    void SetPosition(sf::Vector2f pos) { heart.setPosition(pos); }

    // accessor
    sf::Vector2f GetHeartPosition() { return heart.getPosition(); }

    bool Replinish(Player* player);

    void setRandPos(Vector2f initialC, Vector2f finalC);
};

Health_Replinish::Health_Replinish(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, Vector2u imageCount, float switchTime) :
    h_animation(texture, imageCount, switchTime) {
    this->row = 0;
    heart.setSize(size);
    heart.setOrigin(size / 2.0f);
    heart.setTexture(texture);
    heart.setPosition(position);
}

Health_Replinish::~Health_Replinish() { /* empty */ }

void Health_Replinish::Update(float deltaTime) {
    h_animation.Update(this->row, deltaTime, true, false, false);
    heart.setTextureRect(h_animation.uvRect);
}

void Health_Replinish::Draw(sf::RenderWindow& window) {
    window.draw(heart);
}

bool Health_Replinish::Replinish(Player* player) {
    // if the player is in the heart's boundary
    if (heart.getGlobalBounds().contains(player->getIndividualPos())) {

        // only replinish if health isn't full already
        if (player->getTotalHealth() == player->getOrignalHealth())
            return false;

        // reset player health to original health
        player->setTotalHealth(player->getOrignalHealth());
        return true;
    }
    return false;
}

void Health_Replinish::setRandPos(Vector2f initialC, Vector2f finalC) {

    // find range between given coordinates
    float x_max = abs(initialC.x) + abs(finalC.x);
    float y_max = abs(initialC.y) + abs(finalC.y);

    float x_rand = 0.0f;
    float y_rand = 0.0f;

    while (x_rand == 0.0f || y_rand == 0.0f) {
        //srand((unsigned)time(0));
        x_rand = float(rand() % (int)x_max + 1);
        y_rand = float(rand() % (int)y_max + 1);
    }

    //float x_rand = float(rand() % (int)x_max + 1);
    //float y_rand = float(rand() % (int)y_max + 1);

    //std::cout << "\tRAND COORDS: " << x_rand << ", " << y_rand << std::endl;

    float x_coord = 0.0f;
    float y_coord = 0.0f;

    // upper right quadrant
    if (initialC.x < finalC.x && initialC.y > finalC.y) {
        x_coord = scale * (x_rand - abs(initialC.x));
        y_coord = -1.0f * scale * (y_rand - abs(initialC.y));
    }
    // lower right quadrant
    else if (initialC.x < finalC.x && initialC.y < finalC.y) {
        x_coord = scale * (x_rand - abs(initialC.x));
        y_coord = scale * (y_rand - abs(initialC.y));
    }
    // lower left quadrant
    else if (initialC.x > finalC.x && initialC.y < finalC.y) {
        x_coord = -1.0f * scale * (x_rand - abs(initialC.x));
        y_coord = scale * (y_rand - abs(initialC.y));
    }
    // upper left quadrant
    else {
        x_coord = -1.0f * scale * (x_rand - abs(initialC.x));
        y_coord = -1.0f * scale * (y_rand - abs(initialC.y));
    }

    heart.setPosition(x_coord, y_coord);
}


#endif  // HEALTH_REPLINISH_H