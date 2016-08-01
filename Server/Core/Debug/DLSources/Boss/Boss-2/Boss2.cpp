#define PI 3.14159265
#include "Boss2.h"

Boss2::Boss2()
{
	_angle = 0.0;
}

Boss2::~Boss2()
{

}

DRect		Boss2::calcPos(DRect pos)
{
	if (pos.y >= 650)
		pos.y -= 2;
	if (pos.x > 20)
		pos.x -= 2;
	else if (pos.x < 1250)
		pos.x += 2;
	return (pos);
}

bool		Boss2::getFireRate() const
{
	static int v = 0;

	if (v >= 100) {
		v = 0;
		return (true);
	}
	v++;
	return (false);
}

int			Boss2::getLifePoint() const
{
	return (2000);
}

DRect		*Boss2::getSpawn() const
{
	DRect	*tmp = new DRect();

	tmp->x = 1290;
	tmp->y = 750;
	return (tmp);
}

DRect		Boss2::getSizeObj() const
{
	DRect	tmp;

	tmp.x = 80;
	tmp.y = 20;
	return (tmp);
}

e_type		Boss2::getType() const
{
	return (BOSS2);
}

e_type		Boss2::getAmmo() const
{
	return (AMMO3);
}

int			Boss2::getReward() const
{
	return (2000);
}

#ifdef _WIN32
extern "C"
__declspec(dllexport) IEntities* __cdecl getPtr()
{
	IEntities *tmp = new Boss2();

	return (tmp);
}
#else
extern "C"
{
	IEntities* getPtr()
	{
		IEntities *tmp = new Boss2();

		return (tmp);
	}
}
#endif
