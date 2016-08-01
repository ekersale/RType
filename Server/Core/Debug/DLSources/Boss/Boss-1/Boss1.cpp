#define PI 3.14159265
#include "Boss1.h"

Boss1::Boss1()
{
	_angle = 0.0;
}

Boss1::~Boss1()
{

}

DRect		Boss1::calcPos(DRect pos)
{
	if (pos.x >= 1000)
		pos.x -= 2;
	if (pos.y > 20)
		pos.y -= 2;
	else if (pos.y < 700)
		pos.y += 2;
	return (pos);
}

bool		Boss1::getFireRate() const
{
	static int v = 0;

	if (v >= 100) {
		v = 0;
		return (true);
	}
	v++;
	return (false);
}

int			Boss1::getLifePoint() const
{
	return (1200);
}

DRect		*Boss1::getSpawn() const
{
	DRect	*tmp = new DRect();

	tmp->x = 1290;
	tmp->y = -10;
	return (tmp);
}

DRect		Boss1::getSizeObj() const
{
	DRect	tmp;

	tmp.x = 20;
	tmp.y = 80;
	return (tmp);
}

e_type		Boss1::getType() const
{
	return (BOSS1);
}

e_type		Boss1::getAmmo() const
{
	return (AMMO3);
}

int			Boss1::getReward() const
{
	return (1000);
}

#ifdef _WIN32
extern "C"
__declspec(dllexport) IEntities* __cdecl getPtr()
{
	IEntities *tmp = new Boss1();

	return (tmp);
}
#else
extern "C"
{
	IEntities* getPtr()
	{
		IEntities *tmp = new Boss1();

		return (tmp);
	}
}
#endif
