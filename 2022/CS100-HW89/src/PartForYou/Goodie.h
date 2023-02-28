#ifndef __GOODIE_H
#define __GOODIE_H

#include "GameObjects.h"
#include "GameWorld.h"
#include "Spaceship.h"
#include <algorithm>

class Goodie:public GameObject
{
public:
  Goodie(int imageID, int x, int y, int direction, int layer, double size):GameObject(imageID,x,y,direction,layer,size){};
  virtual void Update()=0;
private:
};


class HP_Restore:public Goodie{
public:
  HP_Restore(int x, int y):Goodie(IMGID_HP_RESTORE_GOODIE,x,y,0,2,0.5f){};
  virtual void Update();
private:
};


class Power_up:public Goodie{
public:
  Power_up(int x, int y):Goodie(IMGID_POWERUP_GOODIE,x,y,0,2,0.5f){};
  virtual void Update();
private:
};


class Meteor_Goodie:public Goodie{
public:
  Meteor_Goodie(int x, int y):Goodie(IMGID_METEOR_GOODIE,x,y,0,2,0.5f){};
  virtual void Update();
private:
};

#endif