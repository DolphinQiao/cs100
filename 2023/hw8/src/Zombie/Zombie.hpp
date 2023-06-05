#ifndef ZOMBIE_HPP__
#define ZOMBIE_HPP__

#include "WorldBase.hpp"
#include "GameObject.hpp"
#include "utils.hpp"
#include "GameWorld.hpp"
#include "Background.hpp"
#include "Seed.hpp"
#include "Plant.hpp"

class Zombie : public GameObject
{
public:
	enum class STATUS_TYPE {
		WALKING, EATING, RUNNING, JUMPING, STOP
	};
	Zombie(ImageID imageID, int x, int y, AnimID animID, int HP): GameObject(imageID, x, y,LAYER_ZOMBIES, 20, 80, animID), m_HP(HP), m_status(Zombie::STATUS_TYPE::WALKING) {};
	virtual bool is_zombie() override;
	virtual void Update() = 0;
	virtual void OnClick() override;
	virtual GameObject::COLLIDE_TYPE collide_class() override;
	int GetHP();
	void SetHP(int HP);

	STATUS_TYPE GetStatus();
	void SetStatus(STATUS_TYPE Status);
	
private:
	int m_HP;
	STATUS_TYPE m_status;
};

class Regular_zombie : public Zombie
{
public:
	Regular_zombie(int x, int y) : Zombie(IMGID_REGULAR_ZOMBIE, x, y, ANIMID_WALK_ANIM, 200) {};
	virtual void Update();

private:
	
	/*
	* 1 walking
	* 2 eating
	*/
};

class Bucket_zombie : public Zombie
{
public:
	Bucket_zombie(int x, int y) : Zombie(IMGID_BUCKET_HEAD_ZOMBIE, x, y, ANIMID_WALK_ANIM, 1300) {};
	virtual void Update();
private:
	/*
	* 1 walking
	* 2 eating
	*/
};

class Vaulting_zombie : public Zombie
{
public:
	Vaulting_zombie(int x, int y) : Zombie(IMGID_POLE_VAULTING_ZOMBIE, x, y, ANIMID_RUN_ANIM, 340), m_count_down(0) { SetStatus(Zombie::STATUS_TYPE::RUNNING);};
	virtual void Update();
private:
	int m_count_down;
/*
* 1 walking
* 2 eating
* 3 running
* 4 jumping
* 5 stop
*/
};

#endif