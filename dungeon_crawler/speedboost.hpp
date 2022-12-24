#ifndef SPEEDBOOST
#define SPEEDBOOST
#include "prize.hpp"

class Speedboost : public Prize
{
    /*
    Speedboost class: Increases players maximum speed
    */
private:
    float boost_;
public:
    Speedboost(float boost);
    Speedboost(); // if no value is given, it is randomized
    virtual void PickUp(Player& player);
    ~Speedboost();
};
#endif

Speedboost::Speedboost(float boost) : Prize(), boost_(boost)
{
    flavortxt_.setString("Move\nspeed\n" + (std::to_string(boost_*100)).substr(0,4) +"%");
    color_ = sf::Color::Magenta;
}
Speedboost::Speedboost(){
    boost_ = rand() % 10;
    flavortxt_.setString("Move\nspeed\n" + std::to_string(boost_*100).substr(0,4) +"%");
    color_ = sf::Color::Magenta;
}

void Speedboost::PickUp(Player& player){
    player.UpgradeSpeed(boost_ + 1);
}

Speedboost::~Speedboost()
{
}
