#include "monster.hpp"
#include <SFML/Graphics.hpp>
Monster::Monster(float posX, float posY, int hp, float size, float speed, std::string texturePath)
{
    //Set important values here
    monsterTexture_.loadFromFile(texturePath);
    body_.setPosition(posX, posY);
    hp_ = hp;
    body_.setRadius(size);
    name_ = rand() % 100;
    direction_ = sf::Vector2f(1.0f, 0.0f);
    speed_ = speed;
}

void Monster::takeDamage(int dmg) { 
        hp_ -= dmg;
        if(hp_ < 0) body_.setRadius(60.f);
    }

void Monster::update(sf::Time deltaTime, Player player)
    {

    body_.setTexture(&monsterTexture_);

    float xDiff = player.getPosition().x - body_.getPosition().x;
	float yDiff = player.getPosition().y - body_.getPosition().y;

    waitTime_ += 0.01;

     if(waitTime_ >= weapon_.GetFireRate()) {
        waitTime_ = 0;
        projectiles.push_back(Projectile(weapon_.GetDamage(),weapon_.GetRange(),weapon_.GetSpeed()));
		projectiles.back().body_.setPosition(body_.getPosition().x + 20, body_.getPosition().y + 20);
		projectiles.back().setDirection(direction_);
    }

    for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i].UpdateProjectile(deltaTime);
	}

    float length = sqrt(xDiff*xDiff + yDiff*yDiff);
    sf::Vector2f movement(xDiff/length, yDiff/length);
    direction_ = sf::Vector2f(xDiff/length, yDiff/length);

    if(length > 150.f) {body_.move(movement*speed_);} // Stop moving if close enough to player
    }

sf::Vector2f Monster::getPosition() {
       return body_.getPosition();
    }

void Monster::Draw(sf::RenderWindow& window)
    {
	    window.draw(body_);

    }

void Monster::ModWeapon(Weapon wpn){
    weapon_ = wpn;
}