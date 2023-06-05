#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <memory>
#include "ObjectBase.hpp"

// Declares the class name GameWorld so that its pointers can be used.
class GameWorld;
using pGameWorld = std::shared_ptr<GameWorld>;

class GameObject : public ObjectBase, public std::enable_shared_from_this<GameObject> {
public:
	enum class COLLIDE_TYPE
	{
		OTHER, PLANT, PEA, EXPLOSION
	};
  GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID) :ObjectBase(imageID, x, y, layer, width, height, animID), m_is_dead(false) {};
  using std::enable_shared_from_this<GameObject>::shared_from_this; // Use shared_from_this() instead of "this".
  virtual void Update() = 0;
  bool collide(std::shared_ptr<GameObject> other);
  const bool Get_is_dead() const;
  const void Set_is_dead(bool);
  virtual bool is_zombie() = 0;
  virtual COLLIDE_TYPE collide_class() = 0;


  /*
  * 0 Other
  * 1 Plant
  * 2 Pea
  * 3 Explosion
  */
private:
	bool m_is_dead;
};


#endif // !GAMEOBJECT_HPP__
