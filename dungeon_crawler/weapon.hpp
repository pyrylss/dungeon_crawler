#include "projectile.hpp"

#ifndef WEAPON
#define WEAPON
/*      
        Weapon is used to launch Projectiles. Weapon class determines the on hit damage,
        range, speed of the projetile and how often the projectile can be launched (fireRate). Firerate tells
        how many seconds it takes to launch the next projectile. Default weapon has damage of 5, range of 10
        and firerate of 2 and projectile speed of 50. 
*/

class Weapon
{
public:

	Weapon(int damage = 5, int range = 10, float fireRate = 2.f, float speed = 50.f) {
        dmg_ = damage;
        rng_ = range;
        rate_ = fireRate;
        spd_ = speed;
    }

	~Weapon() {}

    float GetFireRate() { return rate_; }

    int GetDamage() {return dmg_;}

    int GetRange() {return rng_;}

    float GetSpeed() {return spd_;}

    void Upgrade(int dmgplus, int rangeplus, float rateplus, float speedplus){
        dmg_ += dmgplus;
        rng_ += rangeplus;
        rate_ += rateplus;
        spd_ += speedplus;
    }

    void SetToDefault()// sets all values to default
    { 
        dmg_ = 5;
        rng_ = 10;
        rate_ = 2.f;
        spd_ = 50.f;
    }

private:

    int dmg_;
    int rng_;
    float rate_;
    float spd_;
};
#endif