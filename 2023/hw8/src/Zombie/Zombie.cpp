#include "Zombie.hpp"
void Zombie::OnClick()
{
	return; 
}
bool Zombie::is_zombie()
{
	return true;
}

int Zombie::GetHP()
{
	return m_HP;
}

void Zombie::SetHP(int HP)
{
	m_HP = HP;
}

Zombie::STATUS_TYPE Zombie::GetStatus()
{
	return m_status;
}

void Zombie::SetStatus(Zombie::STATUS_TYPE Status)
{
	m_status = Status;
}

GameObject::COLLIDE_TYPE Zombie::collide_class()
{
	return GameObject::COLLIDE_TYPE::OTHER;
}

void Regular_zombie::Update()
{
	if (GetHP() <= 0)
	{
		Set_is_dead(true);
		return;
	}
	if (Get_is_dead())
	{
		return;
	}
	if (GetStatus() == Zombie::STATUS_TYPE::WALKING)
	{
		MoveTo(GetX() - 1, GetY());
	}
}

void Bucket_zombie::Update()
{
	if (GetHP() <= 0)
	{
		Set_is_dead(true);
		return;
	}
	if (Get_is_dead())
	{
		return;
	}
	if (GetHP() <= 200)
	{
		ChangeImage(IMGID_REGULAR_ZOMBIE);
	}
	if (GetStatus() == Zombie::STATUS_TYPE::WALKING)
	{
		MoveTo(GetX() - 1, GetY());
	}
}

void Vaulting_zombie::Update()
{
	if (GetHP() <= 0)
	{
		Set_is_dead(true);
		return;
	}
	if (Get_is_dead())
	{
		return;
	}
	if (GetStatus() == Zombie::STATUS_TYPE::WALKING)//walking
	{
		MoveTo(GetX() - 1, GetY());
	}
	else if(GetStatus() == Zombie::STATUS_TYPE::EATING)//eating
	{

	}
	else if(GetStatus() == Zombie::STATUS_TYPE::RUNNING)//running
	{
		MoveTo(GetX() - 40, GetY());
		for (auto it = theWorld -> Get_obj_begin(); it != theWorld-> Get_obj_end(); ++it)
		{
			if ((*it)->collide_class() == GameObject::COLLIDE_TYPE::PLANT && (*it)->collide(shared_from_this()))
			{
				auto& plant = dynamic_cast<Plant&>(**it);
				SetStatus(Zombie::STATUS_TYPE::STOP);
				m_count_down = 41;
				PlayAnimation(ANIMID_JUMP_ANIM);
			}
		}
		MoveTo(GetX() + 40, GetY());
		MoveTo(GetX() - 2, GetY());
	}
	else if (GetStatus() == Zombie::STATUS_TYPE::JUMPING)//jumping
	{

	}
	else if (GetStatus() == Zombie::STATUS_TYPE::STOP)//Stop
	{
		if (m_count_down > 0)
		{
			m_count_down--;
			return;
		}

		PlayAnimation(ANIMID_WALK_ANIM);
		SetStatus(Zombie::STATUS_TYPE::WALKING);
		MoveTo(GetX() - 150, GetY());
	}
}