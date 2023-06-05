#include "GameObject.hpp"
bool GameObject::collide(std::shared_ptr<GameObject> other)
{
	if ((GetWidth() + other->GetWidth()) / 2.0f > abs(GetX() - other->GetX()) &&
		(GetHeight() + other->GetHeight()) / 2.0f > abs(GetY() - other->GetY()))
		return true;
	return false;
}
const bool GameObject::Get_is_dead() const {
	return m_is_dead;
}
const void GameObject::Set_is_dead(bool is_dead)
{
	m_is_dead = is_dead;
}


