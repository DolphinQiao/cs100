#ifndef SEED_HPP__
#define SEED_HPP__

#include "WorldBase.hpp"
#include "GameObject.hpp"
#include "utils.hpp"
#include "GameWorld.hpp"
#include "Background.hpp"
#include "Plant.hpp"
#include "Zombie.hpp"

class Seed : public GameObject
{
public:
	Seed(ImageID imageID, int x, int y, int price, int cooldown_time, int type) :
		GameObject(imageID, x, y, LAYER_UI, 50, 70, ANIMID_NO_ANIMATION), m_price(price), m_cooldown_time(cooldown_time), m_type(type) {}
	virtual void Update() = 0;
	virtual void OnClick() override;
	virtual bool is_zombie() override;
	virtual GameObject::COLLIDE_TYPE collide_class() override;
	int Get_cooldown();
	//virtual void Plant() = 0;
private:
	int m_price;
	int m_cooldown_time;
	int m_type;
};

class Sunflower_seed : public Seed
{
public:
	Sunflower_seed() : Seed(IMGID_SEED_SUNFLOWER, 130, WINDOW_HEIGHT - 44, 50, 240, 1) {}
	virtual void Update() override;

};

class Peashooter_seed : public Seed
{
public:
	Peashooter_seed() : Seed(IMGID_SEED_PEASHOOTER, 190, WINDOW_HEIGHT - 44, 100, 240, 2) {}
	virtual void Update() override;
};

class Wallnut_seed : public Seed
{
public:
	Wallnut_seed() : Seed(IMGID_SEED_WALLNUT, 250, WINDOW_HEIGHT - 44, 50, 900, 3) {}
	virtual void Update() override;
};

class Cherrybomb_seed : public Seed
{
public:
	Cherrybomb_seed() : Seed(IMGID_SEED_CHERRY_BOMB, 310, WINDOW_HEIGHT - 44, 150, 1200, 4) {}
	virtual void Update() override;
};

class Repeater_seed : public Seed
{
public:
	Repeater_seed() : Seed(IMGID_SEED_REPEATER, 370, WINDOW_HEIGHT - 44, 200, 240, 5){}
	virtual void Update() override;
};

#endif