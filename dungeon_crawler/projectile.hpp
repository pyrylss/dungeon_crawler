#include <SFML/Graphics.hpp>

#ifndef PROJECTILE
#define PROJECTILE

/*	Projectile is an object launched by weapon. Projectile damages the player or monsters
	when hit. Projectile class stores the information about damage, range, shape, direction and position
	of the projectile and has the functions to update and draw it.
*/

class Projectile 
{
public:

    Projectile(int damage = 5, int range = 10, float speed = 15.f);

    ~Projectile() {}

	void SetPosition();						// sets the starting position of the projectile according to players position
	void setDirection(sf::Vector2f direction); // sets the projectile direction


	void UpdateProjectile(sf::Time deltaTime);	// Updates the position of the projectile

	sf::Vector2f getPosition();
					
	void DrawProjectile(sf::RenderWindow& window);	// Draws the projectile body to the window according to current position	
	
	sf::CircleShape body_;
	sf::Vector2f direction_;
	sf::Vector2f position_;
private:
	sf::Texture projectileTexture_;
	int dmg_;
    int rng_;
	float speed_;
};

#endif