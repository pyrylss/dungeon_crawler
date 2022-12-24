#include "prize.hpp"

Prize::Prize(std::string id): font_(){
        font_.loadFromFile("src/Qdbettercomicsans-jEEeG.ttf");
        prizetype.flavortxt.setFont(font_);
        prizetype.flavortxt.setCharacterSize(20);

        if (id == "W"){
            prizetype.type = id;
            prizetype.color = sf::Color::Black;
            prizetype.flavortxt.setString("Weapon\n+2 damage\n+0.2 speed");
        } 
        else if (id == "P"){
            prizetype.type = id;
            prizetype.color = sf::Color::Green;
            prizetype.flavortxt.setString("Health Potion\nHeals 15 HP");
        }
        else if(id == "M"){
            prizetype.type = id;
            prizetype.color = sf::Color::Red;
            prizetype.flavortxt.setString("+10 Max HP");
        }
        prizetype.sprite.setFillColor(prizetype.color);
}

void Prize::PickUp(Player player)
{
    if (prizetype.type == "P")    
        player.PickupPotion();
    else if (prizetype.type == "M")
    {
        player.addMaxHP(10);
    }
    else if (prizetype.type == "W")
    {
        player.UpgradeWeapon(2, 0.2);
    }
    
    
    taken_ = true;
}

void Prize::Draw(sf::RenderWindow& mWindow, int x, int y){
    if (!taken_){
        prizetype.sprite.setPosition(sf::Vector2f(x, y));
        prizetype.flavortxt.setPosition(sf::Vector2f(x - 30, y + 20));

        mWindow.draw(prizetype.sprite);
        mWindow.draw(prizetype.flavortxt);
    }
}
