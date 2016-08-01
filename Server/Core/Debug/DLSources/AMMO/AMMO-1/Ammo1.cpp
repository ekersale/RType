#include "Ammo1.h"

Ammo1::Ammo1()
{
	_movement = 0;
}

Ammo1::~Ammo1()
{
}

void		Ammo1::setMovement(int move)
{
	(void)move;
}

DRect		Ammo1::calcPos(DRect pos)
{
	pos.x -= 2;
	return (pos);
}

e_type		Ammo1::getType() const
{
	return (AMMO1);
}

int			Ammo1::getPower() const
{
	return (200);
}

#ifdef _WIN32
extern "C"
__declspec(dllexport) IAmmo* __cdecl getPtr()
{
	IAmmo *tmp = new Ammo1();

	return (tmp);
}
#else
extern "C"
{
  IAmmo* getPtr()
  {
    IAmmo *tmp = new Ammo1();

    return (tmp);
  }
}
#endif
