
#ifndef EXTRA_HP
#define EXTRA_HP
#include "prize.hpp"

class ExtraHP : public Prize
{
    /*
    Increases players maximum HP
    */
private:
    int extra_;
public:
    ExtraHP(int extra);
    ExtraHP(); // if no value is given, it is randomized
    virtual void PickUp(Player& player);
    ~ExtraHP();
};

ExtraHP::ExtraHP(int extra) : Prize(), extra_(extra){
    flavortxt_.setString(" +" + std::to_string(extra_) + " \n Max HP");
    color_ = sf::Color::Green;
}
ExtraHP::ExtraHP(){
    extra_ = rand() % 50;
    flavortxt_.setString(" +" + std::to_string(extra_) + " \n Max HP");
    color_ = sf::Color::Green;
}

void ExtraHP::PickUp(Player& player){
    player.addMaxHP(extra_);
}

ExtraHP::~ExtraHP()
{
}
#endif