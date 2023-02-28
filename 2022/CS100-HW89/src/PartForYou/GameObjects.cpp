#include "GameObjects.h"
const bool GameObject::collide(GameObject *a,GameObject *b) const
{
	if (sqrt(
		(a->GetX() - b->GetX()) * (a->GetX() - b->GetX()) +
		(a->GetY() - b->GetY()) * (a->GetY() - b->GetY())
	) < 30.0f * (a->GetSize() + b->GetSize())
		)return true;
  return false;
}
const bool GameObject::Get_is_dead() const{
  return m_is_dead;
}
const void GameObject::Set_is_dead(bool is_dead)
{
  m_is_dead=is_dead;
}