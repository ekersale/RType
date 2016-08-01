#define PI 3.14159265
#include "Monster3.h"

Monster3::Monster3()
{
	_movement = 1;
	_direction = true;
}

Monster3::~Monster3()
{

}

void		Monster3::setMovement(int move)
{
	_movement = move;
}

DRect		Monster3::calcPos(DRect pos)
{
	if (pos.x > 700)
		pos.x -= 2;
	else if (pos.x < 1270)
		pos.x += 2;
	return (pos);
}

bool		Monster3::getFireRate() const
{
	static int v = 0;

	if (v >= 200) {
		v = 0;
		return (true);
	}
	v++;
	return (false);
}

int			Monster3::getLifePoint() const
{
	return (500);
}

DRect		*Monster3::getSpawn() const
{
	DRect	*tmp = new DRect();

	tmp->x = 1290;
	tmp->y = -10;
	return (tmp);
}

DRect		Monster3::getSizeObj() const
{
	DRect	tmp;

	tmp.x = 10;
	tmp.y = 20;
	return (tmp);
}

e_type		Monster3::getType() const
{
	return (MONSTER4);
}

e_type		Monster3::getAmmo() const
{
	return (AMMO3);
}

int			Monster3::getReward() const
{
	return (700);
}

#ifdef _WIN32
extern "C"
__declspec(dllexport) IEntities* __cdecl getPtr()
{
	IEntities *tmp = new Monster3();

	return (tmp);
}
#else
extern "C"
{
	IEntities* getPtr()
	{
		IEntities *tmp = new Monster3();

		return (tmp);
	}
}
#endif
