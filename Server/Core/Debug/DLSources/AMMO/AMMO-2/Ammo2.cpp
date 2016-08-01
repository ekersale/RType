#include "Ammo2.h"

Ammo2::Ammo2()
{
	_movement = 0;
}

Ammo2::~Ammo2()
{
}

void		Ammo2::setMovement(int move)
{
	_movement = move;
}

DRect		Ammo2::calcPos(DRect pos)
{
	pos.x -= 2;
	switch (_movement)
	{
	case 1:
		pos.y -= 1;
		break;
	case 2:
		pos.y += 1;
		break;
	default:
		break;
	}
	return (pos);
}

e_type		Ammo2::getType() const
{
	return (AMMO2);
}

int			Ammo2::getPower() const
{
	return (300);
}

#ifdef _WIN32
extern "C"
__declspec(dllexport) IAmmo* __cdecl getPtr()
{
	IAmmo *tmp = new Ammo2();

	return (tmp);
}
#else
extern "C"
{
  IAmmo* getPtr()
  {
    IAmmo *tmp = new Ammo2();

    return (tmp);
  }
}
#endif
