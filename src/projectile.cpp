#include "projectile.hpp"

Projectile::Projectile(int damage, int range, float speed) : dmg_(damage), rng_(range), speed_(speed) {
	body_.setRadius(20.f);
    body_.setFillColor(sf::Color::Magenta);
	projectileTexture_.loadFromFile("src/Sprites/PROJECTILE.png");
}

void Projectile::setDirection(sf::Vector2f direction) { direction_ = direction; }


void Projectile::UpdateProjectile(sf::Time deltaTime) {
	body_.setTexture(&projectileTexture_);

	sf::Vector2f movement(0.f, 0.f);

	movement.x += direction_.x * speed_; 
	movement.y += direction_.y * speed_;
	
	body_.move(movement);
}	

sf::Vector2f Projectile::getPosition() { return body_.getPosition(); }	
					
void Projectile::DrawProjectile(sf::RenderWindow& window) { window.draw(body_); }