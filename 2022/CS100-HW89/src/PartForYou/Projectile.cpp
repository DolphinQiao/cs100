#include "Projectile.h"
class GameWorld;
const void Projectile::Set_damage(int damage)
{
  m_damage=damage;
}
const int Projectile::Get_damage()const{
  return m_damage;
}
void Blue_bullet::Update()
{
  if(Get_is_dead()) return;
  if(GetY()>=WINDOW_HEIGHT)
  {
    Set_is_dead(true);
    return;
  }
  for(std::list<GameObject*>::iterator it=theWorld->Get_pos_l()->begin();it!=theWorld->Get_pos_l()->end(); ++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Enemy*>(*it)!=nullptr&&collide(this,*it))
    {
      dynamic_cast<Enemy*>(*it)->Set_HP(dynamic_cast<Enemy*>(*it)->Get_HP()-Get_damage());
      if(dynamic_cast<Enemy*>(*it)->Get_HP()<=0) (*it)->Set_is_dead(true), dynamic_cast<Enemy*>(*it)->destroy();
      Set_is_dead(true);
      return;
    }
  }
  MoveTo(GetX(),GetY()+6);
  for(std::list<GameObject*>::iterator it= theWorld->Get_pos_l()->begin();it!= theWorld->Get_pos_l()->end();++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Enemy*>(*it)!=nullptr&&collide(this,*it))
    {
      dynamic_cast<Enemy*>(*it)->Set_HP(dynamic_cast<Enemy*>(*it)->Get_HP()-Get_damage());
      if(dynamic_cast<Enemy*>(*it)->Get_HP()<=0) (*it)->Set_is_dead(true), dynamic_cast<Enemy*>(*it)->destroy();
      Set_is_dead(true);
      return;
    }
  }
}

void Meteor::Update(){
  if(Get_is_dead())return;
  if(GetY()>=WINDOW_HEIGHT)
  {
    Set_is_dead(true);
    return;
  }
  for(std::list<GameObject*>::iterator it= theWorld->Get_pos_l()->begin();it!= theWorld->Get_pos_l()->end();++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Enemy*>(*it)!=nullptr&&collide(this,*it))
    {
      (*it)->Set_is_dead(true), dynamic_cast<Enemy*>(*it)->destroy();
    }
  }
  MoveTo(GetX(),GetY()+2);
  SetDirection(GetDirection()+5);
  for(std::list<GameObject*>::iterator it= theWorld->Get_pos_l()->begin();it!= theWorld->Get_pos_l()->end();++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Enemy*>(*it)!=nullptr&&collide(this,*it))
    {
      (*it)->Set_is_dead(true), dynamic_cast<Enemy*>(*it)->destroy();
    }
  }
}

const int Red_bullet::Get_flymode()const{
  return m_fly_mode;
}
const void Red_bullet::Set_flymode(int flymode){
  m_fly_mode=flymode;
}

void Red_bullet::Update()
{
  if(Get_is_dead())return;
  if(GetY()<0)
  {
    Set_is_dead(true);
    return;
  }
  for(std::list<GameObject*>::iterator it=theWorld->Get_pos_l()->begin();it!= theWorld->Get_pos_l()->end();++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr&&collide(this,*it))
    {
        dynamic_cast<Dawnbreaker*>(*it)->Set_HP(dynamic_cast<Dawnbreaker*>(*it)->Get_HP()-Get_damage());
      Set_is_dead(true);
      return;
    }
  }
  switch (Get_flymode())
  {
  case 1://down
    MoveTo(GetX(),GetY()-6);
    SetDirection(180);
    break;
  
  case 2://right-down
    MoveTo(GetX()+2,GetY()-6);
    SetDirection(162);
    break;

  case 3://left-down
    MoveTo(GetX()-2,GetY()-6);
    SetDirection(198);
    break;
  }
  for(std::list<GameObject*>::iterator it=theWorld->Get_pos_l()->begin();it!=theWorld->Get_pos_l()->end();++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr&&collide(this,*it))
    {
      dynamic_cast<Dawnbreaker*>(*it)->Set_HP(dynamic_cast<Dawnbreaker*>(*it)->Get_HP()-Get_damage());
      Set_is_dead(true);
      return;
    }
  }
}