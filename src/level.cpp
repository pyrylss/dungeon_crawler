#include "level.hpp"
#include <SFML/Graphics.hpp>
#include "iostream"

Level::Level()
:   monsterList_(), points_(0) {
    levelTexture_.loadFromFile("src/Sprites/FLOOR.png", sf::IntRect(0,0,16,16));
}

void Level::createBorder()
{
    //Create vertical and horizontal borders
    sf::RectangleShape levelPiece;
    levelPiece.setSize(sf::Vector2f(1500.0f, 1100.0f));
    
    //Set texture to tile over the level piece
    levelTexture_.setRepeated(true);
    levelPiece.setTextureRect(sf::IntRect(0,0,256,256));
    levelPiece.setTexture(&levelTexture_, false);

    levelPiece.setOutlineColor(sf::Color (139,69,19));
    levelPiece.setOutlineThickness(10.f);
    levelPiece.setPosition(50.f,50.f);
    levelPiece_ = levelPiece;
}
void Level::createMonsters(int points)
{
    points_ = points;
    //While we still have points, add monsters to monsterList
    while(points_ > 0)
    {   
        int chooser = rand() % 3; //Choose a random number between 0 and 2

        // when progress reaches 7, boss enemy is spawned.
        if(points == 20) {
            BossSlime newMonster = BossSlime(rand() % 1000,rand() % 1000);
            monsterList_.push_back(newMonster);
            break;
        } 
        else if (chooser == 0) {
            GreenSlime newMonster = GreenSlime(rand() % 1000,rand() % 1000);
            monsterList_.push_back(newMonster);
            points_--;
        }
        else if(chooser == 1 && points_ >= 2) {
            RedSlime newMonster = RedSlime(rand() % 1000, rand() % 1000);
            monsterList_.push_back(newMonster);
            points_ = points_ - 2;
        }
        else if(chooser == 2 && points >= 2) {
            BlueSlime newMonster = BlueSlime(rand() % 1000, rand() % 1000);
            monsterList_.push_back(newMonster);
            points_ = points_ - 2;
        }
    }
}
void Level::DrawAll(sf::RenderWindow& window)
{
    window.draw(levelPiece_);

    for(auto it : monsterList_)
    {
        window.draw(it.body_);
    }
}