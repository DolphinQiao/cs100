#include "GameWorld.hpp"
#include "cstdio"

GameWorld* theWorld = nullptr;
GameWorld::~GameWorld() {}

void GameWorld::Init() {
  // YOUR CODE HERE
	SetWave(0);
	SetSun(50);
	m_sun_count_down = 180;
	m_wave_count_down = 1200;
	m_on_hand = -1;
	//SetSun(999999); ∆∆Ω‚∞Ê
	m_obj.push_back(std::make_shared<Background>());
	int pos_x = FIRST_ROW_CENTER;
	int pos_y = FIRST_COL_CENTER;
	for (int i = 0; i < GAME_ROWS; ++i)
	{
		pos_x = FIRST_ROW_CENTER;
		for (int j = 0; j < GAME_COLS; ++j)
		{
			m_obj.push_back(std::make_shared<Spot>(pos_x, pos_y));
			pos_x += LAWN_GRID_WIDTH;
		}
		pos_y += LAWN_GRID_HEIGHT;
	}
	m_obj.push_back(std::make_shared<Sunflower_seed>());
	m_obj.push_back(std::make_shared<Peashooter_seed>());
	m_obj.push_back(std::make_shared<Wallnut_seed>());
	m_obj.push_back(std::make_shared<Cherrybomb_seed>());
	m_obj.push_back(std::make_shared<Repeater_seed>());
	m_obj.push_back(std::make_shared<Shovel>());

}

LevelStatus GameWorld::Update() {
  // YOUR CODE HERE
	//ÃÌº”—Ùπ‚
	if (m_sun_count_down > 0)
	{
		m_sun_count_down--;
	}
	else
	{
		m_obj.push_back(std::make_shared<Sun>(randInt(75, WINDOW_HEIGHT - 75), WINDOW_HEIGHT - 1, 1));
		m_sun_count_down = 300;
	}

	//…˙≥…–¬µƒΩ© ¨
	if (m_wave_count_down > 0)
	{
		m_wave_count_down--;
	}
	else
	{
		SetWave(GetWave() + 1);
		int num_zombie = int((15 + GetWave()) / 10);
		m_wave_count_down = std::max(150, 600 - 20 * GetWave());
		double P1r = 20;
		double P2r = 2 * std::max(GetWave() - 8, 0);
		double P3r = 3 * std::max(GetWave() - 15, 0);
		for (int i = 0; i < num_zombie; ++i)
		{
			int row = randInt(0, 4);
			int r = randInt(1, P1r + P2r + P3r);
			int x = randInt(WINDOW_WIDTH - 40, WINDOW_WIDTH - 1);
			int y = FIRST_ROW_CENTER + LAWN_GRID_HEIGHT * row;
			if (r >= 1 && r <= P1r)
			{
				m_obj.push_back(std::make_shared<Regular_zombie>(x, y));
			}
			else if (r > P1r && r <= P2r + P1r)
			{
				m_obj.push_back(std::make_shared<Bucket_zombie>(x, y));
			}
			else
			{
				m_obj.push_back(std::make_shared<Vaulting_zombie>(x, y));
			}
		}
	}

	//±È¿˙Update
	for (auto it = m_obj.begin(); it != m_obj.end(); ++it)
	{
		(*it)->Update();
	}

	//ºÏ≤‚≈ˆ◊≤
	for (auto it = m_obj.begin(); it != m_obj.end(); ++it)
	{
		if ((*it)->is_zombie())
		{
			for (auto other = m_obj.begin(); other != m_obj.end(); ++other)
			{
				if (!(*other)->is_zombie())
				{
					if ((*other)->collide_class() == GameObject::COLLIDE_TYPE::OTHER) continue;
					if ((*it)->collide(*other))
					{
						if ((*other)->collide_class() == GameObject::COLLIDE_TYPE::PLANT)//÷≤ŒÔ
						{
							auto& plant = dynamic_cast<Plant&>(**other);
							auto& zombie = dynamic_cast<Zombie&>(**it);
							
							if (zombie.GetStatus() == Zombie::STATUS_TYPE::WALKING)
							{
								zombie.PlayAnimation(ANIMID_EAT_ANIM);
								zombie.SetStatus(Zombie::STATUS_TYPE::EATING);
							}
							if (zombie.GetStatus() == Zombie::STATUS_TYPE::EATING)
							{
								plant.SetHP(plant.GetHP() - 3);
							}
						}
						else if ((*other)->collide_class() == GameObject::COLLIDE_TYPE::PEA)//Õ„∂π
						{
							auto& pea = dynamic_cast<Pea&>(**other);
							if (pea.Get_is_dead()) continue;
							auto& zombie = dynamic_cast<Zombie&>(**it);
							pea.Set_is_dead(true);
							zombie.SetHP(zombie.GetHP() - 20);
							if (zombie.GetHP() <= 0)
							{
								zombie.Set_is_dead(true);
							}
						}
						else if ((*other)->collide_class() == GameObject::COLLIDE_TYPE::EXPLOSION)//±¨’®
						{
							auto& zombie = dynamic_cast<Zombie&>(**it);
							zombie.Set_is_dead(true);
						}
					}
				}
			}
		}
	}

	//…æ≥˝À¿Õˆµƒ∂‘œÛ
	for (auto it = m_obj.begin(); it != m_obj.end(); ++it)
	{
		if ((*it)->Get_is_dead())
		{
			m_obj.erase(it--);
		}
	}

	//≈–∂œ «∑Ò ‰µÙ
	for (auto it = m_obj.begin(); it != m_obj.end(); ++it)
	{
		if ((*it)->is_zombie())
		{
			if ((*it)->GetX() < 0)
			{
				return LevelStatus::LOSING;
			}
		}
	}

	//≈–∂œ «∑ÒΩ‚≥˝≥‘

	for (auto it = m_obj.begin(); it != m_obj.end(); ++it)
	{
		if ((*it)->is_zombie())
		{
			bool collide = false;
			for (auto other = m_obj.begin(); other != m_obj.end(); ++other)
			{
				if (!(*other)->is_zombie())
				{
					if ((*it)->collide(*other) && (*other)->collide_class() == GameObject::COLLIDE_TYPE::PLANT) 
					{
						collide = true;
					}
				}
			}
			if (collide == false)
			{
				auto& zombie = dynamic_cast<Zombie&>(**it);
				
				if (zombie.GetStatus() == Zombie::STATUS_TYPE::EATING)
				{
					zombie.PlayAnimation(ANIMID_WALK_ANIM);
					zombie.SetStatus(Zombie::STATUS_TYPE::WALKING);
				}
			}
		}
	}
	
	return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
  // YOUR CODE HERE
	m_obj.clear();

}

int GameWorld::Get_onhand()
{
	return m_on_hand;
}

void GameWorld::Set_onhand(int onhand)
{
	m_on_hand = onhand;
}

void GameWorld::Add_obj(std::shared_ptr<GameObject> obj)
{
	m_obj.push_back(obj);
}

std::list<std::shared_ptr<GameObject>>::iterator GameWorld::Get_obj_begin()
{
	return m_obj.begin();
}

std::list<std::shared_ptr<GameObject>>::iterator GameWorld::Get_obj_end()
{
	return m_obj.end();
}