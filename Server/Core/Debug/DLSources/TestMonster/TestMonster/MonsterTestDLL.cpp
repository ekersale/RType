#define PI 3.14159265
#include "CommanderTest.h"

CommanderTest::CommanderTest()
{
	_angle = 0.0;
}

CommanderTest::~CommanderTest()
{

}

DRect		CommanderTest::calcPos(DRect pos)
{
	double tmp;

	pos.x -= 1;
	if ((tmp = sin(_angle * PI / 180)) > 0) {
		_angle += 2.0;
		pos.y += 1;
	}
	else if (tmp < 0)
		pos.y -= 1;
	else
		pos.y += 0;
	return (pos);
}

bool		CommanderTest::getFireRate() const
{
	static int v = 0;

	if (v >= 100) {
		v = 0;
		return (true);
	}
	v++;
	return (false);
}

int			CommanderTest::getLifePoint() const
{
	return (800);
}

DRect		*CommanderTest::getSpawn() const
{
	DRect	*tmp = new DRect();

	tmp->x = 1290;
	tmp->y = -10;
	return (tmp);
}

DRect		CommanderTest::getSizeObj() const
{
	DRect	tmp;

	tmp.x = 10;
	tmp.y = 20;
	return (tmp);
}

e_type		CommanderTest::getType() const
{
	return (MONSTER1);
}

e_type		CommanderTest::getAmmo() const
{
	return (AMMO1);
}

int			CommanderTest::getReward() const
{
	return (100);
}

extern "C"
__declspec(dllexport) IEntities* __cdecl getPtr()
{
	IEntities *tmp = new CommanderTest();

	return (tmp);
}