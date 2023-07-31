#include "stats.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <utility>

Stats::Stats()
{
 // empty now, 
 // TODO: move most of the build stuff (fonts, colors etc. here)
 potionTexture_.loadFromFile("src/Sprites/potion.png");
}

void Stats::DrawUi(Player& player, sf::RenderWindow& window){
    // stats square for hp
    sf::RectangleShape hprect; 
    hprect.setSize(sf::Vector2f(300, 100));
    hprect.setOutlineColor(sf::Color::Red);
    hprect.setOutlineThickness(10);
    hprect.setFillColor(sf::Color::Black);

    //Potion icon
    sf::CircleShape potionIcon;
    potionIcon.setTexture(&potionTexture_);
    potionIcon.setRadius(40.f);
    potionIcon.setPosition(1470,65);

    // stats square for potions
    sf::RectangleShape potionrect; 
    potionrect.setSize(sf::Vector2f(250, 100));
    potionrect.setOutlineColor(sf::Color::Red);
    potionrect.setOutlineThickness(10);
    potionrect.setFillColor(sf::Color::Black);

    // stats square for weapon
    sf::RectangleShape weaponrect; 
    weaponrect.setSize(sf::Vector2f(250, 150));
    weaponrect.setOutlineColor(sf::Color::Red);
    weaponrect.setOutlineThickness(10);
    weaponrect.setFillColor(sf::Color::Black);

    sf::Font font;
    //font.loadFromFile("Qdbettercomicsans-jEEeG.ttf");
    font.loadFromFile("src/Qdbettercomicsans-jEEeG.ttf");
    
    //HP text
    sf::Text hptxt;
    hptxt.setString("HP: " + std::to_string(player.GetHP()) + "/" + std::to_string(player.GetMaxHP()));
    hptxt.setFont(font);
    hptxt.setFillColor(sf::Color::White);
    hptxt.setCharacterSize(50);

    //Potion text
    sf::Text potiontxt;
    potiontxt.setString("Potions: " + std::to_string(player.GetPotionNum()) + "\nR to use");
    potiontxt.setFont(font);
    potiontxt.setFillColor(sf::Color::White);
    potiontxt.setCharacterSize(30);

    //Cheat text
    sf::Text cheattxt;
    cheattxt.setString("CHEATER!!!");
    cheattxt.setFont(font);
    cheattxt.setFillColor(sf::Color::Red);
    cheattxt.setCharacterSize(60);

    //Lose text
    sf::Text losetxt;
    losetxt.setString("You perished :(\nPress P to restart");
    losetxt.setFont(font);
    losetxt.setFillColor(sf::Color::Red);
    losetxt.setCharacterSize(120);

    //Win text
    sf::Text wintxt;
    wintxt.setString("You win! :)\nPress P to restart");
    wintxt.setFont(font);
    wintxt.setFillColor(sf::Color::Green);
    wintxt.setCharacterSize(120);

    //Weapon text
    sf::Text weapontxt;
    std::pair<int, float> weaponstats = player.getWeaponStats();
    weapontxt.setString("WEAPON \nDamage: " + std::to_string(weaponstats.first) + "\nSpeed: " + std::to_string(weaponstats.second));
    weapontxt.setFont(font);
    weapontxt.setFillColor(sf::Color::White);
    weapontxt.setCharacterSize(30);    

    //Progress text
    sf::Text progresstxt;
    progresstxt.setString("Rooms cleared: " + std::to_string(player.progress_-1));
    progresstxt.setFont(font);
    progresstxt.setFillColor(sf::Color::White);
    progresstxt.setCharacterSize(30);

    // places the box and text on window
    hprect.setPosition(50, 50);
    hptxt.setPosition(60, 60);
    potionrect.setPosition(1300, 50);
    potiontxt.setPosition(1310, 60);
    cheattxt.setPosition(60,150);
    progresstxt.setPosition(1310,200);

    if(loseCheck) {losetxt.setPosition(300,300);}
    else {losetxt.setPosition(-300.f,-300.f);}

    if(winCheck) {wintxt.setPosition(300,300);}
    else {wintxt.setPosition(-300.f,-300.f);}

    weaponrect.setPosition(1300, 1000);
    weapontxt.setPosition(1310, 1010);

    //Draw text onto the screen
    window.draw(hprect);
    window.draw(hptxt);
    window.draw(potionrect);
    window.draw(potiontxt);
    window.draw(weaponrect);
    window.draw(weapontxt);
    window.draw(potionIcon);
    window.draw(progresstxt);
    if(cheatCheck) {window.draw(cheattxt);}
    window.draw(losetxt);
    window.draw(wintxt);
}
