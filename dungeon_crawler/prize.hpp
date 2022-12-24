#include "player.hpp"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#ifndef PRIZE
#define PRIZE

class Prize
{
    /* The base class for prizes placed on the doors

    */
   
private:

    sf::Color color_; // color for the type of prize
    sf::Text flavortxt_; // text to be displayed next to the prize
    sf::RectangleShape sprite_ = sf::RectangleShape(sf::Vector2f(100, 100));
    

    sf::Font font_;

public:
    Prize();
    virtual void PickUp(Player& player){};
    void Draw(sf::RenderWindow& mWindow, int x, int y);

    friend class Healthpotion;
    friend class Weaponupgrade;
    friend class ExtraHP;
    friend class Speedboost;
};


Prize::Prize(): font_(){

        flavortxt_.setCharacterSize(20);

        sprite_.setFillColor(sf::Color::Black);
        sprite_.setOutlineThickness(10.f);

}


void Prize::Draw(sf::RenderWindow& mWindow, int x, int y){
    font_.loadFromFile("src/Qdbettercomicsans-jEEeG.ttf");
    flavortxt_.setFont(font_);
    sprite_.setOutlineColor(color_);
    sprite_.setPosition(sf::Vector2f(x, y));
    flavortxt_.setPosition(sf::Vector2f(x + 5, y + 5));
    mWindow.draw(sprite_);
    mWindow.draw(flavortxt_);

}
#endif