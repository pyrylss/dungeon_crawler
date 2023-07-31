#include <SFML/Graphics.hpp>
#ifndef STATS
#define STATS
class Stats
{
private:
    /* fonts, styles etc will be added here */
    sf::Texture potionTexture_;
public:
    Stats(); // creates an empty instance 
    void DrawUi(Player& player, sf::RenderWindow& window); //draws the boxes for stats, need player to extract info
    bool cheatCheck;
    bool loseCheck;
    bool winCheck;
};

#endif
