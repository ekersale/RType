#define PI 3.14159265
#include "Boss3.h"

Boss3::Boss3()
{
	_angle = 0.0;
}

Boss3::~Boss3()
{

}

DRect		Boss3::calcPos(DRect pos)
{
	if (pos.x >= 1000)
		pos.x -= 2;
	if (pos.y > 20)
		pos.y -= 2;
	else if (pos.y < 700)
		pos.y += 2;
	return (pos);
}

bool		Boss3::getFireRate() const
{
	static int v = 0;

	if (v >= 100) {
		v = 0;
		return (true);
	}
	v++;
	return (false);
}

int			Boss3::getLifePoint() const
{
	return (3000);
}

DRect		*Boss3::getSpawn() const
{
	DRect	*tmp = new DRect();

	tmp->x = 1290;
	tmp->y = -10;
	return (tmp);
}

DRect		Boss3::getSizeObj() const
{
	DRect	tmp;

	tmp.x = 20;
	tmp.y = 80;
	return (tmp);
}

e_type		Boss3::getType() const
{
	return (BOSS3);
}

e_type		Boss3::getAmmo() const
{
	return (AMMO4);
}

int			Boss3::getReward() const
{
	return (3000);
}

#ifdef _WIN32
extern "C"
__declspec(dllexport) IEntities* __cdecl getPtr()
{
	IEntities *tmp = new Boss3();

	return (tmp);
}
#else
extern "C"
{
	IEntities* getPtr()
	{
		IEntities *tmp = new Boss3();

		return (tmp);
	}
}
#endif
