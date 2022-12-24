#ifndef HPOTION
#define HPOTION
#include "prize.hpp"

class Healthpotion : public Prize
/*
Healthpotion class: each health potion heals 25HP
*/
{
public:
    Healthpotion();
    virtual void PickUp(Player& player);
    ~Healthpotion();
};
#endif

Healthpotion::Healthpotion() : Prize()
{
    color_ = sf::Color::Red;
    flavortxt_.setString("Health\nPotion\n+25 HP");
}

void Healthpotion::PickUp(Player& player){
    player.PickupPotion();
}

Healthpotion::~Healthpotion()
{
}
