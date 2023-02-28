#ifndef __SPACESHIP_H
#define __SPACESHIP_H

#include "GameObjects.h"
#include "GameWorld.h"
#include "WorldBase.h"
#include "Projectile.h"
#include "Scenery.h"
#include "Goodie.h"
#include <algorithm>

class Spaceship:public GameObject{
public:
  Spaceship(int imageID, int x, int y, int direction, int layer, double size):GameObject(imageID,x,y,direction,layer,size),m_HP(0),m_energy(0){};
  const int Get_HP() const;
  const void Set_HP(int);
  const int Get_energy()const;
  const void Set_energy(int);
  virtual void Update()=0;
private:
	int m_HP;
	int m_energy;
};
class Dawnbreaker:public Spaceship{
public:
  Dawnbreaker():Spaceship(IMGID_DAWNBREAKER,300,100,0,0,1.0f){Set_HP(100);Set_energy(10);};
  virtual void Update();
private:
};

class Enemy:public Spaceship
{
public:
  Enemy(int imageID,int x,int y,int HP,int speed,int attack,int energy):Spaceship(imageID,x,y,180,0,1.0f),m_speed(speed),m_attack(attack),m_fly_mode(0),m_fly_time(0){Set_HP(HP);Set_energy(energy);};
  const int Get_speed()const;
  const void Set_speed(int);
  const int Get_fly_mode()const;
  const int Get_attack()const;
  const void Set_fly_mode(int);
  const int Get_fly_time()const;
  const void Set_fly_time(int);
  virtual void Update()=0;
  virtual void destroy()=0;
private:
  int m_speed,m_fly_mode,m_attack,m_fly_time;
};
class Alphatron:public Enemy{
public:
  Alphatron(int x,int y,int HP,int speed,int attack):Enemy(IMGID_ALPHATRON,x,y,HP,speed,attack,25){};
  virtual void Update();
  virtual void destroy();
private:
};

class Sigmatron:public Enemy{
public:
  Sigmatron(int x,int y,int HP,int speed,int attack):Enemy(IMGID_SIGMATRON,x,y,HP,speed,attack,0){};
  virtual void Update();
  virtual void destroy();
private:
};

class Omegatron:public Enemy{
public:
  Omegatron(int x,int y,int HP,int speed,int attack):Enemy(IMGID_OMEGATRON,x,y,HP,speed,attack,50){};
  virtual void Update();
  virtual void destroy();
private:
};

#endif