#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__

#include "ObjectBase.h"
#include<math.h>
class GameObject : public ObjectBase{
public:
  GameObject(int imageID, int x, int y, int direction, int layer, double size):ObjectBase(imageID,x,y,direction,layer,size),m_is_dead(false){};
  virtual void Update()=0;
  const bool collide(GameObject*,GameObject*) const;
  const bool Get_is_dead() const;
  const void Set_is_dead(bool);
private:
  bool m_is_dead;
};

#endif