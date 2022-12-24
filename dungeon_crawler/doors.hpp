#include <SFML/Graphics.hpp>
#include "healthpotion.hpp"
#include "speedboost.hpp"
#include "weaponupgrade.hpp"
#include "extraHP.hpp"
#include <vector>
#include <random>
#include <variant>
/* 
A class for the doors. Just three rectangles with prizes in them.
No cpp file cus do we really need one?

*/
#ifndef DOORS
#define DOORS
class Doors
{

private:
    sf::RectangleShape leftdoor, middoor, rightdoor;
    sf::Texture doorTexture_;
    std::vector<Prize*> possible_ptrs_; //stores pointers to the possible prizes
    
    //Different tiers of prizes defined here. More could be added exponentially.
    Healthpotion p1= Healthpotion();
    ExtraHP p2= ExtraHP(20);
    Speedboost p3= Speedboost(0.2);
    Weaponupgrade p4= Weaponupgrade(5, 0, 0, 0.2);
    Weaponupgrade p5= Weaponupgrade(1, 0, 0.2, 0.1);
    ExtraHP p6= ExtraHP(5);
    Weaponupgrade p7= Weaponupgrade(3, 1, 0, 0);
    Speedboost p8= Speedboost(0.10);
    ExtraHP p9= ExtraHP(10);
    Weaponupgrade p10= Weaponupgrade(0, 0, 0.3, 0.5);

    // indexes of the prizes to be placed on the door (from the possible_ptrs_ list)
    int left_index;
    int mid_index;
    int right_index;
    
    //Healthpotion leftprize;
    //Healthpotion midprize;
    //ExtraHP rightprize;

public:
    Doors();
    void GeneratePrizeList();
    void NewIndexes(); // sets new indexes for the prizes
    void Draw(sf::RenderWindow &mWindow);
    void PickupPrize(Player& player, int doornum);
};
#endif


void Doors::GeneratePrizeList(){
    //Populate our lists for prizes

    possible_ptrs_.push_back(&p1);

    possible_ptrs_.push_back(&p2);

    possible_ptrs_.push_back(&p3);

    possible_ptrs_.push_back(&p4);

    possible_ptrs_.push_back(&p5);

    possible_ptrs_.push_back(&p6);

    possible_ptrs_.push_back(&p7);

    possible_ptrs_.push_back(&p8);


    possible_ptrs_.push_back(&p9);

    possible_ptrs_.push_back(&p10);
    }

void Doors::NewIndexes(){
    left_index = rand() % 10;
    mid_index = rand() % 10;
    right_index = rand() % 10;
    while (mid_index == left_index){
        mid_index = rand() % 10;
    }
    while (right_index == mid_index || right_index == left_index){
        right_index = rand() % 10;
    }
}


Doors::Doors() {
        GeneratePrizeList();

        NewIndexes();
        
        doorTexture_.loadFromFile("src/Sprites/door.png");

        leftdoor.setSize(sf::Vector2f(150.f,150.f));
        leftdoor.setPosition(sf::Vector2f(20, 500)); 
        leftdoor.setTexture(&doorTexture_);

        middoor.setSize(sf::Vector2f(150,150));
        middoor.setPosition(sf::Vector2f(600, 20));
        middoor.setTexture(&doorTexture_);

        rightdoor.setSize(sf::Vector2f(150,150));
        rightdoor.setPosition(sf::Vector2f(1420, 500));
        rightdoor.setTexture(&doorTexture_);

}


void Doors::Draw(sf::RenderWindow &mWindow){
        mWindow.draw(leftdoor);
        mWindow.draw(rightdoor);
        mWindow.draw(middoor);

        possible_ptrs_[left_index]->Draw(mWindow, 50 ,670);
        possible_ptrs_[mid_index]->Draw(mWindow, 750, 50);
        possible_ptrs_[right_index]->Draw(mWindow, 1450, 670);
    }

void Doors::PickupPrize(Player& player, int doornum){
    if (doornum == 1){ 
       possible_ptrs_[left_index] ->PickUp(player); 
    }
    if (doornum == 2){
        possible_ptrs_[mid_index]->PickUp(player);
    }
    if (doornum == 3){
        possible_ptrs_[right_index]->PickUp(player);
    }
    NewIndexes();
    
}
