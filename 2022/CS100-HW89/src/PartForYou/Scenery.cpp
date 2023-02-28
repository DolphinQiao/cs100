#include "Scenery.h"
void Star::Update()
{
  if(GetY()<0)
  {
    Set_is_dead(true);
    return ;
  }
  MoveTo(GetX(),GetY()-1);
}

void Explosion::Update()
{
  if (Get_is_dead())return;
  SetSize(GetSize()-0.2f);
  Set_time(Get_time() - 1);
  if (Get_time() == 0)
  {
      Set_is_dead(true);
      return;
  }
}
const void Explosion::Set_time(int time)
{
    m_time = time;
}
const int Explosion::Get_time() const {
    return m_time;
}