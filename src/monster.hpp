#include <SFML/Graphics.hpp>
#include "player.hpp"
#include <cmath>

#ifndef MONSTER
#define MONSTER

class Monster {
public:

    Monster(float posX, float posY, int hp, float size, float speed, std::string texturePath); //Additional variable would be the weapon once that class is implemented

    void takeDamage(int dmg);

    void update(sf::Time deltaTime, Player player);

    sf::Vector2f getPosition();

    void Draw(sf::RenderWindow& window);

    void ModWeapon(Weapon wpn);

    std::vector<Projectile> projectiles;

public:
    sf::Texture monsterTexture_;
    
    int hp_;
    std::string name_;
    Weapon weapon_;
    int damage_;
    sf::CircleShape body_;
    sf::Vector2f direction_;
    float waitTime_;
    float speed_;
};
class BossSlime: public Monster
{
    public:
        BossSlime(float posX, float posY) : Monster(posX, posY, 500, 150.f, 0.5, ("src/Sprites/SLIME.png"))
        {
            weapon_= Weapon(15, 10, 0.1, 20.f);
        }

};

class GreenSlime: public Monster
{
    public:
        GreenSlime(float posX, float posY) : Monster(posX, posY, 35, 60.f, 1.f, ("src/Sprites/SLIME.png"))
        {            
            weapon_= Weapon(10, 10, 0.8, 20.f);
        }
};

class RedSlime: public Monster
{
    public:
        RedSlime(float posX, float posY) : Monster(posX, posY, 75, 70.f, 1.5, ("src/Sprites/redSlime.png"))
        {
            weapon_= Weapon(12, 10, 0.4, 25.f);
        }
};

class BlueSlime: public Monster
{
    public:
        BlueSlime(float posX, float posY) : Monster(posX, posY, 50, 50.f, 2.f, ("src/Sprites/blueSlime.png"))
        {
            weapon_= Weapon(5, 10, 0.2, 15.f);
        }
};


#endif
