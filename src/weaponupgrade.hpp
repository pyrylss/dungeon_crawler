#ifndef WEAPON_UPGRADE
#define WEAPON_UPGRADE
#include "prize.hpp"

class Weaponupgrade : public Prize
/*
Weapon Upgrade class: Upgrades 2 different stats of the weapon
*/
{
private:
    int dmgplus_;
    int rangeplus_;
    float rateplus_;
    float speedplus_;

public:
    Weaponupgrade(int dmgplus, int rangeplus, float rateplus, float speedplus);
    Weaponupgrade();// if no values are given, they are randomized
    virtual void PickUp(Player& player);
    ~Weaponupgrade();
};

#endif

Weaponupgrade::Weaponupgrade(int dmgplus, int rangeplus, float rateplus, float speedplus)
    :Prize(), dmgplus_(dmgplus), rangeplus_(rangeplus), rateplus_(rateplus), speedplus_(speedplus)
{
    color_ = sf::Color(119,136,153);
    std::string str = "Weapon";
    if (dmgplus_!=0){str += "\n+" + std::to_string(dmgplus_).substr(0,4) + " damage";}
    if(rangeplus_ != 0){str += "\n+" + std::to_string(rangeplus_).substr(0,4) + " range";}
    if(rateplus_ != 0){str += "\n+" + std::to_string(rateplus_).substr(0,4) + " firerate";}
    if(speedplus_ != 0){str += "\n+" + std::to_string(speedplus_).substr(0,4) + " speed";}
    flavortxt_.setString(str);
}

Weaponupgrade::Weaponupgrade(){
    dmgplus_ = rand() % 10;
    rateplus_ = static_cast<float>(rand() % 10)/10;
    rangeplus_=0;
    speedplus_=0;

    color_ = sf::Color(119,136,153);
    std::string str = "Weapon";
    if (dmgplus_!=0){str += "\n+" + std::to_string(dmgplus_).substr(0,4) + " damage";}
    if(rangeplus_ != 0){str += "\n+" + std::to_string(rangeplus_).substr(0,4) + " range";}
    if(rateplus_ != 0){str += "\n+" + std::to_string(rateplus_).substr(0,4) + " firerate";}
    if(speedplus_ != 0){str += "\n+" + std::to_string(speedplus_).substr(0,4) + "speed";}
    flavortxt_.setString(str);
}

void Weaponupgrade::PickUp(Player& player){
    player.UpgradeWeapon(dmgplus_, rangeplus_, rateplus_, speedplus_);
}

Weaponupgrade::~Weaponupgrade()
{
}
