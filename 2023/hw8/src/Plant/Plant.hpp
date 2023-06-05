#ifndef PLANT_HPP__
#define PLANT_HPP__

#include "WorldBase.hpp"
#include "GameObject.hpp"
#include "utils.hpp"
#include "GameWorld.hpp"
#include "Background.hpp"
#include "Seed.hpp"

class Plant : public GameObject
{
public:
	Plant(ImageID imageID, int x, int y, int HP) :GameObject(imageID, x, y, LAYER_PLANTS, 60, 80, ANIMID_IDLE_ANIM), m_HP(HP) {};
	virtual bool is_zombie() override;
	virtual void Update() = 0;
	virtual void OnClick() override;
	virtual GameObject::COLLIDE_TYPE collide_class() override;
	int GetHP();
	void SetHP(int HP);
private:
	int m_HP;
};

class Sunflower : public Plant
{
public:
	Sunflower(int x, int y) : Plant(IMGID_SUNFLOWER, x, y, 300),m_count_down(0) { m_count_down = randInt(30, 600); };
	virtual void Update() override;
private:
	int m_count_down;
};

class Peashooter : public Plant
{
public:
	Peashooter(int x, int y) : Plant(IMGID_PEASHOOTER, x, y, 300) { m_count_down = 0; };
	virtual void Update() override;
private:
	int m_count_down;
};

class Wallnut : public Plant
{
public:
	Wallnut(int x, int y) : Plant(IMGID_WALLNUT, x, y, 4000) {}
	virtual void Update() override;
};

class Repeater : public Plant
{
public:
	Repeater(int x, int y) : Plant(IMGID_REPEATER, x, y, 300), m_count_down(0){}
	virtual void Update() override;
private:
	int m_count_down;
};

class Cherry_bomb : public Plant
{
public:
	Cherry_bomb(int x, int y) : Plant(IMGID_CHERRY_BOMB, x, y, 4000), m_count_down(15) {}
	virtual void Update() override;
private:
	int m_count_down;
};


#endif