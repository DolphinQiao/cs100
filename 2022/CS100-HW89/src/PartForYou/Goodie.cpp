#include "Goodie.h"
class GameWorld;
void HP_Restore::Update()
{
  if(Get_is_dead())return;
  if(GetY()<0)
  {
    Set_is_dead(true);
    return;
  }
  for(std::list<GameObject*>::iterator it=theWorld->Get_pos_l()->begin();it!=theWorld->Get_pos_l()->end();++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr&&collide(this,*it))
    {
      dynamic_cast<Dawnbreaker*>(*it)->Set_HP(std::min(100,dynamic_cast<Dawnbreaker*>(*it)->Get_HP()+50));
      theWorld->IncreaseScore(20);
      Set_is_dead(true);
      return;
    }
  }
  MoveTo(GetX(),GetY()-2);
  for(std::list<GameObject*>::iterator it=theWorld->Get_pos_l()->begin();it!=theWorld->Get_pos_l()->end();++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr&&collide(this,*it))
    {
      dynamic_cast<Dawnbreaker*>(*it)->Set_HP(std::min(100,dynamic_cast<Dawnbreaker*>(*it)->Get_HP()+50));
      theWorld->IncreaseScore(20);
      Set_is_dead(true);
      return;
    }
  }
}
void Power_up::Update()
{
  if(Get_is_dead())return ;
  if(GetY()<0)
  {
    Set_is_dead(true);
    return;
  }
  for(std::list<GameObject*>::iterator it=theWorld->Get_pos_l()->begin();it!=theWorld->Get_pos_l()->end();++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr&&collide(this,*it))
    {
      theWorld->Set_Powerup(theWorld->Get_Powerup()+1);
      theWorld->IncreaseScore(20);
      Set_is_dead(true);
      return;
    }
  }
  MoveTo(GetX(),GetY()-2);
  for(std::list<GameObject*>::iterator it=theWorld->Get_pos_l()->begin();it!=theWorld->Get_pos_l()->end();++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr&&collide(this,*it))
    {
      theWorld->Set_Powerup(theWorld->Get_Powerup()+1);
      theWorld->IncreaseScore(20);
      Set_is_dead(true);
      return;
    }
  }
}

void Meteor_Goodie::Update()
{
  if(Get_is_dead())return ;
  if(GetY()<0)
  {
    Set_is_dead(true);
    return ;
  }
  for(std::list<GameObject*>::iterator it=theWorld->Get_pos_l()->begin();it!=theWorld->Get_pos_l()->end();++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr&&collide(this,*it))
    {
      theWorld->Set_Meteor(theWorld->Get_Meteor()+1);
      theWorld->IncreaseScore(20);
      Set_is_dead(true);
      return;
    }
  }
  MoveTo(GetX(),GetY()-2);
  for(std::list<GameObject*>::iterator it=theWorld->Get_pos_l()->begin();it!=theWorld->Get_pos_l()->end();++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr&&collide(this,*it))
    {
      theWorld->Set_Meteor(theWorld->Get_Meteor()+1);
      theWorld->IncreaseScore(20);
      Set_is_dead(true);
      return;
    }
  }
}