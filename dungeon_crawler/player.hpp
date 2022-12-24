#include <SFML/Graphics.hpp>
#include <utility>
#include "weapon.hpp"
#include <cmath>

#ifndef PLAYER
#define PLAYER

/*  Player class contains information about the player stats and the functions
    for attacking and picking up items. Player will start with a default weapon
    and 100 hp.
*/

class Player 
{
public:
  
    Player();


   /* UseWeapon() function calls the Attack function of the weapon currently in use.
    Can be used every 1/fireRate second. (firerate is obtained form weapon_)
    to do: if ( time between function calls >= firerate) Attack(), else fail
*/
    void UseWeapon();

    sf::Vector2f getPosition();
 
    int GetHP();

    int GetPotionNum();

    int GetMaxHP();

    void PickupPotion();

    void UsePotion();

    void UpgradeWeapon(int dmgplus, int rangeplus, float rateplus, float speedplus);

    void addMaxHP(int add);

    std::pair<int, float> getWeaponStats(); // Returns a pair containin weapon damage and firerate

    void UpgradeSpeed(float rate);

    void takeDamage(int dmg);

    sf::CircleShape getBody();

    void update(sf::Time deltaTime, sf::RenderWindow* window);

    //Check keyboard buttons
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    //Check mouse buttons
    void handleMouseInput(sf::Mouse::Button button, bool isPressed);

    void Draw(sf::RenderWindow& window);
    // Moves player to opposing side of the room and adds progress.
    void UseDoor(float newX, float newY);

    std::vector<Projectile> projectiles;

private:
    sf::CircleShape body_;
    sf::Texture playerTexture;

    sf::CircleShape weaponBody_;
    sf::Texture weaponTexture_;

    int hp_;
    int max_hp_;
    int healthpotions_;
    //Check if input is pressed
    bool mIsMovingUp = false;
    bool mIsMovingDown = false;
    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;
    bool mAttack = false;
    //Check if player's movement is being restricted in any direction (eg. obstacle in the way)
    bool mIsRestrictedUp;
    bool mIsRestrictedDown;
    bool mIsRestrictedLeft;
    bool mIsRestrictedRight;

    Weapon weapon_;
    float waitTime_;
    float speed_;
public:
    sf::Vector2f direction_;
    sf::Vector2f mouseDir_;
    int progress_; // Check how far along player has progressed, this goes up by one when the player clears a room.
    bool deadCheck; // Bool to check if player is dead
    bool cheatKill; // Bool to check if kill cheat is on
    bool restartCheck;
    bool titleScreenCheck = false;
};

#endif