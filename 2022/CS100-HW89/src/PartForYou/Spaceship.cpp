#include "Spaceship.h"
class GameWorld;
const int Spaceship::Get_energy() const
{
  return m_energy;
}
const int Spaceship::Get_HP() const{
  return m_HP;
}
const void Spaceship::Set_energy(int energy)
{
  m_energy=energy;
  return;
}
const void Spaceship::Set_HP(int HP)
{
  m_HP=HP;
  return;
}
void Dawnbreaker::Update()
{
  if(Get_is_dead())return;
  if(theWorld->GetKey(KeyCode::UP))
  {
    MoveTo(GetX(),GetY()+4);
  }
  if(theWorld->GetKey(KeyCode::DOWN))
  {
    MoveTo(GetX(),GetY()-4);
  }
  if(theWorld->GetKey(KeyCode::LEFT))
  {
    MoveTo(GetX()-4,GetY());
  }
  if(theWorld->GetKey(KeyCode::RIGHT))
  {
    MoveTo(GetX()+4,GetY());
  }
  if(GetX()<0)MoveTo(0,GetY());
  if(GetX()>=WINDOW_WIDTH)MoveTo(WINDOW_WIDTH-1,GetY());
  if(GetY()<0)MoveTo(GetX(),0);
  if(GetY()>=WINDOW_HEIGHT)MoveTo(GetX(),WINDOW_HEIGHT-1);
  if(theWorld->GetKey(KeyCode::FIRE1)&&Get_energy()>=10)
  {
    Set_energy(Get_energy()-10);
    theWorld->Get_pos_l()->push_back(new Blue_bullet(GetX(), GetY() + 50, 0.5f + 0.1f * theWorld->Get_Powerup(), 5 + 3 * theWorld->Get_Powerup()));
  }
  if(theWorld->GetKeyDown(KeyCode::FIRE2)&&theWorld->Get_Meteor()>0)
  {
    theWorld->Get_pos_l()->push_back(new Meteor(GetX(),std::min(GetY()+100,WINDOW_HEIGHT-1),100000));
    theWorld->Set_Meteor(theWorld->Get_Meteor()-1);
  }
  if(Get_energy()<10)Set_energy(Get_energy()+1);
}

const int Enemy::Get_attack()const 
{
  return m_attack;
}
const int Enemy::Get_fly_mode()const{
  return m_fly_mode;
}
const int Enemy::Get_speed()const{
  return m_speed;
}
const void Enemy::Set_fly_mode(int fly_mode)
{
  m_fly_mode=fly_mode;
}
const int Enemy::Get_fly_time()const {
  return m_fly_time;
}
const void Enemy::Set_fly_time(int fly_time)
{
  m_fly_time=fly_time;
}
const void Enemy::Set_speed(int speed)
{
  m_speed=speed;
}

void Alphatron::destroy()
{
  //GameObject* p = new Explosion(GetX(), GetY());
  theWorld->Get_pos_l()->push_back(new Explosion(GetX(), GetY()));
  theWorld->IncreaseScore(50);
  theWorld->Set_destroyed(theWorld->Get_destroyed()+1);
  theWorld->Set_onScreen(theWorld->Get_onScreen() - 1);
}

void Alphatron::Update()
{
  if(Get_is_dead())return;
  if(GetY()<0)
  {
    Set_is_dead(true);
    theWorld->Set_onScreen(theWorld->Get_onScreen() - 1);
    return;
  }
  Dawnbreaker* pos=nullptr;
  for(std::list<GameObject*>::iterator it=theWorld->Get_pos_l()->begin(); it != theWorld->Get_pos_l()->end(); ++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Blue_bullet*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_HP(Get_HP()- dynamic_cast<Blue_bullet*>(*it)->Get_damage());
      (*it)->Set_is_dead(true);
      if(Get_HP()<=0){
        Set_is_dead(true),destroy();
        return;
      }
    }
    if(dynamic_cast<Meteor*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_is_dead(true);destroy();
      //(*it)->Set_is_dead(true);
      return;
    }
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_is_dead(true);destroy();
      dynamic_cast<Dawnbreaker*>(*it)->Set_HP(dynamic_cast<Dawnbreaker*>(*it)->Get_HP()-20);
      if(dynamic_cast<Dawnbreaker*>(*it)->Get_HP()<=0) dynamic_cast<Dawnbreaker*>(*it)->Set_is_dead(true);
      return;
    }
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr) pos= dynamic_cast<Dawnbreaker*>(*it);
  }
  if(std::abs(pos->GetX()-GetX())<=10)
  {
    if(Get_energy() >= 25)
    {
      if(randInt(1,4)==1)
      {
        Set_energy(Get_energy()-25);
        theWorld->Get_pos_l()->push_back(new Red_bullet(GetX(),GetY()-50,180,Get_attack(),1));
      }
    }
  }
  if(Get_energy()<25) Set_energy(Get_energy()+1);
  if(Get_fly_time()==0)
  {
    int r=randInt(1,3);
    if(r==1)
    {
      Set_fly_mode(1);Set_fly_time(randInt(10,50));
    }else if(r==2)
    {
      Set_fly_mode(2);Set_fly_time(randInt(10,50));
    }else{
      Set_fly_mode(3);Set_fly_time(randInt(10,50));
    }
  }
  if(GetX()<0)
  {
    Set_fly_mode(2);Set_fly_time(randInt(10,50));
  }
  if(GetX()>=WINDOW_WIDTH)
  {
    Set_fly_mode(3);Set_fly_time(randInt(10,50));
  }
  Set_fly_time(Get_fly_time()-1);
  if(Get_fly_mode()==1)
  {
    MoveTo(GetX(),GetY()-Get_speed());
  }else if(Get_fly_mode()==2)
  {
    MoveTo(GetX()+Get_speed(),GetY()-Get_speed());
  }else if(Get_fly_mode()==3)
  {
    MoveTo(GetX()-Get_speed(),GetY()-Get_speed());
  }
  for(std::list<GameObject*>::iterator it=theWorld->Get_pos_l()->begin(); it != theWorld->Get_pos_l()->end(); ++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Blue_bullet*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_HP(Get_HP()- dynamic_cast<Blue_bullet*>(*it)->Get_damage());
      (*it)->Set_is_dead(true);
      if(Get_HP()<=0){
        Set_is_dead(true),destroy();
        return;
      }
    }
    if(dynamic_cast<Meteor*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_is_dead(true);destroy();
      //(*it)->Set_is_dead(true);
      return;
    }
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_is_dead(true);destroy();
      dynamic_cast<Dawnbreaker*>(*it)->Set_HP(dynamic_cast<Dawnbreaker*>(*it)->Get_HP()-20);
      if(dynamic_cast<Dawnbreaker*>(*it)->Get_HP()<=0) (*it)->Set_is_dead(true);
      return;
    }
  }
}

void Sigmatron::Update()
{
  if(Get_is_dead()) return;
  if(GetY()<0)
  {
    Set_is_dead(true);
    theWorld->Set_onScreen(theWorld->Get_onScreen() - 1);
    return;
  }

  Dawnbreaker* pos=nullptr;
  for(std::list<GameObject*>::iterator it=theWorld->Get_pos_l()->begin();it!=theWorld->Get_pos_l()->end();++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Blue_bullet*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_HP(Get_HP()- dynamic_cast<Blue_bullet*>(*it)->Get_damage());
      (*it)->Set_is_dead(true);
      if(Get_HP()<=0){
        Set_is_dead(true);destroy();
        return;
      }
    }
    if(dynamic_cast<Meteor*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_is_dead(true);destroy();
      //(*it)->Set_is_dead(true);
      return;
    }
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_is_dead(true);destroy();
      dynamic_cast<Dawnbreaker*>(*it)->Set_HP(dynamic_cast<Dawnbreaker*>(*it)->Get_HP()-20);
      if(dynamic_cast<Dawnbreaker*>(*it)->Get_HP()<=0) (*it)->Set_is_dead(true);
      return;
    }
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr) pos= dynamic_cast<Dawnbreaker*>(*it);
  }
  if(std::abs(pos->GetX()-GetX())<=10)
  {
    Set_fly_mode(1);Set_fly_time(WINDOW_HEIGHT);
    Set_speed(10);
  }

  if(Get_fly_time()==0)
  {
    int r=randInt(1,3);
    if(r==1)
    {
      Set_fly_mode(1);Set_fly_time(randInt(10,50));
    }else if(r==2)
    {
      Set_fly_mode(2);Set_fly_time(randInt(10,50));
    }else{
      Set_fly_mode(3);Set_fly_time(randInt(10,50));
    }
  }
  if(GetX()<0)
  {
    Set_fly_mode(2);Set_fly_time(randInt(10,50));
  }
  if(GetX()>=WINDOW_WIDTH)
  {
    Set_fly_mode(3);Set_fly_time(randInt(10,50));
  }
  Set_fly_time(Get_fly_time()-1);
  if(Get_fly_mode()==1)
  {
    MoveTo(GetX(),GetY()-Get_speed());
  }else if(Get_fly_mode()==2)
  {
    MoveTo(GetX()+Get_speed(),GetY()-Get_speed());
  }else if(Get_fly_mode()==3)
  {
    MoveTo(GetX()-Get_speed(),GetY()-Get_speed());
  }

  for(std::list<GameObject*>::iterator it=theWorld->Get_pos_l()->begin();it!=theWorld->Get_pos_l()->end();++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Blue_bullet*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_HP(Get_HP()- dynamic_cast<Blue_bullet*>(*it)->Get_damage());
      (*it)->Set_is_dead(true);
      if(Get_HP()<=0){
        Set_is_dead(true);destroy();
        return;
      }
    }
    if(dynamic_cast<Meteor*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_is_dead(true);destroy();
      //(*it)->Set_is_dead(true);
      return;
    }
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_is_dead(true);destroy();
      dynamic_cast<Dawnbreaker*>(*it)->Set_HP(dynamic_cast<Dawnbreaker*>(*it)->Get_HP()-20);
      if(dynamic_cast<Dawnbreaker*>(*it)->Get_HP()<=0) (*it)->Set_is_dead(true);
      return;
    }
  }

}

void Sigmatron::destroy()
{
  theWorld->Get_pos_l()->push_back(new Explosion(GetX(),GetY()));
  theWorld->IncreaseScore(100);theWorld->Set_destroyed(theWorld->Get_destroyed()+1);
  theWorld->Set_onScreen(theWorld->Get_onScreen()-1);
  if(randInt(1,5)==1)
  {
    theWorld->Get_pos_l()->push_back(new HP_Restore(GetX(),GetY()));
  }
}



void Omegatron::Update()
{
  if(Get_is_dead()) return;
  if(GetY()<0)
  {
    Set_is_dead(true);
    theWorld->Set_onScreen(theWorld->Get_onScreen() - 1);
    return;
  }

  Dawnbreaker* pos;
  for(std::list<GameObject*>::iterator it=theWorld->Get_pos_l()->begin();it!=theWorld->Get_pos_l()->end();++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Blue_bullet*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_HP(Get_HP()- dynamic_cast<Blue_bullet*>(*it)->Get_damage());
      (*it)->Set_is_dead(true);
      if(Get_HP()<=0){
        Set_is_dead(true);destroy();
        return;
      }
    }
    if(dynamic_cast<Meteor*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_is_dead(true);destroy();
      //(*it)->Set_is_dead(true);
      return;
    }
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_is_dead(true);destroy();
      dynamic_cast<Dawnbreaker*>(*it)->Set_HP(dynamic_cast<Dawnbreaker*>(*it)->Get_HP()-20);
      if(dynamic_cast<Dawnbreaker*>(*it)->Get_HP()<=0) (*it)->Set_is_dead(true);
      return;
    }
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr) pos= dynamic_cast<Dawnbreaker*>(*it);
  }
  if(Get_energy()>=50)
  {
    theWorld->Get_pos_l()->push_back(new Red_bullet(GetX(),GetY(),162,Get_attack(),3));
    theWorld->Get_pos_l()->push_back(new Red_bullet(GetX(),GetY(),198,Get_attack(),2));
    Set_energy(Get_energy() - 50);
  }
  if(Get_energy()<50)Set_energy(Get_energy()+1);

  if(Get_fly_time()==0)
  {
    int r=randInt(1,3);
    if(r==1)
    {
      Set_fly_mode(1);Set_fly_time(randInt(10,50));
    }else if(r==2)
    {
      Set_fly_mode(2);Set_fly_time(randInt(10,50));
    }else{
      Set_fly_mode(3);Set_fly_time(randInt(10,50));
    }
  }
  if(GetX()<0)
  {
    Set_fly_mode(2);Set_fly_time(randInt(10,50));
  }
  if(GetX()>=WINDOW_WIDTH)
  {
    Set_fly_mode(3);Set_fly_time(randInt(10,50));
  }
  Set_fly_time(Get_fly_time()-1);
  if(Get_fly_mode()==1)
  {
    MoveTo(GetX(),GetY()-Get_speed());
  }else if(Get_fly_mode()==2)
  {
    MoveTo(GetX()+Get_speed(),GetY()-Get_speed());
  }else if(Get_fly_mode()==3)
  {
    MoveTo(GetX()-Get_speed(),GetY()-Get_speed());
  }

  for(std::list<GameObject*>::iterator it=theWorld->Get_pos_l()->begin();it!=theWorld->Get_pos_l()->end();++it)
  {
    if((*it)->Get_is_dead())continue;
    if(dynamic_cast<Blue_bullet*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_HP(Get_HP()- dynamic_cast<Blue_bullet*>(*it)->Get_damage());
      (*it)->Set_is_dead(true);
      if(Get_HP()<=0){
        Set_is_dead(true);destroy();
        return;
      }
    }
    if(dynamic_cast<Meteor*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_is_dead(true);destroy();
      //(*it)->Set_is_dead(true);
      return;
    }
    if(dynamic_cast<Dawnbreaker*>(*it)!=nullptr&&collide(this,*it))
    {
      Set_is_dead(true);destroy();
      dynamic_cast<Dawnbreaker*>(*it)->Set_HP(dynamic_cast<Dawnbreaker*>(*it)->Get_HP()-20);
      if(dynamic_cast<Dawnbreaker*>(*it)->Get_HP()<=0) (*it)->Set_is_dead(true);
      return;
    }
  }

}
void Omegatron::destroy()
{
  theWorld->Get_pos_l()->push_back(new Explosion(GetX(),GetY()));
  theWorld->IncreaseScore(200);theWorld->Set_destroyed(theWorld->Get_destroyed()+1);
  theWorld->Set_onScreen(theWorld->Get_onScreen()-1);
  if(randInt(1,5)<=2)
  {
    if(randInt(1,5)==1)theWorld->Get_pos_l()->push_back(new Meteor_Goodie(GetX(),GetY()));
    else theWorld->Get_pos_l()->push_back(new Power_up(GetX(),GetY()));
  }
}