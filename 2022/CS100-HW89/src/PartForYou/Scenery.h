#ifndef __SCENERY_H
#define __SCENERY_H

#include "GameObjects.h"
class GameWorld;
class Scenery:public GameObject{
public:
  Scenery(int imageID, int x, int y, int direction, int layer, double size):GameObject(imageID,x,y,direction,layer,size){};
  virtual void Update()=0;
private:
};

class Star:public Scenery{
public:
  Star(int x,int y,double size):Scenery(IMGID_STAR,x,y,0,4,size){};
  virtual void Update();
private:
};

class Explosion:public Scenery{
public:
  Explosion(int x,int y):Scenery(IMGID_EXPLOSION,x,y,0,3,4.5f),m_time(20){};
  const void Set_time(int);
  const int Get_time() const;
  virtual void Update();
private:
  int m_time;
};

#endif