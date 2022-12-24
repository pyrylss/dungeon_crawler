#include <SFML/Graphics.hpp>
#include <filesystem>

#include "monster.cpp"
#include "level.cpp"
#include "stats.cpp"
#include "doors.hpp"
#include "projectile.cpp"
#include "player.cpp"
/* General structure of the game class from "SFML Game Development", Haller, Hanson and Moreira, 2013, UK


Overall fuctions of the game: the game window and what happens inside it
*/
class Game
{
public: 
    Game(); // Creates a game object: the game window and player and monsters
    void run(); // Starts the game app and runs the needed functions 

private:
    void processEvents(); // Handles input from player (keypresses etc.)
    void render(); // Draws the items on the window

private:
    sf::RenderWindow mWindow;
    sf::RectangleShape titleScreen_;
    sf::Texture titleScreenTexture_;
    sf::Text titleText_;

    Player mPlayer;
    Level mLevel;
    Stats mStats;
    Doors mDoors;
};