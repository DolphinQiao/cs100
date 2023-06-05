#ifndef BACKGROUND_HPP__
#define BACKGROUND_HPP__

#include "WorldBase.hpp"
#include "GameObject.hpp"
#include "utils.hpp"
#include "GameWorld.hpp"
#include "Zombie.hpp"
#include "Plant.hpp"
#include "Seed.hpp"

class Other : public GameObject
{
public:
	Other(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID) :GameObject(imageID, x, y, layer, width, height, animID) {};
	virtual bool is_zombie() override;
	virtual void OnClick() = 0;
	virtual void Update() = 0;
	virtual GameObject::COLLIDE_TYPE collide_class() = 0;
};
class Background : public Other
{
public:
	Background() :Other(IMGID_BACKGROUND, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LAYER_BACKGROUND, WINDOW_WIDTH, WINDOW_HEIGHT, ANIMID_NO_ANIMATION) {}
	virtual void Update() override;
	virtual void OnClick() override;
	virtual GameObject::COLLIDE_TYPE collide_class() override;
};

class Sun: public Other
{
public:
	Sun(int x, int y, int drop_type) : Other(IMGID_SUN, x, y, LAYER_SUN, 80, 80, ANIMID_IDLE_ANIM), m_drop_time(0), m_drop_type(drop_type), m_acc(4), m_death_time(300)
	{
		if (drop_type == 1)//天上
		{
			m_drop_time = randInt(63, 263);
		}else//向日葵
		{
			m_drop_time = 12;
		}
	};
	virtual void Update() override;
	virtual void OnClick() override;
	virtual GameObject::COLLIDE_TYPE collide_class() override;
private:
	int m_drop_time;
	int m_drop_type;
	int m_acc;
	int m_death_time;
};
class Spot : public Other
{
public:
	Spot(int x, int y) : Other(IMGID_NONE, x, y, LAYER_UI, 60, 80, ANIMID_NO_ANIMATION) {}
	virtual void Update() override;
	virtual void OnClick() override;
	virtual GameObject::COLLIDE_TYPE collide_class() override;
};

class Mask : public Other
{
public:
	Mask(int x, int y, int cooldown) : Other(IMGID_COOLDOWN_MASK, x, y, LAYER_COOLDOWN_MASK, 50, 70, ANIMID_NO_ANIMATION), m_count_down(cooldown) {}
	virtual void Update() override;
	virtual void OnClick() override;
	virtual GameObject::COLLIDE_TYPE collide_class() override;
private:
	int m_count_down;
};

class Shovel : public Other
{
public:
	Shovel(): Other(IMGID_SHOVEL, 600, WINDOW_HEIGHT - 40, LAYER_UI, 50, 50, ANIMID_NO_ANIMATION){}
	virtual void Update() override;
	virtual void OnClick() override;
	virtual GameObject::COLLIDE_TYPE collide_class() override;
};

class Pea : public Other
{
public:
	Pea(int x, int y): Other(IMGID_PEA, x, y, LAYER_PROJECTILES, 28, 28, ANIMID_NO_ANIMATION){}
	virtual void Update() override;
	virtual void OnClick() override;
	virtual GameObject::COLLIDE_TYPE collide_class() override;
};

class Explosion : public Other
{
public:
	Explosion(int x, int y) : Other(IMGID_EXPLOSION, x, y, LAYER_PROJECTILES, 3 * LAWN_GRID_WIDTH, 3 * LAWN_GRID_HEIGHT, ANIMID_NO_ANIMATION), m_count_down(3) {};
	virtual void Update() override;
	virtual void OnClick() override;
	virtual GameObject::COLLIDE_TYPE collide_class() override;
private:
	int m_count_down;
};
#endif