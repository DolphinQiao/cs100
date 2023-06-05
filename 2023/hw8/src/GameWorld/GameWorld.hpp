#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "WorldBase.hpp"
#include "GameObject.hpp"
#include "utils.hpp"
#include "Background.hpp"
#include "Seed.hpp"
#include "Zombie.hpp"
#include "Plant.hpp"

extern GameWorld* theWorld;

class GameWorld : public WorldBase, public std::enable_shared_from_this<GameWorld> {
public:
	// Use shared_from_this() instead of "this".
	GameWorld() : m_obj(), m_sun_count_down(180), m_wave_count_down(1200), m_on_hand(-1) { theWorld = this; }; 
	//GameWorld() : m_obj(), m_sun_count_down(180), m_wave_count_down(12), m_on_hand(-1) { theWorld = this;}; 测试版
  virtual ~GameWorld();

  void Init() override;

  LevelStatus Update() override;

  void CleanUp() override;
  int Get_onhand();
  void Set_onhand(int onhand);
  void Add_obj(std::shared_ptr<GameObject> obj);
  std::list<std::shared_ptr<GameObject>>::iterator Get_obj_begin();
  std::list<std::shared_ptr<GameObject>>::iterator Get_obj_end();
  enum class HAND_TYPE
  {
	  NOTHING, SHOVEL, SUNFLOWER_SEED, PEASHOOTER_SEED, WALLNUT_SEED, CHERRY_BOMB_SEED, REPEATER_SEED
  };

private: 
	std::list<std::shared_ptr<GameObject>> m_obj;
	int m_sun_count_down;
	int m_wave_count_down;
	int m_on_hand;
	/*
	-1 手中没有东西
	0 铲子
	1 向日葵种子
	2 豌豆射手种子
	3 坚果墙种子
	4 樱桃炸弹种子
	5 双发射手种子

	*/
};

#endif // !GAMEWORLD_HPP__
