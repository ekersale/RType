#include "Ammo3.h"

Ammo3::Ammo3()
{
	_movement = 0;
	_direction = true;
}

Ammo3::~Ammo3()
{
}

void		Ammo3::setMovement(int move)
{
	_movement = move;
}

DRect		Ammo3::calcPos(DRect pos)
{
	pos.x -= 2;
	switch (_movement)
	{
	case 1:
		if (_direction == true) {
			pos.y -= 1;
			if (pos.y - 1 <= 0)
				_direction = false;
		}
		else {
			pos.y += 1;
			if (pos.y + 1 >= 780) {
				_direction = true;
			}
		}
	case 2:
		if (_direction == true) {
			pos.y += 1;
			if (pos.y + 1 >= 780) {
				_direction = true;
		}
		else {
			pos.y -= 1;
			if (pos.y - 1 <= 0)
				_direction = false;
			}
		}
		break;
	default:
		break;
	}
	return (pos);
}

e_type		Ammo3::getType() const
{
	return (AMMO3);
}

int			Ammo3::getPower() const
{
	return (200);
}

#ifdef _WIN32
extern "C"
__declspec(dllexport) IAmmo* __cdecl getPtr()
{
	IAmmo *tmp = new Ammo3();

	return (tmp);
}
#else
extern "C"
{
  IAmmo* getPtr()
  {
    IAmmo *tmp = new Ammo3();

    return (tmp);
  }
}
#endif
