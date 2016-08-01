#define PI 3.14159265
#include "Monster0.h"

Monster0::Monster0()
{
	_movement = 0;
}

Monster0::~Monster0()
{

}

void		Monster0::setMovement(int move)
{
	(void)move;
}

DRect		Monster0::calcPos(DRect pos)
{
	pos.x -= 1;
	return (pos);
}

bool		Monster0::getFireRate() const
{
	static int v = 0;

	if (v >= 200) {
		v = 0;
		return (true);
	}
	v++;
	return (false);
}

int			Monster0::getLifePoint() const
{
	return (300);
}

DRect		*Monster0::getSpawn() const
{
	DRect	*tmp = new DRect();

	tmp->x = 1290;
	tmp->y = -10;
	return (tmp);
}

DRect		Monster0::getSizeObj() const
{
	DRect	tmp;

	tmp.x = 10;
	tmp.y = 20;
	return (tmp);
}

e_type		Monster0::getType() const
{
	return (MONSTER1);
}

e_type		Monster0::getAmmo() const
{
	return (AMMO1);
}

int			Monster0::getReward() const
{
	return (100);
}

#ifdef _WIN32
extern "C"
__declspec(dllexport) IEntities* __cdecl getPtr()
{
	IEntities *tmp = new Monster0();

	return (tmp);
}
#else
extern "C"
{
	IEntities* getPtr()
	{
		IEntities *tmp = new Monster0();

		return (tmp);
	}
}
#endif
