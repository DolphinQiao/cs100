#ifndef __PROJECTILE_H
#define __PROJECTILE_H

#include "GameObjects.h"
#include "GameWorld.h"
#include "WorldBase.h"
#include "Spaceship.h"

class Projectile:public GameObject
{
public:
  Projectile(int imageID, int x, int y, int direction, int layer, double size,int damage):GameObject(imageID,x,y,direction,layer,size),m_damage(damage){};
  virtual void Update()=0;
  const int Get_damage()const;
  const void Set_damage(int);

private:
  int m_damage;
};

class Blue_bullet:public Projectile
{
public:
  Blue_bullet(int x, int y,double size,int damage):Projectile(IMGID_BLUE_BULLET,x,y,0,1,size,damage){};
  virtual void Update();
private:
};

class Meteor:public Projectile
{
public:
  Meteor(int x, int y,int damage):Projectile(IMGID_METEOR,x,y,0,1,2.0f,damage){};
  virtual void Update();
private:
};

class Red_bullet:public Projectile
{
public:
  Red_bullet(int x, int y,int direction,int damage,int fly_mode):Projectile(IMGID_RED_BULLET,x,y,direction,1,0.5f,damage){Set_flymode(fly_mode);};
  virtual void Update();
  const int Get_flymode()const;
  const void Set_flymode(int);
private:
  int m_fly_mode;
};


#endif