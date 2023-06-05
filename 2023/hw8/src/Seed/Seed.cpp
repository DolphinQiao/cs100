#include "Seed.hpp"
bool Seed::is_zombie()
{
	return false;
}

void Seed::OnClick()
{
	if (theWorld->Get_onhand() >= 0)
	{
		return;
	}
	if (theWorld->GetSun() >= m_price)
	{
		theWorld->Add_obj(std::make_shared<Mask>(GetX(), GetY(), Get_cooldown()));
		theWorld->SetSun(theWorld->GetSun() - m_price);
		theWorld->Set_onhand(m_type);
	}
}

GameObject::COLLIDE_TYPE Seed::collide_class()
{
	return GameObject::COLLIDE_TYPE::OTHER;
}

int Seed::Get_cooldown()
{
	return m_cooldown_time;
}

void Sunflower_seed::Update()
{
	return;
}

void Peashooter_seed::Update()
{
	return;
}

void Wallnut_seed::Update()
{
	return;
}

void Cherrybomb_seed::Update()
{
	return;
}

void Repeater_seed::Update()
{
	return;
}