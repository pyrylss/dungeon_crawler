#include "game.hpp"
/*IOStream needed for debugging purposes*/
#include <iostream>
#include <string>


Game::Game()
: mWindow(sf::VideoMode(1600, 1200), "Dungeon wizard")
, mPlayer()
, mLevel()
, mStats()
, mDoors()
{
    srand(time(0));
}

void Game::run()
{
    sf::Time TimePerFrame = sf::seconds(1.f/60.f); 
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    
    mLevel.createBorder();
    mLevel.createMonsters(mPlayer.progress_);

    //Title screen and spacebar text
    titleScreenTexture_.loadFromFile("src/Sprites/title.png"); 
    titleScreen_.setTexture(&titleScreenTexture_);
    titleScreen_.setSize(sf::Vector2f(1600.f,1200.f));
    titleScreen_.setPosition(0,0);
    sf::Font font;
    font.loadFromFile("src/Qdbettercomicsans-jEEeG.ttf");
    titleText_.setFont(font);
    titleText_.setString("Start the game with SPACEBAR");
    titleText_.setFillColor(sf::Color::White);
    titleText_.setCharacterSize(90);
    titleText_.setPosition(200,600);


    while (mWindow.isOpen()) // game runs constantly while the window is open
    {
        //If player wants to restart then all enemies die and the player is teleported back to the game
        if(mPlayer.restartCheck)
        {
            mPlayer.restartCheck = false;
            for(auto i = mLevel.monsterList_.begin(); i != mLevel.monsterList_.end();)
            {
                i = mLevel.monsterList_.erase(i);
            }
            mLevel.createMonsters(mPlayer.progress_);
            mPlayer.deadCheck = false;
        }

        //If cheats are on then kill all enemies immediately
        if(mPlayer.cheatKill)
        {
            mStats.cheatCheck = true;
            for(auto i = mLevel.monsterList_.begin(); i != mLevel.monsterList_.end();)
            {
                i = mLevel.monsterList_.erase(i);
            }
            mPlayer.cheatKill = false;
        }

        //Check if player has lost
        if(mPlayer.GetHP() <= 0)
        {
            mStats.loseCheck = true;
        }
        else
        {
            mStats.loseCheck = false;
        }

        if(mPlayer.progress_ == 10 && mLevel.monsterList_.size() == 0) {  
            mStats.winCheck = true;
        } else {
            mStats.winCheck = false;
        }


        // by making sure the game renders in fixed time every time, we avoid lag
        // tecnique from the book "SFML Game Development", Haller, Hanson, Moreira, 2013, UK, page 22-23
        timeSinceLastUpdate += clock.restart(); // keeps track of time since last calling the update functions

        while(timeSinceLastUpdate > TimePerFrame)
        
        {
            timeSinceLastUpdate -= TimePerFrame; 
            processEvents();
            // updates the positions of the player, monsters and projectiles
            mPlayer.update(TimePerFrame, &mWindow);
            //Update position for each monster, and additionally check collision with player
            unsigned long i = 0;
            while((i < mLevel.monsterList_.size()) && !mPlayer.deadCheck)
            {
                mLevel.monsterList_[i].update(TimePerFrame, mPlayer);
                i++;
            }
        }

        render(); 
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            //Check if keyboard event or mouse event
            case sf::Event::KeyPressed:
                mPlayer.handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                mPlayer.handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::MouseButtonPressed:
                mPlayer.handleMouseInput(event.mouseButton.button, true);
                break;
            case sf::Event::MouseButtonReleased:
                mPlayer.handleMouseInput(event.mouseButton.button, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
            default:
                break;
        }

        // Checks if doors are open and if the player is near enough to go trough.

        if(mLevel.monsterList_.size() == 0 &&  mPlayer.progress_ < 10 && mPlayer.titleScreenCheck){
            sf::Vector2f Pos = mPlayer.getPosition();
            // left door
            if(Pos.x <= 100.f && Pos.y >= 500.f && Pos.y <= 850.f){
                mDoors.PickupPrize(mPlayer, 1);
                mPlayer.UseDoor(1425.f,720.f);
                mLevel.createBorder();
                mLevel.createMonsters(mPlayer.progress_*2);
            }
            //middle door
            if(Pos.x <= 950.f && Pos.x >= 600.f && Pos.y <= 100.f){
                mDoors.PickupPrize(mPlayer, 2);
                mPlayer.UseDoor(975.f,1000.f);
                mLevel.createBorder();
                mLevel.createMonsters(mPlayer.progress_*2);
            }
            if(Pos.x >= 1450.f && Pos.y >= 500.f && Pos.y <= 850.f){
                mDoors.PickupPrize(mPlayer, 3);
                mPlayer.UseDoor(100.f,720.f);
                mLevel.createBorder();
                mLevel.createMonsters(mPlayer.progress_*2);
            }
            
        }
    }
}

void Game::render()
{
    mWindow.clear();
    mLevel.DrawAll(mWindow);
    mPlayer.Draw(mWindow);
    mStats.DrawUi(mPlayer, mWindow);
    if(mLevel.monsterList_.size() == 0 && mPlayer.progress_ < 10) {mDoors.Draw(mWindow); } //Draw doors only if all monsters are dead

    //Next two loops work as projectile collision detection and rendering of these projectiles. Rendering could be decoupled from coll. detection
        for (int i = 0; i < mPlayer.projectiles.size(); i++)
	    {
		    mPlayer.projectiles[i].DrawProjectile(mWindow);
            //Monster takes damage if projectile hits it
            for(int j = 0; j < mLevel.monsterList_.size(); j++)
            {
                if(mLevel.monsterList_[j].body_.getGlobalBounds().contains(mPlayer.projectiles[i].getPosition())) {
                    mLevel.monsterList_[j].takeDamage(10);
                    if(mLevel.monsterList_[j].hp_ <= 0) {mLevel.monsterList_.erase(mLevel.monsterList_.begin() + j);}
                    mPlayer.projectiles.erase(mPlayer.projectiles.begin() + i);
                    break;
                }
            }
        }

        for(int j = 0; j < mLevel.monsterList_.size(); j++)
        {
            for (int i = 0; i < mLevel.monsterList_[j].projectiles.size(); i++)
            {
                mLevel.monsterList_[j].projectiles[i].DrawProjectile(mWindow);

                //Player takes damage if projectile hits it
                if(abs(mPlayer.getPosition().x - mLevel.monsterList_[j].projectiles[i].getPosition().x) < 40 && abs(mPlayer.getPosition().y - mLevel.monsterList_[j].projectiles[i].getPosition().y) < 40) {
                    mPlayer.takeDamage(10);
                    mLevel.monsterList_[j].projectiles.erase(mLevel.monsterList_[j].projectiles.begin() + i);
                }
            }
        }
    if(!mPlayer.titleScreenCheck) {mWindow.draw(titleScreen_); mWindow.draw(titleText_);} //Draw title screen on top on start

    mWindow.display();
}
