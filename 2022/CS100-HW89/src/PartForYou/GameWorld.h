#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <list>
#include "GameObjects.h"
#include "WorldBase.h"
#include "Spaceship.h"
#include "GameWorld.h"

#include <algorithm>
#include <cstring>


class Dawnbreaker;
class GameWorld;
extern GameWorld* theWorld;
class GameWorld : public WorldBase {
public:
	GameWorld() :m_chances(3), m_destroyed(0), m_onScreen(0), m_Meteors(0), m_Powerup(0),m_pos_DB(0){ theWorld = this; }
  virtual ~GameWorld();

  virtual void Init() override;

  virtual LevelStatus Update() override;

  virtual void CleanUp() override;

  virtual bool IsGameOver() const override;

  const int Get_Powerup() const;
  const void Set_Powerup(int);

  const int Get_Meteor() const;
  const void Set_Meteor(int);

  const int Get_destroyed()const;
  const void Set_destroyed(int);

  const int Get_onScreen()const;
  const void Set_onScreen(int);

  std::list<GameObject*>* Get_pos_l();
  
  int m_chances,m_destroyed,m_onScreen,m_Meteors,m_Powerup;

  std::list <GameObject*> m_l;

  //static GameWorld* theWorld() {
  //    static GameWorld* w = nullptr;
  //    if (w == nullptr)
  //        w = new GameWorld();
  //    else return w;
  //};
private:
  Dawnbreaker *m_pos_DB;
};



#endif // !GAMEWORLD_H__
