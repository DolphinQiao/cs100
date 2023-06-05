#include "Plant.hpp"

bool Plant::is_zombie()
{
	return false;
}
void Plant::OnClick()
{
	if (theWorld->Get_onhand() == 0)
	{
		Set_is_dead(true);
		theWorld->Set_onhand(-1);
	}
}

GameObject::COLLIDE_TYPE Plant::collide_class()
{
	return GameObject::COLLIDE_TYPE::PLANT;
}

int Plant::GetHP()
{
	return m_HP;
}
void Plant::SetHP(int HP)
{
	m_HP = HP;
}

void Sunflower::Update()
{
	if (GetHP() <= 0)
	{
		Set_is_dead(true);
		return;
	}
	if (m_count_down > 0)
	{
		m_count_down--;
		return;
	}
	theWorld->Add_obj(std::make_shared<Sun>(GetX(), GetY(), 2));
	m_count_down = 600;

}

void Peashooter::Update()
{
	if (GetHP() <= 0)
	{
		Set_is_dead(true);
		return;
	}
	if (m_count_down > 0)
	{
		m_count_down--;
		return;
	}
	bool if_zombie = false;
	for (auto it = theWorld->Get_obj_begin(); it != theWorld->Get_obj_end(); ++it)
	{
		if ((*it)->is_zombie() && (*it)->GetX() > GetX() && GetY() == (*it)->GetY())
		{
			if_zombie = true;
		}
	}
	if (if_zombie)
	{
		theWorld->Add_obj(std::make_shared<Pea>(GetX() + 30, GetY() + 20));
		m_count_down = 30;
	}

}

void Wallnut::Update()
{
	if (Get_is_dead()) return;
	if (GetHP() < 4000 / 3)
	{
		ChangeImage(IMGID_WALLNUT_CRACKED);
	}
	if (GetHP() <= 0)
	{
		Set_is_dead(true);
	}
	return;
}

void Repeater::Update()
{
	if (Get_is_dead()) return;
	if (GetHP() <= 0)
	{
		Set_is_dead(true);
	}

	if (m_count_down > 0)
	{
		m_count_down--;
		if (m_count_down != 25- 1) return;
	}
	
	bool if_zombie = false;
	for (auto it = theWorld->Get_obj_begin(); it != theWorld->Get_obj_end(); ++it)
	{
		if ((*it)->is_zombie() && (*it)->GetX() > GetX() && GetY() == (*it)->GetY())
		{
			if_zombie = true;
		}
	}
	if(if_zombie){
		theWorld->Add_obj(std::make_shared<Pea>(GetX() + 30, GetY() + 20));
		if (m_count_down != 25 - 1)m_count_down = 30;
	}


	return;
}

void Cherry_bomb::Update()
{
	if (Get_is_dead()) return;
	if (GetHP() <= 0)
	{
		Set_is_dead(true);
	}

	if (m_count_down > 0)
	{
		m_count_down--;
		return;
	}

	theWorld->Add_obj(std::make_shared<Explosion>(GetX(), GetY()));
	Set_is_dead(true);
	return;
}