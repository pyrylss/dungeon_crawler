#include "player.hpp"

Player::Player() : hp_(100), max_hp_(100), healthpotions_(0), direction_(sf::Vector2f(0.0f, 0.0f)), speed_(15.f) {
        //Player graphics
        progress_ = 0;
        body_.setRadius(50.f);
        body_.setPosition(100.f, 1001.f);
        playerTexture.loadFromFile("src/Sprites/wizard.png");
        body_.setTexture(&playerTexture);

        weapon_ = Weapon();

        //Weapon graphics
        weaponBody_.setRadius(35.f);
        weaponBody_.setPosition(100.f, 1001.f);
        weaponTexture_.loadFromFile("src/Sprites/wand.png");
        weaponBody_.setTexture(&weaponTexture_);


        //body_.setFillColor(sf::Color::Cyan);
        waitTime_ = 0;
        cheatKill = false;
        deadCheck = false;
    }


sf::Vector2f Player::getPosition() {
    return body_.getPosition();
}

int Player::GetHP(){return hp_;}

int Player::GetPotionNum(){return healthpotions_;}

int Player::GetMaxHP(){return max_hp_;}


void Player::PickupPotion(){healthpotions_ += 1;}

void Player::UsePotion(){
    if (healthpotions_ > 0){
        hp_ += 25;              // health potion heals 25 hp
        healthpotions_ -= 1;
        if (hp_ > max_hp_){
            hp_ = max_hp_;
        }
    }
}

void Player::UpgradeWeapon(int dmgplus, int rangeplus, float rateplus, float speedplus){
    weapon_.Upgrade(dmgplus, rangeplus, rateplus, speedplus);
}

void Player::addMaxHP(int add){
    max_hp_ += add;
    hp_ += add;
}

std::pair<int, float> Player::getWeaponStats(){
    float rate = weapon_.GetFireRate();
    int damage = weapon_.GetDamage();
    return std::make_pair(damage, rate);
}

void Player::UpgradeSpeed(float rate){
    speed_ = speed_ * rate;
}

void Player::takeDamage(int dmg) { 
    hp_ -= dmg;
    if(hp_ <= 0) {
        body_.setPosition(-100.f,-100.f);
        deadCheck = true;
    }
}

sf::CircleShape Player::getBody() {
    return body_;
}

void Player::update(sf::Time deltaTime, sf::RenderWindow* window)
{
    //Make position of weapon the player position with a small offset
    weaponBody_.setPosition(body_.getPosition().x-20.f, body_.getPosition().y);

    // Restart all values if game is restarted
    if(restartCheck)
    {
        hp_ = 100;
        max_hp_ = 100;
        progress_ = 0;
        healthpotions_ = 0;
        speed_ = 15;
        body_.setPosition(800,600);
        weapon_.SetToDefault();
        titleScreenCheck = false;
    }

    waitTime_ += 0.2;

    //Get the mouse position in the window relative to the player position, then normalize it so that the vector is of size 1
    mouseDir_ = sf::Vector2f(sf::Mouse::getPosition(*window).x - getPosition().x, sf::Mouse::getPosition(*window).y - getPosition().y);
    auto mouseDirLength = sqrt(mouseDir_.x*mouseDir_.x + mouseDir_.y*mouseDir_.y);
    mouseDir_ = sf::Vector2f(mouseDir_.x/mouseDirLength, mouseDir_.y/mouseDirLength);

    if(mAttack && waitTime_ >= weapon_.GetFireRate()) {
        waitTime_ = 0;
        projectiles.push_back(Projectile(weapon_.GetDamage(),weapon_.GetRange(),weapon_.GetSpeed()));
        projectiles.back().body_.setPosition(body_.getPosition());            
        projectiles.back().setDirection(mouseDir_);
    }


    for (int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i].UpdateProjectile(deltaTime);

        //projectiles disappear when hitting a wall
        if(projectiles[i].getPosition().x > 1550 || projectiles[i].getPosition().x < 25 || projectiles[i].getPosition().y < 30 || projectiles[i].getPosition().y > 1100) {
            projectiles.erase(projectiles.begin() + i);
        }
    }
    
    sf::Vector2f movement(0.f, 0.f);
    float scaleFactor = 1/1.414; //To prevent the player from moving faster diagonally

    //Is player movement restricted?
    if(getPosition().x > 1465)
    {
        mIsRestrictedRight = true;
    }
    else {mIsRestrictedRight = false;}

    if(getPosition().x < 40)
    {
        mIsRestrictedLeft = true;
    }
    else {mIsRestrictedLeft = false;}

    if(getPosition().y < 50)
    {
        mIsRestrictedUp = true;
    }
    else {mIsRestrictedUp = false;}

    if(getPosition().y > 1050)
    {
        mIsRestrictedDown = true;
    }
    else {mIsRestrictedDown = false;}

    if(mIsMovingUp && mIsMovingRight && (!mIsRestrictedUp && !mIsRestrictedRight)) {
        direction_ = sf::Vector2f(1.0f * scaleFactor, -1.0f * scaleFactor);
        movement.y -= (1.f * speed_ * scaleFactor);
        movement.x += (1.f * speed_ * scaleFactor);
    }
    else if(mIsMovingUp && mIsMovingLeft && (!mIsRestrictedUp && !mIsRestrictedLeft)) {
        direction_ = sf::Vector2f(-1.0f * scaleFactor, -1.0f * scaleFactor);
        movement.y -= (1.f * speed_ * scaleFactor);
        movement.x -= (1.f * speed_ * scaleFactor);
    }
    else if(mIsMovingDown && mIsMovingRight && (!mIsRestrictedDown && !mIsRestrictedRight)) {
        direction_ = sf::Vector2f(1.0f * scaleFactor, 1.0f * scaleFactor);
        movement.y += (1.f * speed_ * scaleFactor);
        movement.x += (1.f * speed_ * scaleFactor);
    }
    else if(mIsMovingDown && mIsMovingLeft && (!mIsRestrictedDown && !mIsRestrictedLeft)) {
        direction_ = sf::Vector2f(-1.0f * scaleFactor, 1.0f * scaleFactor);
        movement.y += (1.f * speed_ * scaleFactor);
        movement.x -= (1.f * speed_ * scaleFactor);
    }
    else {
    if(mIsMovingUp && !mIsRestrictedUp) {
        movement.y -= (1.f * speed_);
        direction_ = sf::Vector2f(0.0f, -1.0f);
    }
    if(mIsMovingDown && !mIsRestrictedDown) {
        direction_ = sf::Vector2f(0.0f, 1.0f);
        movement.y += (1.f * speed_);
    }
    if(mIsMovingLeft && !mIsRestrictedLeft) {
        direction_ = sf::Vector2f(-1.0f, 0.0f);
        movement.x -= (1.f * speed_);
    }
    if(mIsMovingRight && !mIsRestrictedRight) {
        direction_ = sf::Vector2f(1.0f, 0.0f);
        movement.x += (1.f * speed_);
    }
    }
    //Move the player
    body_.move(movement);
    
}


void Player::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
    else if (key == sf::Keyboard::R)
        UsePotion();
    else if (key == sf::Keyboard::P)
        restartCheck = true;
    else if (key == sf::Keyboard::Space)
        titleScreenCheck = true;
    else if (key == sf::Keyboard::Enter)
        cheatKill = true;
}

void Player::handleMouseInput(sf::Mouse::Button button, bool isPressed)
{
    if(button == sf::Mouse::Button::Left)
    {
        mAttack = isPressed;
    }
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body_);
    window.draw(weaponBody_);
}

void Player::UseDoor(float newX, float newY) {
    body_.setPosition(newX,newY);
    progress_++;
}

