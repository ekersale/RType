#define PI 3.14159265
#include "Monster1.h"

Monster1::Monster1()
{
	_movement = 1;
	_direction = true;
}

Monster1::~Monster1()
{

}

void		Monster1::setMovement(int move)
{
	_movement = move;
}

DRect		Monster1::calcPos(DRect pos)
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
			if (pos.y + 1 >= 755) {
				_direction = true;
			}
		}
	case 2:
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
		break;
	default:
		break;
	}
	return (pos);
}

bool		Monster1::getFireRate() const
{
	static int v = 0;

	if (v >= 100) {
		v = 0;
		return (true);
	}
	v++;
	return (false);
}

int			Monster1::getLifePoint() const
{
	return (400);
}

DRect		*Monster1::getSpawn() const
{
	DRect	*tmp = new DRect();

	tmp->x = 1290;
	tmp->y = -10;
	return (tmp);
}

DRect		Monster1::getSizeObj() const
{
	DRect	tmp;

	tmp.x = 10;
	tmp.y = 20;
	return (tmp);
}

e_type		Monster1::getType() const
{
	return (MONSTER2);
}

e_type		Monster1::getAmmo() const
{
	return (AMMO2);
}

int			Monster1::getReward() const
{
	return (150);
}

#ifdef _WIN32
extern "C"
__declspec(dllexport) IEntities* __cdecl getPtr()
{
	IEntities *tmp = new Monster1();

	return (tmp);
}
#else
extern "C"
{
	IEntities* getPtr()
	{
		IEntities *tmp = new Monster1();

		return (tmp);
	}
}
#endif
