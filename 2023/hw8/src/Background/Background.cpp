#include "Background.hpp"

bool Other::is_zombie()
{
	return false;
}

void Background::Update()
{
	return;
}
void Background::OnClick()
{
	return;
}

GameObject::COLLIDE_TYPE Background::collide_class()
{
	return GameObject::COLLIDE_TYPE::OTHER;
}

void Sun::Update()
{
	if (m_drop_time > 0)
	{
		if (m_drop_type == 1)//ÌìÉÏ
		{
			MoveTo(GetX(), GetY() - 2);
		}
		else
		{
			MoveTo(GetX() - 1, GetY() + m_acc);
			m_acc -= 1;
		}
		m_drop_time--;
	}
	else
	{
		if (m_death_time == 0) Set_is_dead(true);
		else m_death_time--;
	}
	return;
}
void Sun::OnClick()
{
	Set_is_dead(true);
	theWorld->SetSun(theWorld -> GetSun() + 25);

	return;
}

GameObject::COLLIDE_TYPE Sun::collide_class()
{
	return GameObject::COLLIDE_TYPE::OTHER;
}

void Spot::Update()
{
	return;
}
void Spot::OnClick()
{
	if (theWorld->Get_onhand() == 0)
	{
	}
	else if (theWorld->Get_onhand() == 1)
	{
		theWorld->Add_obj(std::make_shared<Sunflower>(GetX(), GetY()));
		theWorld->Set_onhand(-1);
	}
	else if (theWorld->Get_onhand() == 2)
	{
		theWorld->Add_obj(std::make_shared<Peashooter>(GetX(), GetY()));
		theWorld->Set_onhand(-1);
	}
	else if (theWorld->Get_onhand() == 3)
	{
		theWorld->Add_obj(std::make_shared<Wallnut>(GetX(), GetY()));
		theWorld->Set_onhand(-1);
	}
	else if (theWorld->Get_onhand() == 4)
	{
		theWorld->Add_obj(std::make_shared<Cherry_bomb>(GetX(), GetY()));
		theWorld->Set_onhand(-1);
	}
	else if (theWorld->Get_onhand() == 5)
	{
		theWorld->Add_obj(std::make_shared<Repeater>(GetX(), GetY()));
		theWorld->Set_onhand(-1);
	}
	return;
}

GameObject::COLLIDE_TYPE Spot::collide_class()
{
	return GameObject::COLLIDE_TYPE::OTHER;
}

void Mask::Update()
{
	if (m_count_down == 0) Set_is_dead(true);
	else m_count_down--;
	return;
}
void Mask::OnClick()
{
	return;
}

GameObject::COLLIDE_TYPE Mask::collide_class()
{
	return GameObject::COLLIDE_TYPE::OTHER;
}

void Shovel::Update()
{
	return;
}


void Shovel::OnClick()
{
	if (theWorld->Get_onhand() > 0) return;
	if (theWorld->Get_onhand() == 0)
	{
		theWorld->Set_onhand(-1);
	}
	else
	{
		theWorld->Set_onhand(0);
	}
}

GameObject::COLLIDE_TYPE Shovel::collide_class()
{
	return GameObject::COLLIDE_TYPE::OTHER;
}

void Pea::Update()
{
	if (Get_is_dead()) return;
	MoveTo(GetX() + 8, GetY());
	if (GetX() >= WINDOW_WIDTH)
	{
		Set_is_dead(true);
	}
	
}

void Pea::OnClick()
{
	return;
}

GameObject::COLLIDE_TYPE Pea::collide_class()
{
	return GameObject::COLLIDE_TYPE::PEA;
}

void Explosion::Update()
{
	if (Get_is_dead()) return;
	if (m_count_down > 0)
	{
		m_count_down--;
		return;
	}
	Set_is_dead(true);
}

void Explosion::OnClick()
{
	return;
}

GameObject::COLLIDE_TYPE Explosion::collide_class()
{
	return GameObject::COLLIDE_TYPE::EXPLOSION;
}