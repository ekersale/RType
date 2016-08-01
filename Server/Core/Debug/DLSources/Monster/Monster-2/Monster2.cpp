#define PI 3.14159265
#include "Monster2.h"

Monster2::Monster2()
{
	_movement = 1;
	_direction = true;
}

Monster2::~Monster2()
{

}

void		Monster2::setMovement(int move)
{
	_movement = move;
}

DRect		Monster2::calcPos(DRect pos)
{
	switch (_movement)
	{
	case 1:
		if (pos.x != 700)
			pos.x -= 2;
		else
		{
			if (_direction == true) {
				pos.y += 1;
				if (pos.y + 1 >= 755) {
					_direction = true;
				}
				else {
					pos.y -= 1;
					if (pos.y - 1 <= 0)
						_direction = false;
				}
			}
		}
		break;
	case 2:
		if (pos.x != 700)
			pos.x -= 2;
		else
		{
			if (_direction == true) {
				pos.y -= 1;
				if (pos.y - 1 <= 0)
					_direction = false;
				}
				else {
					pos.y += 1;
					if (pos.y + 1 >= 755) {
						_direction = true;
				}
			}
		}
		break;
	default:
		break;
	}
	return (pos);
}

bool		Monster2::getFireRate() const
{
	static int v = 0;

	if (v >= 200) {
		v = 0;
		return (true);
	}
	v++;
	return (false);
}

int			Monster2::getLifePoint() const
{
	return (500);
}

DRect		*Monster2::getSpawn() const
{
	DRect	*tmp = new DRect();

	tmp->x = 1290;
	tmp->y = 360;
	return (tmp);
}

DRect		Monster2::getSizeObj() const
{
	DRect	tmp;

	tmp.x = 10;
	tmp.y = 20;
	return (tmp);
}

e_type		Monster2::getType() const
{
	return (MONSTER3);
}

e_type		Monster2::getAmmo() const
{
	return (AMMO1);
}

int			Monster2::getReward() const
{
	return (200);
}

#ifdef _WIN32
extern "C"
__declspec(dllexport) IEntities* __cdecl getPtr()
{
	IEntities *tmp = new Monster2();

	return (tmp);
}
#else
extern "C"
{
	IEntities* getPtr()
	{
		IEntities *tmp = new Monster2();

		return (tmp);
	}
}
#endif
