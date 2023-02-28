#include "GameWorld.h"

GameWorld* theWorld = nullptr;

GameWorld::~GameWorld() {
  for(std::list<GameObject*>::iterator it=m_l.begin();it!=m_l.end();++it)
  {
    delete *it;
  }
}

void GameWorld::Init() { 
  
  m_pos_DB=new Dawnbreaker();
  Set_destroyed(0);
  Set_Meteor(0);
  Set_onScreen(0);
  theWorld->Set_Powerup(0);
  m_l.push_back(m_pos_DB);
  for(int i=0;i<30;++i)
  {
    m_l.push_back(new Star(randInt(0,WINDOW_WIDTH-1),randInt(0,WINDOW_HEIGHT-1),1.0f*randInt(10,40)/100.0f));
  }
}

const int GameWorld::Get_Powerup() const{
  return m_Powerup;
}
const void GameWorld::Set_Powerup(int Powerup){
  m_Powerup=Powerup;
}

const int GameWorld::Get_Meteor() const
{
  return m_Meteors;
}
const void GameWorld::Set_Meteor(int Meteor)
{
  m_Meteors=Meteor;
}

const int GameWorld::Get_destroyed()const{
  return m_destroyed;
}
const void GameWorld::Set_destroyed(int destroyed)
{
  m_destroyed=destroyed;
}

const int GameWorld::Get_onScreen()const{
  return m_onScreen;
}
const void GameWorld::Set_onScreen(int onScreen)
{
  m_onScreen=onScreen;
}

std::list<GameObject*>* GameWorld::Get_pos_l(){
  return &m_l;
}

LevelStatus GameWorld::Update() {
  if(randInt(1,30)==1)
  {
    m_l.push_back(new Star(randInt(0,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,1.0f*randInt(10,40)/100.0f));
  }
  int required=3*GetLevel();
  int to_destroy=required-m_destroyed;
  int maxOnScreen = (5+GetLevel())/2;
  int allowed = std::min(to_destroy,maxOnScreen);
  if(m_onScreen<allowed)
  {
    if(randInt(1,100)<= allowed - m_onScreen)
    {
      int P1=6;int P2=2*std::max(GetLevel()-1,0);int P3=3*std::max(GetLevel()-2,0);
      int r=randInt(1,P1+P2+P3);
      if(r>=1&&r<=P1)
      {
        m_l.push_back(new Alphatron(randInt(1,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,20+2*GetLevel(),2+GetLevel()/5,4+GetLevel()));
      }else if(r<=P1+P2)
      {
        m_l.push_back(new Sigmatron(randInt(1,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,20+GetLevel(),2 + GetLevel() / 5, 25 + 5 * GetLevel()));
      }else{
        m_l.push_back(new Omegatron(randInt(1,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,20+GetLevel(),3+GetLevel()/4,2+2*GetLevel()));
      }
      Set_onScreen(Get_onScreen()+1);
    }
  }
  for(std::list<GameObject*>::iterator it = m_l.begin(); it != m_l.end(); ++it)
  {
    (*it)->Update();
    if (m_pos_DB->Get_HP() <= 0 || m_pos_DB->Get_is_dead() == true) {
        m_chances--;
        return LevelStatus::DAWNBREAKER_DESTROYED;
    }
  }
  if(m_destroyed==required)
  {
    CleanUp();
    return LevelStatus::LEVEL_CLEARED;
  }
  for(std::list<GameObject*>::iterator it=m_l.begin();it!=m_l.end();)
  {
    if((*it)->Get_is_dead())
    {
      delete* it;
      m_l.erase(it++);
    }
    else
    {
        it++;
    }
  }
  SetStatusBarMessage("HP:" + std::to_string(m_pos_DB->Get_HP()) + "/100   Meteors:" + std::to_string(m_Meteors) + "   Lives:"+std::to_string(m_chances)+"   Level:"+std::to_string(GetLevel())+"   Enemies:"+std::to_string(m_destroyed)+"/"+std::to_string(required)+"   Score:"+std::to_string(GetScore()));

  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
  for(std::list<GameObject*>::iterator it=m_l.begin();it!=m_l.end();)
  {
    delete *it;
    m_l.erase(it++);
  }
}
bool GameWorld::IsGameOver() const {
  if(m_chances==0)return true;
  return false;
}
